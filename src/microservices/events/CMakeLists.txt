cmake_minimum_required(VERSION 3.16)
project(events VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Drogon REQUIRED)
find_package(unofficial-modern-cpp-kafka REQUIRED)

set(SOURCES
    src/main.cpp /
    src/utils/envs.cpp /
    src/endpoints/healthcheck.cpp /
    src/endpoints/movie.cpp /
    src/endpoints/user.cpp /
    src/endpoints/payment.cpp /
    src/msgs/kafka_echo.cpp /
    src/kafka/kafka_api.cpp /
    src/utils/envs.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon unofficial::modern-cpp-kafka::modern-cpp-kafka)
