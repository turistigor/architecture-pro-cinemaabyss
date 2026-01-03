#include "payment.h"
#include "../msgs/kafka_echo.h"


DrogonHandlerPtr<> create_payment_handler = [](
    const drogon::HttpRequestPtr& req,
    DrogonHandlerCallback&& callback
) {
    LOG_INFO << "Create user POST-request received";

    bool res = kafka_echo_check(KafkaMsg::PAYMENT_CREATED, "Payment created");

    Json::Value json;
    json["status"] = (res == true) ? "success" : "failed";
    auto resp = drogon::HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(drogon::k201Created);

    LOG_INFO << "Create payment POST-request processed";

    callback(resp);
};
