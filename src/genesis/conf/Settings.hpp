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

    void save();

    // At least this beats manually doing the getters :')
    // These are just wrappers around std::any_cast, which we need anyway.
    // We already expose conf.
    GETTER(int, Int)
    GETTER(size_t, Size)
    GETTER(double, Double)
    GETTER(std::string, String)
    GETTER(bool, Bool)
};

#undef GETTER

}
