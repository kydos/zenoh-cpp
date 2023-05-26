cmake_minimum_required(VERSION 3.20)
project(zenohcxx_examples LANGUAGES C CXX)

if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()

include(FetchContent)
include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories("./include")
FetchContent_declare(c_backend GIT_REPOSITORY "https://github.com/eclipse-zenoh/zenoh-c")
FetchContent_MakeAvailable(c_backend)
FetchContent_declare(cpp_wrapper GIT_REPOSITORY "https://github.com/eclipse-zenoh/zenoh-cpp" GIT_TAG main)
FetchContent_MakeAvailable(cpp_wrapper)



add_executable(zce_put zce_put.cxx generated/cloudevents.pb.cc)
target_link_libraries(zce_put PRIVATE zenohcxx::zenohc::lib ${Protobuf_LIBRARIES})
set_property(TARGET zce_put PROPERTY LANGUAGE CXX)
set_property(TARGET zce_put PROPERTY CXX_STANDARD 17)

add_executable(zce_sub zce_sub.cxx generated/cloudevents.pb.cc)
target_link_libraries(zce_sub PRIVATE zenohcxx::zenohc::lib ${Protobuf_LIBRARIES})
set_property(TARGET zce_sub PROPERTY LANGUAGE CXX)
set_property(TARGET zce_sub PROPERTY CXX_STANDARD 17)
