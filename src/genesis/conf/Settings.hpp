#pragma once

#include <string>
#include <map>
#include <any>
#include <memory>

#include "stc/Environment.hpp"

namespace genesis {

#define GETTER(type, name) type get##name(const std::string& key) { return std::any_cast<type>(conf.at(key)); }

class Settings {
private:
    static inline std::map<std::string, std::any> defaultConf = {
        {"width", 1024},
        {"height", 576},
        {"volume", 100},
        {"fullscreen", false}
    };

public:
    std::map<std::string, std::any> conf;
    fs::path home;
    static std::shared_ptr<Settings> instance;

    Settings();

    GETTER(int, Int)
    GETTER(size_t, Size)
    GETTER(double, Double)
    GETTER(std::string, String)
    GETTER(bool, Bool)
};

#undef GETTER

}
