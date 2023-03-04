#pragma once

namespace flap {

template <class F, class... Ts>
constexpr bool any_of_eq(const F& f, const Ts&... ts) {
    return ((f == ts) || ...);
}

template <class F, class... Ts>
constexpr bool none_of_eq(const F& f, const Ts&&... ts) {
    return !any_of_eq(f, ts...);
}

template <class F, class... Ts>
constexpr bool all_of_eq(const F& f, const Ts&... ts) {
    return ((f == ts) && ...);
}

}  // namespace flap
