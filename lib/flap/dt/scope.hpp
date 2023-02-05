#pragma once

#include <algorithm>
#include <map>
#include <stdexcept>

namespace flap::dt {

template <class K, class V>
class Scope {
 public:
    explicit Scope(const Scope* parent = nullptr) : m_parent{parent} {}

    Scope(const Scope&) = delete;
    Scope& operator=(const Scope&) = delete;

    Scope(Scope&&) = delete;
    Scope& operator=(Scope&&) = delete;

    ~Scope() = default;

    template <class K2>
    const V& at(const K2& key) const {
        auto iter =
            std::find_if(m_map.begin(), m_map.end(), [&](const auto pair) {
                const auto& [k, _] = pair;
                return k == key;
            });
        if (iter != m_map.end()) return iter->second;
        if (m_parent) return m_parent->at(key);
        throw std::runtime_error("at()");
    }

    template <class K2>
    V& add(K2&& key) {
        return m_map[K{std::forward<K2>(key)}];
    }

    template <class K2>
    [[nodiscard]] bool contains(const K2& key) const noexcept {
        auto iter =
            std::find_if(m_map.begin(), m_map.end(), [&](const auto pair) {
                const auto& [k, _] = pair;
                return k == key;
            });
        if (iter != m_map.end()) return true;
        if (m_parent) return m_parent->contains(key);
        return false;
    }

 private:
    std::map<K, V, std::less<>> m_map{};
    const Scope* m_parent{nullptr};
};

}  // namespace flap::dt
