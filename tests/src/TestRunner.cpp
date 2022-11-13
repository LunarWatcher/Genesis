#define CATCH_CONFIG_RUNNER
#include "catch2/catch_session.hpp"
#include "genesis/rendering/Constants.hpp"

const bool genesis::Constants::isTest = true;

int main(int argc, const char* argv[]) {
    return Catch::Session().run(argc, argv);
}
