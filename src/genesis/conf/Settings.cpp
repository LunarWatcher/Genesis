#include "Settings.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>

#include "genesis/rendering/Constants.hpp"

#if !defined(_WIN32) && !defined(_WIN64)
    #include <pwd.h>
    // Used for getuid
    #include <sys/types.h>
    #include <unistd.h>
#else
    #include <windows.h>
#endif

namespace genesis {

std::shared_ptr<Settings> Settings::instance = std::make_shared<Settings>();

Settings::Settings() {
    home = Constants::isTest ? fs::path("./") : stc::getHome();
    // TODO: find a better way to manage data dirs. Maybe a shared class for all filesystem resources?
    bool hasFolder = fs::exists(home / ".genesis/");
    confPath = home / ".genesis" / "settings.json";

    // Standards:tm:
    // Also avoids problems if keys aren't stored
    // Would also let us store less data. /shrug
    conf = defaultConf;

    // I still can't get over how cool this operator is :D
    if (hasFolder && fs::exists(confPath)) {
        std::ifstream stream(confPath);
        nlohmann::json tmp;

        stream >> tmp;
        conf.update(tmp, true);
    } else {
        if(!hasFolder && !fs::create_directory(home / ".genesis")) {
            throw std::runtime_error("Failed to create settings directory");
        }
    }
}

void Settings::save() {
    std::ofstream f(confPath);
    f << conf << std::endl;
}

}
