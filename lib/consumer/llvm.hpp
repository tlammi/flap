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

#include <flap/consumer.hpp>

namespace flap::consumer {

class Llvm final : public Consumer {
 public:
    void consume(const ast::Module& module_) override {}
    void consume(const ast::Function& func) override {
        auto* ft =
            llvm::FunctionType::get(llvm::Type::getInt32Ty(m_ctx), false);
        m_func = llvm::Function::Create(ft, llvm::Function::ExternalLinkage,
                                        func.name(), &m_mod);
        auto* bb = llvm::BasicBlock::Create(m_ctx, "entry", m_func);
        m_builder.SetInsertPoint(bb);
    }
    void consume(const ast::IntLiteral& lit) override {
        auto* val = llvm::ConstantInt::get(
            m_ctx, llvm::APInt(32, lit.value(), lit.radix()));
        m_builder.CreateRet(val);
        llvm::verifyFunction(*m_func);

        // m_mod.print(llvm::errs(), nullptr);
        m_mod.print(llvm::outs(), nullptr);
    }

 private:
    llvm::LLVMContext m_ctx{};
    llvm::Module m_mod{"flap WIP", m_ctx};
    llvm::IRBuilder<> m_builder{m_ctx};
    llvm::Function* m_func{};
};

}  // namespace flap::consumer
