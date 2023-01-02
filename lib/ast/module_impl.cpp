#include "ast/module_impl.hpp"

#include <flap/consumer.hpp>
namespace flap::ast {

void ModuleImpl::accept(Consumer& consumer) const noexcept {
    auto recurse = consumer.consume(*this);
    if (recurse == Recurse::Yes)
        for (const auto& f : m_funcs) {
            f->accept(consumer);
        }
}
}  // namespace flap::ast
