#include "healthcheck.h"


DrogonHandlerPtr<> healthcheck_handler = [](
    const drogon::HttpRequestPtr& req,
    DrogonHandlerCallback&& callback
) {
    LOG_INFO << "Healthcheck GET-request received";

    Json::Value json;
    json["status"] = true;

    auto resp = drogon::HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(drogon::k200OK);

    LOG_INFO << "Healthcheck GET-request processed";

    callback(resp);
};
