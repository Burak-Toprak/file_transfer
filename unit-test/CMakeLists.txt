cmake_minimum_required(VERSION 3.15)

project(unit_test)

add_subdirectory(googletest-1.15.0)

enable_testing()

add_library(observer_lib ../src/observer.cpp)
add_library(reading_lib ../src/reading.cpp)
add_library(file_transfer_lib ../src/file_transfer.cpp)
add_library(stream_lib ../src/stream.cpp)
add_library(server_lib ../src/server.cpp)
add_library(client_lib ../src/client.cpp)
add_library(server_connection_lib ../src/server_connection.cpp)
add_library(client_connection_lib ../src/client_connection.cpp)

include_directories(${PROJECT_SOURCE_DIR}/../include)
include_directories(${PROJECT_SOURCE_DIR}/googletest-1.15.0/googletest/include)

add_executable(server_test server_test.cpp)
add_executable(client_test client_test.cpp)

target_link_libraries(file_transfer_lib observer_lib reading_lib)
target_link_libraries(stream_lib file_transfer_lib)
target_link_libraries(server_lib stream_lib)
target_link_libraries(client_lib stream_lib)
target_link_libraries(server_connection_lib server_lib)
target_link_libraries(client_connection_lib client_lib)
target_link_libraries(server_test gtest gtest_main)
target_link_libraries(server_test server_connection_lib)
target_link_libraries(client_test gtest gtest_main)
target_link_libraries(client_test client_connection_lib)

set_target_properties(server_test
PROPERTIES 
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/../server)

set_target_properties(client_test
PROPERTIES 
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/../client)

add_test(s_test server_test)
add_test(c_test client_test)