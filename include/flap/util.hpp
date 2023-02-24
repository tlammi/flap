#pragma once

namespace flap {

namespace detail {

template <class... Fns>
struct Matcher : Fns... {
    using Fns::operator()...;
};

template <class... Fns>
Matcher(Fns...) -> Matcher<Fns...>;

}  // namespace detail

template <class Var, class... Fns>
auto match(Var&& v, Fns&&... fns) {
    return std::visit(detail::Matcher{std::forward<Fns>(fns)...},
                      std::forward<Var>(v));
}

}  // namespace flap
