#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <dimensional/derived_units/momentum.hpp>
#include "../format_io_common.hpp"

TEST_CASE("momentum format test", "[quantity][abbreviation]") {
  REQUIRE(fmt(1 | si::momentum_t{}) == "1 [N·s]");
}
TEST_CASE("momentum quantifier format test", "[quantity][abbreviation]") {
  REQUIRE(fmt(1 | si::momentum) == "1 [N·s]");
}
TEST_CASE("momentum type test", "[quantity][abbreviation]") {
  REQUIRE(mitama::is_same_dimensional_v<std::decay_t<decltype(1|si::momentum)>, mitama::quantity_t<std::decay_t<decltype(meters*kilograms*second<-1>)>>>);
}
