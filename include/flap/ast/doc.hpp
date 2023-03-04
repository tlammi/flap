#pragma once

#include <flap/ast/func.hpp>
#include <flap/types/scope.hpp>

namespace flap::ast {

/**
 * A single program document (file)
 * */
struct Doc {
    ScopePtr<Func> functions{make_scope<Func>()};
};
}  // namespace flap::ast
