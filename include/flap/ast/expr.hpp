#pragma once

#include <variant>
namespace flap::ast {

class BinOp;
class UnOp;
class IntLit;
class IdenExpr;
class FuncCall;

template <class... Ts>
using Var = std::variant<const Ts*...>;

/**
 * Expression type
 * */
using Expr = Var<BinOp, UnOp, IntLit, IdenExpr, FuncCall>;

}  // namespace flap::ast
