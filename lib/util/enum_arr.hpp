#pragma once

#include "util/cast.hpp"

namespace flap::lib::util {

template <class E, class V, size_t S = underlying_cast(E::COUNT_)>
class EnumArr {
 public:
    static constexpr auto static_size = S;

    template <class... Vs>
    constexpr EnumArr(Vs&&... vs) : m_arr{std::forward<Vs>(vs)...} {}

    constexpr V& operator[](E e) { return m_arr.at(underlying_cast(e)); }
    constexpr const V& operator[](E e) const {
        return m_arr.at(underlying_cast(e));
    }

    constexpr size_t size() const noexcept { return S; }

 private:
    std::array<V, S> m_arr;
};

namespace detail {

template <class E, class V, class F, class S, class... Ts>
constexpr void do_assign(EnumArr<E, V>& e, F&& f, S&& s, Ts&&... ts) {
    e[std::forward<F>(f)] = std::forward<S>(s);
    if constexpr (sizeof...(Ts)) {
        do_assign(e, std::forward<Ts>(ts)...);
    }
}
}  // namespace detail

template <class E, class V, class... Ts>
constexpr EnumArr<E, V> make_enum_arr(Ts&&... ts) {
    EnumArr<E, V> ea{};
    detail::do_assign(ea, std::forward<Ts>(ts)...);
    return ea;
}
}  // namespace flap::lib::util
