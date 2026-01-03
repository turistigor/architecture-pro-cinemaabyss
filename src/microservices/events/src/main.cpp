#include <string>

#include <drogon/drogon.h>

#include "endpoints/handlers.h"
#include "utils/envs.h"

static constexpr uint16_t PORT_DEF {8082};
static constexpr std::string HOST_DEF {"0.0.0.0"};

static constexpr uint64_t THREADS_COUNT {4};


int main() {
    uint16_t port = get_env("EVENTS_PORT", PORT_DEF);
    std::string host = get_env("EVENTS_HOST", HOST_DEF);

    auto& app = drogon::app();

    app.setUploadPath("/tmp/drogon_uploads");
    app.setLogLevel(trantor::Logger::kInfo);
    app.addListener(host, port);
    app.setThreadNum(THREADS_COUNT);

    app.registerHandler("/api/events/health", healthcheck_handler, { drogon::Get });
    app.registerHandler("/api/events/movie", create_movie_handler, { drogon::Post });
    app.registerHandler("/api/events/user", create_user_handler, { drogon::Post });
    app.registerHandler("/api/events/payment", create_payment_handler, { drogon::Post });

    LOG_INFO << "Server starting on " << host << ":" << port;
    app.run();

    return 0;
};
