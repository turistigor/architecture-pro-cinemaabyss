#include "user.h"
#include "../msgs/kafka_echo.h"


DrogonHandlerPtr<> create_user_handler = [](
    const drogon::HttpRequestPtr& req,
    DrogonHandlerCallback&& callback
) {
    LOG_INFO << "Create user POST-request received";

    bool res = kafka_echo_check(KafkaMsg::USER_CREATED, "User created");

    Json::Value json;
    json["status"] = (res == true) ? "success" : "failed";
    auto resp = drogon::HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(drogon::k201Created);

    LOG_INFO << "Create user POST-request processed";

    callback(resp);
};
