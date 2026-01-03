#ifndef EVENTS_KAFKA_ECHO
#define EVENTS_KAFKA_ECHO

#include "../kafka/kafka_api.h"


bool kafka_echo_check(KafkaMsg kafka_msg, const std::string& msg_data);


#endif  // EVENTS_KAFKA_ECHO