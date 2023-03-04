#pragma once

#include <map>
#include <memory>

namespace flap {
template <class V>
class Scope;

template <class V>
using ScopePtr = std::shared_ptr<Scope<V>>;

template <class V>
class Scope {
    friend ScopePtr<V> make_scope<V>();
    friend ScopePtr<V> make_scope<V>(ScopePtr<V>);

 public:
    void insert(std::string_view key, V v) {
        m_map[std::string(key)] = std::move(v);
    }

    const V& at(std::string_view key) const {
        auto iter = m_map.find(key);
        if (iter != m_map.end()) return iter->second;
        if (m_parent) return m_parent->at(key);
        throw std::runtime_error("Scope::at()");
    }

    ScopePtr<V> parent() { return m_parent; }

    bool contains(std::string_view key) const noexcept {
        return m_map.find(key) != m_map.end();
    }

 private:
    Scope() = default;
    Scope(ScopePtr<V> parent) : m_parent{std::move(parent)} {}

    ScopePtr<V> m_parent{};
    std::map<std::string, V, std::less<>> m_map{};
};

template <class V>
ScopePtr<V> make_scope() {
    return ScopePtr<V>{new Scope<V>};
}

template <class V>
ScopePtr<V> make_scope(ScopePtr<V> p) {
    return ScopePtr<V>{new Scope<V>{std::move(p)}};
}
}  // namespace flap
