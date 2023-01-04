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
#include <stack>

namespace flap::llvm {

class ConsumerImpl final : public Consumer {
 public:
    Recurse consume(const ast::Function& func) override {
        auto* ft =
            ::llvm::FunctionType::get(::llvm::Type::getInt32Ty(m_ctx), false);
        m_func = ::llvm::Function::Create(ft, ::llvm::Function::ExternalLinkage,
                                          func.name(), &m_mod);
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

    Recurse consume(const ast::FunctionCall& call) override {
        auto* tgt = m_mod.getFunction(call.name());
        if (!tgt) throw std::runtime_error("Unknown function name");
        if (tgt->arg_size())
            throw std::runtime_error("Parameters not supported yet");
        auto* val = m_builder.CreateCall(tgt);
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
};

std::unique_ptr<Consumer> make_consumer() {
    return std::make_unique<ConsumerImpl>();
}

}  // namespace flap::llvm
