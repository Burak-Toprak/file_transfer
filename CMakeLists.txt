cmake_minimum_required(VERSION 3.15)

project(file_transfer)

add_library(observer_lib src/observer.cpp)
add_library(reading_lib src/reading.cpp)
add_library(file_transfer_lib src/file_transfer.cpp)
add_library(stream_lib src/stream.cpp)
add_library(server_lib src/server.cpp)
add_library(client_lib src/client.cpp)
add_library(server_connection_lib src/server_connection.cpp)
add_library(client_connection_lib src/client_connection.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(server src/main_server.cpp)
add_executable(client src/main_client.cpp)

target_link_libraries(file_transfer_lib observer_lib reading_lib)
target_link_libraries(stream_lib file_transfer_lib)
target_link_libraries(server_lib stream_lib)
target_link_libraries(client_lib stream_lib)
target_link_libraries(server_connection_lib server_lib)
target_link_libraries(client_connection_lib client_lib)
target_link_libraries(server server_connection_lib)
target_link_libraries(client client_connection_lib)

set_target_properties(server
PROPERTIES 
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/../server)

set_target_properties(client
PROPERTIES 
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/../client)