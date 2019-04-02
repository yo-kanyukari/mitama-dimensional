#ifndef MITAMA_DIMENSIONAL_DERIVED_UNITS_MOLAR_VOLUME_HPP
#define MITAMA_DIMENSIONAL_DERIVED_UNITS_MOLAR_VOLUME_HPP
#include "../si_units/all.hpp"
#include "../quantity.hpp"
#include "../io.hpp"


namespace mitama::si {
using molar_volume_t = decltype(meter<3> / mol<>);

inline constexpr molar_volume_t molar_volume{};
}

namespace mitama {
template <> struct abbreviation<si::molar_volume_t> { static constexpr char str[] = "m^3/mol"; };
}
#endif