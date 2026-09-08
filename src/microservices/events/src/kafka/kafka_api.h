#ifndef EVENTS_KAFKA_API
#define EVENTS_KAFKA_API


#include <memory>

#include <kafka/KafkaConsumer.h>
#include <kafka/KafkaProducer.h>


using namespace kafka;
using namespace kafka::clients::consumer;
using namespace kafka::clients::producer;

enum KafkaMsg { MOVIE_CREATED = 1, USER_CREATED, PAYMENT_CREATED };


class KafkaAPI {
    Properties _consumer_props;
    Properties _producer_props;
    std::unique_ptr<KafkaConsumer> _consumer;
    std::unique_ptr<KafkaProducer> _producer;

public:
    explicit KafkaAPI(const std::string& kafka_url);

    bool send_msg(KafkaMsg kafka_msg, const std::string& msg_data);
    std::string receive_msg(KafkaMsg kafka_msg);
};


#endif  // EVENTS_KAFKA_API