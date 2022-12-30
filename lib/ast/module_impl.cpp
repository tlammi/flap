#include "ast/module_impl.hpp"

#include <flap/consumer.hpp>
namespace flap::ast {
void ModuleImpl::accept(Consumer& consumer) const noexcept {
    consumer.consume(*this);
    for (const auto& f : m_funcs) {
        f->accept(consumer);
    }
}
}  // namespace flap::ast
