#include "catch2/catch_test_macros.hpp"
#include "genesis/conf/Settings.hpp"

#include <iostream>
#include <fstream>

TEST_CASE("Verifying catch2 + ctest linked", "[TemporaryTest]") {
    // Clean start
    fs::remove_all("./.genesis");

    SECTION("Basic writing should work") {
        genesis::Settings settings;
        // Make sure the new directory has been created
        REQUIRE(fs::exists("./.genesis"));
        // The config file itself shouldn't be automatically created
        REQUIRE_FALSE(fs::exists("./.genesis/settings.json"));

        // Compare to two semi-arbitrary standards to make sure loading works.
        // This does not make sure all the standards are in place.
        // If some of them are, they probably all are.
        REQUIRE(settings.getInt("width") == 1024);
        REQUIRE(settings.getInt("volume") == 100);

        settings.conf["width"] = 1920;

        settings.save();
        REQUIRE(fs::exists("./.genesis/settings.json"));

        genesis::Settings load;
        REQUIRE(load.getInt("width") == 1920);
    }
    SECTION("Unsaved config should be discarded") {
        for (int i = 0; i < 2; ++i) {
            {
                genesis::Settings settings;

                settings.conf["width"] = 1920;
                settings.conf["fullscreen"] = true;
                if (i == 1) {
                    settings.save();
                }
            }

            bool saved = fs::exists("./.genesis/settings.json");
            if (i == 0) {
                REQUIRE_FALSE(saved);
            } else {
                REQUIRE(saved);
            }
        }
    }
    SECTION("Partial config should be substituted with defaults") {
        nlohmann::json file{
            {"width", 694},
            {"fullscreen", true}
        };

        std::ofstream dumpFile("./genesis/settings.json");
        dumpFile << file << std::endl;

        genesis::Settings settings;

        // Again, don't need to test everything. Some missing holes being filled in is good enough
        // Though if there ever are subkeys (conf["a"]["b"]...), at least one of those should be added.
        REQUIRE(settings.getInt("height") == 576);
        REQUIRE(settings.getInt("renderDist") == 3);
        REQUIRE(settings.getInt("volume") == 100);

    }

}
