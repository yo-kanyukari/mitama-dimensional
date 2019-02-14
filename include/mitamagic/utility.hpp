#pragma once
#include <ratio>
#include <type_traits>
// Type List Modules
namespace mitama::mitamagic {
template < class... > inline constexpr bool always_false_v = false;

template <class> struct is_rational : std::false_type {};

template <std::intmax_t N, std::intmax_t D>
struct is_rational<std::ratio<N, D>> : std::true_type {};

template <class T> inline constexpr bool is_rational_v = is_rational<T>::value;

template <class R1, class R2>
using ratio_max = std::conditional_t<std::ratio_greater_v<R1, R2>, R1, R2>;

template <class R1, class R2>
using ratio_min = std::conditional_t<std::ratio_less_v<R1, R2>, R1, R2>;

template <class...> struct type_list {}; // Type List

template <class...> struct tlist_cat; // List concatenate: primary

template <template <class...> class Pack, class... Elems>
struct tlist_cat<Pack<Elems...>> {
  using type = Pack<Elems...>;
}; // List concatenate: binary

template <template <class...> class Pack, class... Left, class... Right>
struct tlist_cat<Pack<Left...>, Pack<Right...>> {
  using type = Pack<Left..., Right...>;
}; // List concatenate: binary

template <class Pack1st, class Pack2nd, class... PackTail>
struct tlist_cat<Pack1st, Pack2nd, PackTail...>
    : tlist_cat<typename tlist_cat<Pack1st, Pack2nd>::type, PackTail...> {
}; // List concatenate: variadic(recursive class)

template <class... Packs>
using tlist_cat_t = typename tlist_cat<Packs...>::type; // alias template

template <std::size_t I, class T> struct tlist_element;

// recursive case
template <std::size_t I, template <class...> class Pack, class Head,
          class... Tail>
struct tlist_element<I, Pack<Head, Tail...>>
    : tlist_element<I - 1, Pack<Tail...>> {
  static_assert(I <= sizeof...(Tail), "pack out of range.");
};

// base case
template <template <class...> class Pack, class Head, class... Tail>
struct tlist_element<0, Pack<Head, Tail...>> {
  using type = Head;
};

template <std::size_t N, typename Pack>
using tlist_element_t = typename tlist_element<N, Pack>::type;

template <template <class> class, class, class> struct tlist_filter_impl;

template <template <class> class Pred, template <class...> class tPack,
          class... Result, class Head, class... Tail>
struct tlist_filter_impl<Pred, tPack<Head, Tail...>, tPack<Result...>>
    : std::conditional_t<
          Pred<Head>::value,
          tlist_filter_impl<Pred, tPack<Tail...>, tPack<Result...>>,
          tlist_filter_impl<Pred, tPack<Tail...>, tPack<Result..., Head>>> {};

template <template <class> class Pred, template <class...> class Pack,
          class... Result>
struct tlist_filter_impl<Pred, Pack<>, Pack<Result...>> {
  using type = Pack<Result...>;
};

template <template <class> class Pred, template <class...> class Pack>
struct tlist_filter_impl<Pred, Pack<>, Pack<>> {
  using type = Pack<>;
};

template <template <class> class, class> struct tlist_filter;

template <template <class> class Pred, template <class...> class Pack,
          class... Types>
struct tlist_filter<Pred, Pack<Types...>> {
  using type = typename tlist_filter_impl<Pred, Pack<Types...>, Pack<>>::type;
};

template <template <class> class Pred, class Pack>
using tlist_filter_t = typename tlist_filter<Pred, Pack>::type;

template <template <class> class, class> struct tlist_all_match_if;

template <template <class> class Pred, template <class...> class tPack,
          class... Args>
struct tlist_all_match_if<Pred, tPack<Args...>>
    : std::conjunction<Pred<Args>...> {};

template <template <class> class Pred, class TypeList>
inline constexpr bool tlist_all_match_if_v =
    tlist_all_match_if<Pred, TypeList>::value;

template <template <class...> class, class> struct repack;

template <template <class...> class Pack, template <class...> class _,
          class... Elems>
struct repack<Pack, _<Elems...>> {
  using type = Pack<Elems...>;
};

template <template <class...> class P, class P_>
using repack_t = typename repack<P, P_>::type;
} // namespace mitama::mitamagic
