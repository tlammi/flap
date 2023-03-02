#pragma once

#include <flap/ast/node.hpp>
namespace flap::ast {
namespace detail {

template <class T, class Var>
struct is_in_variant : std::false_type {};

template <class T, class... Ts>
struct is_in_variant<T, std::variant<T, Ts...>> : std::true_type {};

template <class T, class F, class... Ts>
struct is_in_variant<T, std::variant<F, Ts...>>
    : is_in_variant<T, std::variant<Ts...>> {};

template <class T, class Var>
constexpr bool is_in_variant_v =
    is_in_variant<T, std::remove_cvref_t<Var>>::value;

template <class First, class... Ts, class Var>
constexpr bool nested_holds(const Var& var) {
    if constexpr (is_in_variant_v<First, Var>) {
        if constexpr (!sizeof...(Ts)) {
            return std::holds_alternative<First>(var);
        } else {
            return nested_holds<Ts...>(std::get<First>(var));
        }
    } else {
        return nested_holds<Ts...>(var);
    }
}

template <class First, class... Ts, class Var>
constexpr auto nested_get(Var&& var) {
    if constexpr (is_in_variant_v<First, Var>) {
        if constexpr (!sizeof...(Ts)) {
            return std::get<First>(std::forward<Var>(var));
        } else {
            return nested_get<Ts...>(std::get<First>(std::forward<Var>(var)));
        }
    } else {
        return nested_get<Ts...>(std::forward<Var>(var));
    }
}

}  // namespace detail

#define DEF_IS(name, ...)                                 \
    template <class... Ts>                                \
    constexpr bool name(const std::variant<Ts...>& var) { \
        return detail::nested_holds<__VA_ARGS__>(var);    \
    }

DEF_IS(is_int_lit, Expr, IntLit)
DEF_IS(is_expr, Expr)

#undef DEF_IS

#define DEF_GET(name, ...)                                              \
    template <class Var>                                                \
    constexpr auto name(Var&& var) {                                    \
        return detail::nested_get<__VA_ARGS__>(std::forward<Var>(var)); \
    }

DEF_GET(get_int_lit, Expr, IntLit);
#undef DEF_GET

}  // namespace flap::ast