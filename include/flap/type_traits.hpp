#pragma once

#include <variant>

namespace flap::type_traits {

template <class... Vs>
struct variant_merge {};
template <class... Ts>
struct variant_merge<std::variant<Ts...>> {
    using type = std::variant<Ts...>;
};
template <class... Ts1, class... Ts2, class... Vs>
struct variant_merge<std::variant<Ts1...>, std::variant<Ts2...>, Vs...> {
    using type =
        typename variant_merge<std::variant<Ts1..., Ts2...>, Vs...>::type;
};
/**
 * Concatenate variants to a single variant
 * */
template <class... Vs>
using variant_merge_t = typename variant_merge<Vs...>::type;

}  // namespace flap::type_traits
