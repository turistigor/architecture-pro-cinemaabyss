#include "movie.h"
#include "../msgs/kafka_echo.h"


DrogonHandlerPtr<> create_movie_handler = [](
    const drogon::HttpRequestPtr& req,
    DrogonHandlerCallback&& callback
) {
    LOG_INFO << "Create movie POST-request received";

    bool res = kafka_echo_check(KafkaMsg::MOVIE_CREATED, "Movie created");

    Json::Value json;
    json["status"] = (res == true) ? "success" : "failed";
    auto resp = drogon::HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(drogon::k201Created);

    LOG_INFO << "Create movie POST-request processed";

    callback(resp);
};
