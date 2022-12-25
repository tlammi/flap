#pragma once

namespace flap::lib::util {

template <class E>
constexpr decltype(auto) underlying_cast(E e) {
    return static_cast<std::underlying_type_t<E>>(e);
}

template <class E>
constexpr decltype(auto) underlying_cast(std::underlying_type_t<E> t) {
    return static_cast<E>(t);
}

}  // namespace flap::lib::util
