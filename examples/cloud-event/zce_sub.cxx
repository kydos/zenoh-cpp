#include <iostream>
#include "zenoh.hxx"
#include "cloudevents.pb.h"

using namespace zenoh;

void on_data(const Sample *s) {
    std::cout << "Received Cloud Event" << std::endl;
}

int main() {
    auto key = "cloudevent/v1/**";
    Config cfg;
    auto z = std::get<Session>(open(std::move(cfg)));
    auto s = std::get<Subscriber>(z.declare_subscriber(key, on_data));
    char ch;
    std::cout << "Press a key to exit" << std::endl;
    std::cin >> ch;
    return 0;
}
