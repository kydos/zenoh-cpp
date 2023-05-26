#include "zenoh.hxx"
#include "cloudevents.pb.h"
#include <vector>
#include <string>

using namespace zenoh;
using namespace io::cloudevents::v1;

int main() {
    std::vector<std::string> vec;        
    
    Config cfg;
    
    auto z = std::get<Session>(open(std::move(cfg)));

    CloudEvent evt;
    auto key = "cloudevent/v1/some-event";
    evt.set_id(key);
    evt.set_source("my_source");
    evt.set_spec_version("1.0");
    evt.set_type("publication");
    evt.set_binary_data("Got the Cloud Event?");
    zenoh::PutOptions pots;
    pots.set_priority(zenoh::Priority::Z_PRIORITY_DATA);
    pots.set_congestion_control(zenoh::CongestionControl::Z_CONGESTION_CONTROL_BLOCK);
    zenoh::Encoding e;
    // We'll add explicit support for Protobuf
    e.set_prefix(zenoh::EncodingPrefix::Z_ENCODING_PREFIX_APP_CUSTOM);
    auto payload = evt.SerializeAsString();
    z.put(key, payload, pots);
    return 0;
}