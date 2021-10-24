#include "Settings.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>

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
    auto home = fs::path(stc::getHome());
    bool hasFolder = fs::exists(home / ".genesis/");

    // Standards:tm:
    // Also avoids problems if keys aren't stored
    // Would also let us store less data. /shrug
    conf = defaultConf;

    // I still can't get over how cool this operator is :D
    if (hasFolder && fs::exists(home / ".genesis/settings.confl")) {
        std::ifstream stream(home / ".genesis/settings.confl");
        std::string line = "";
        while (std::getline(stream, line)) {
            if (auto idx = line.find('='); idx != std::string::npos) {
                std::string key = line.substr(0, idx);
                std::string value = line.substr(idx + 1);
            } else {
                throw std::runtime_error("Malformed config at: " + line);
            }
        }
    } else {
        if(!hasFolder && !fs::create_directory(home, ".genesis")) {
            throw std::runtime_error("Failed to create settings directory");
        }
    }

}

}
