#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

#include <flap/llvm/consumer.hpp>
#include <map>
#include <stack>

namespace flap::llvm {

class ConsumerImpl final : public Consumer {
 public:
    Recurse consume(const ast::Function& func) override {
        ::llvm::FunctionType* ft{nullptr};
        auto params = func.params();
        if (params.empty()) {
            ft = ::llvm::FunctionType::get(::llvm::Type::getInt32Ty(m_ctx),
                                           false);
        } else {
            std::vector<::llvm::Type*> llvm_params(
                params.size(), ::llvm::Type::getInt32Ty(m_ctx));
            ft = ::llvm::FunctionType::get(::llvm::Type::getInt32Ty(m_ctx),
                                           llvm_params, false);
        }
        m_func = ::llvm::Function::Create(ft, ::llvm::Function::ExternalLinkage,
                                          func.name(), &m_mod);
        size_t idx = 0;
        for (auto& param : m_func->args()) {
            param.setName(params.at(idx)->name());
            m_vars[params.at(idx)->name()] = &param;
            ++idx;
        }
        auto* bb = ::llvm::BasicBlock::Create(m_ctx, "entry", m_func);
        m_builder.SetInsertPoint(bb);
        return Recurse::Yes;
    }

    Recurse consume(const ast::RetStmt& stmt) override {
        stmt.expr().accept(*this);
        m_builder.CreateRet(m_stack.top());
        m_stack.pop();
        return Recurse::No;
    }

    Recurse consume(const ast::VarDefStmt& stmt) override {
        stmt.expr().accept(*this);
        m_vars[stmt.name()] = m_stack.top();
        m_stack.pop();
        return Recurse::No;
    }

    Recurse consume(const ast::FunctionCall& call) override {
        auto* tgt = m_mod.getFunction(call.name());
        if (!tgt) throw std::runtime_error("Unknown function name");
        auto args = call.args();
        if (tgt->arg_size() != args.size())
            throw std::runtime_error("Wrong number of arguments");

        std::vector<::llvm::Value*> llvm_args{};
        llvm_args.reserve(args.size());
        for (const auto& arg : args) {
            arg->accept(*this);
            llvm_args.push_back(m_stack.top());
            m_stack.pop();
        }
        auto* val = m_builder.CreateCall(tgt, llvm_args);
        m_stack.push(val);
        return Recurse::No;
    }

    Recurse consume(const ast::BinaryOperator& op) override {
        op.lhs().accept(*this);
        auto lhs = m_stack.top();
        m_stack.pop();
        op.rhs().accept(*this);
        auto rhs = m_stack.top();
        m_stack.pop();
        if (op.oper() == "+") {
            auto* val = m_builder.CreateAdd(lhs, rhs);
            m_stack.push(val);
            return Recurse::No;
        }
        if (op.oper() == "-") {
            auto* val = m_builder.CreateSub(lhs, rhs);
            m_stack.push(val);
            return Recurse::No;
        }
        if (op.oper() == "*") {
            auto* val = m_builder.CreateMul(lhs, rhs);
            m_stack.push(val);
            return Recurse::No;
        }
        throw std::runtime_error("Unimplemented");
    }

    Recurse consume(const ast::IntLiteral& lit) override {
        auto* val = ::llvm::ConstantInt::get(
            m_ctx, ::llvm::APInt(32, lit.value(), lit.radix()));
        m_stack.push(val);
        return Recurse::Yes;
    }

    Recurse consume(const ast::IdentifierExpr& expr) override {
        m_stack.push(m_vars.at(expr.name()));
        return Recurse::No;
    }

    std::string llvm_ir() override {
        std::string out{};
        ::llvm::raw_string_ostream str{out};
        m_mod.print(str, nullptr);
        return out;
    }

 private:
    ::llvm::LLVMContext m_ctx{};
    ::llvm::Module m_mod{"flap WIP", m_ctx};
    ::llvm::IRBuilder<> m_builder{m_ctx};
    ::llvm::Function* m_func{};
    std::stack<::llvm::Value*> m_stack{};
    std::map<std::string_view, ::llvm::Value*> m_vars{};
};

std::unique_ptr<Consumer> make_consumer() {
    return std::make_unique<ConsumerImpl>();
}

}  // namespace flap::llvm
