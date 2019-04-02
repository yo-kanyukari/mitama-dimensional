#ifndef MITAMA_DIMENSIONAL_DERIVED_UNITS_SPECIFIC_ANGULAR_MOMENTUM_HPP
#define MITAMA_DIMENSIONAL_DERIVED_UNITS_SPECIFIC_ANGULAR_MOMENTUM_HPP
#include "../si_units/all.hpp"
#include "../quantity.hpp"
#include "../io.hpp"


namespace mitama::si {
using specific_angular_momentum_t = decltype(meter<2> * second<-1>);

inline constexpr specific_angular_momentum_t specific_angular_momentum{};
}

namespace mitama {
template <> struct abbreviation<si::specific_angular_momentum_t> { static constexpr char str[] = "N·m·s/kg"; };
}
#endif