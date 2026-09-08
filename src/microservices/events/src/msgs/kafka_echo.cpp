#include <trantor/utils/Logger.h>

#include "kafka_echo.h"
#include "../utils/envs.h"

static constexpr std::string KAFKA_URL_DEF {"127.0.0.1:9092"};
std::string kafka_url = get_env("KAFKA_BROKERS", KAFKA_URL_DEF);


bool kafka_echo_check(KafkaMsg kafka_msg, const std::string& msg_data) {
    KafkaAPI kafka_api(kafka_url);

    if (kafka_api.send_msg(kafka_msg, msg_data)) {
        LOG_INFO << msg_data << " - successfully sent";
    } else {
        LOG_INFO << msg_data << " - sending error";
        return false;
    }

    std::string received_data { kafka_api.receive_msg(kafka_msg) };
    if (received_data == msg_data) {
        LOG_INFO << msg_data << " - successfully received";
        return true;
    }

    LOG_INFO << msg_data << " - receiving error";
    return false;
}
