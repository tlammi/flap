#pragma once

namespace flap::util {

template <size_t N, class T, class... Ts>
struct nth_of : nth_of<N - 1, Ts...> {};

template <class T, class... Ts>
struct nth_of<0, T, Ts...> {
    using type = T;
};

template <size_t N, class... Ts>
using nth_of_t = typename nth_of<N, Ts...>::type;

template <class... Ts>
using first_of_t = nth_of_t<0, Ts...>;

}  // namespace flap::util

