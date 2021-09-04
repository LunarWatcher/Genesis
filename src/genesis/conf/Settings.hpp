#pragma once

#include <string>
#include <map>
#include <any>
#include <memory>

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
    std::string home;
    static std::shared_ptr<Settings> instance;

    Settings();

    std::string getHome();
    std::string join(const std::string& a, const std::string& b);

    GETTER(int, Int)
    GETTER(size_t, Size)
    GETTER(double, Double)
    GETTER(std::string, String)
    GETTER(bool, Bool)
};

#undef GETTER

}
