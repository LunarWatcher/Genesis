#pragma once

#include <nlohmann/json.hpp>

namespace genesis {
struct BehaviourTraits {

};

struct PhysicalTraits {

};

extern void from_json(const nlohmann::json& j, BehaviourTraits& r);
extern void from_json(const nlohmann::json& j, PhysicalTraits& r);
}
