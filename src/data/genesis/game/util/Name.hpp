#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace genesis {

struct Name {
    std::string name;
    std::string plural;
    std::string adjective;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Name, name, plural, adjective);
};

}
