#include "Settings.hpp"

#include "genesis/util/Compat.hpp"

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
    auto home = getHome();
    bool hasFolder = fs::exists(join(home, ".genesis/"));

    // Standards:tm:
    // Also avoids problems if keys aren't stored
    // Would also let us store less data. /shrug
    conf = defaultConf;

    if (hasFolder && fs::exists(join(home, ".genesis/settings.confl"))) {
        std::ifstream stream(join(home, ".genesis/settings.confl"));
        std::string line = "";
        while (std::getline(stream, line)) {
            if (auto idx = line.find("="); idx != std::string::npos) {
                std::string key = line.substr(0, idx);
                std::string value = line.substr(idx + 1);
                std::cout << key << ": " << value;
            } else {
                throw std::runtime_error("Malformed config at: " + line);
            }
        }
    } else {
        if(!hasFolder && !fs::create_directory(join(home, ".genesis"))) {
            throw std::runtime_error("Failed to create settings directory");
        }
    }

}

std::string Settings::getHome() {

    StdOptional<std::string> username;
    std::string remainingPath;

    std::string homePath = "";
#if defined(_WIN32) || defined(_WIN64)
    auto userProfile = EnvVariable::getEnv("USERPROFILE");

    if (userProfile == "") {
        auto homeDrive = EnvVariable::getEnv("HOMEDRIVE");
        if (homeDrive == "")
            homeDrive = "";

        auto envHomePath = EnvVariable::getEnv("HOMEPATH");

        if (envHomePath == "") {
            throw std::runtime_error("Failed to find home path");
        }
        homePath = homeDrive + envHomePath;
    } else
        homePath = userProfile;

    // Force forward slashes
    homePath = std::regex_replace(homePath, std::regex("\\\\"), "/");

#else
    /*
     The unixes are easier, because they should in theory share a single
     API that makes this a whole lot easier.
     The idea is checking for HOME if we're looking for the current user.
     If we can't find the home variable, fall back to a UNIX-specific^1
     function that retrieves the path, along with a few other details.
     see getpwnam(3) for more info on the functions, and passwd(5)
     for details on the struct. This code drops the HOME variable for
     various reasons.
     If a username has been supplied (~username/), getpwnam is used instead
     of getpwuid. This returns the same type of struct as getpwuid().
     The bonus with the UNIX approach is that it requires the user to exist,
     where as Windows for non-existent users with a custom specified path should
     in theory cause a bad path. This is on the user, however.
     ^1: untested on mac and other UNIX-based systems. Only verified on Linux.
    */
    struct passwd* passwdPtr = nullptr;

        // While the home environment variable can be used,
        // getenv() is considered insecure
        // secure_getenv is only available on GNU/Linux, and not Mac.
        // Mac is still compatible with the rest of the code,
        // so no environment variables are used
        passwdPtr = getpwuid(getuid());

    if (passwdPtr == nullptr && homePath == "") {
        throw std::runtime_error("Failed to find home directory");
    } else if (homePath == "")
        homePath = passwdPtr->pw_dir;
#endif
    return homePath;
}

std::string Settings::join(const std::string& a, const std::string& b) {
    if (a.ends_with("/")) {
        return b.starts_with("/") ? a + b.substr(1) : a + b;
    }
    return b.starts_with("/") ? a + b : a + "/" + b;
}

}
