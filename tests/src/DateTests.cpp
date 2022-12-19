#include "catch2/catch_test_macros.hpp"

#include "genesis/core/game/log/Date.hpp"

TEST_CASE("Ensure stringifying works correctly", "[Date][Core]") {
    genesis::Date timeOnly{
        -1, 0, 0,
        12, 12, 12
    };
    genesis::Date dateOnly {
        9, 6, 69,
        -1, 0, 0
    };
    genesis::Date full {
        9, 6, 69,
        12, 12, 12
    };
    REQUIRE(genesis::date2str(timeOnly) == "12:12:12");
    REQUIRE(genesis::date2str(dateOnly) == "69-6-9");
    REQUIRE(genesis::date2str(full) == "69-6-9, 12:12:12");
}

TEST_CASE("Ensure it's able to deal with literal garbage", "[Date][Core]") {
    genesis::Date shit {
        -1, 4, 4,
        -1, 0, 0
    };
    REQUIRE_THROWS([&]() {
        genesis::date2str(shit);
    }());
}
