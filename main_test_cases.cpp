#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

int add(int a, int b) {
    return a + b;
}

TEST_CASE("Addition works", "[math]") {
    REQUIRE(add(1, 1) == 3);
    REQUIRE(add(-1, -1) == -2);
}
