#include <unordered_set>

#include "kafka_api.h"

static std::unordered_map<KafkaMsg, std::string> kafka_topics{
    {KafkaMsg::MOVIE_CREATED, "movie-events"},
    {KafkaMsg::USER_CREATED, "user-events"},
    {KafkaMsg::PAYMENT_CREATED, "payment-events"}
};

static std::set<std::string> kafka_topics_set {
    "movie-events", "user-events", "payment-events"
};


KafkaAPI::KafkaAPI(const std::string& kafka_url) {
    this->_consumer_props.put("bootstrap.servers", kafka_url);
    this->_consumer_props.put("group.id", "events-group");
    this->_consumer_props.put("enable.auto.commit", "true");
    this->_consumer_props.put("auto.offset.reset", "earliest");
    this->_consumer_props.put("session.timeout.ms", "10000");

    this->_consumer = std::make_unique<KafkaConsumer>(this->_consumer_props);
    this->_consumer->setLogLevel(Log::Level::Err);
    this->_consumer->subscribe({kafka_topics_set});

    this->_producer_props.put("bootstrap.servers", kafka_url);
    this->_producer_props.put("socket.timeout.ms", "1000");
    this->_producer_props.put("enable.idempotence", "true");

    this->_producer = std::make_unique<KafkaProducer>(this->_producer_props);
    this->_producer->setLogLevel(Log::Level::Err);
}


bool KafkaAPI::send_msg(KafkaMsg kafka_msg, const std::string& msg_data) {
    std::string topic{ kafka_topics[kafka_msg] };
    Key key{ &kafka_msg, sizeof(key) };
    Value value{ msg_data.c_str(), msg_data.size()};
    ProducerRecord record(topic, key, value);

    RecordMetadata record_md = this->_producer->syncSend(record);
    return record_md.persistedStatus() == RecordMetadata::PersistedStatus::Done;
}


std::string KafkaAPI::receive_msg(KafkaMsg kafka_msg) {
    std::string topic{ kafka_topics[kafka_msg] };

    auto records = this->_consumer->poll(std::chrono::seconds(1));
    if (!records.size()) {
        std::cerr << "There are no messages" << std::endl;
        return {};
    }

    auto record = records.back();
    if (record.error()) {
        std::cerr << "Message receiving error: " << record.toString() << std::endl;
    }
    auto value {record.value().toString()};
    std::cout << "Value from the received msg: " << value << std::endl;
    return value;
}
