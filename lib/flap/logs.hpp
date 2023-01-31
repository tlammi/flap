#pragma once

#include <iostream>

namespace flap {
namespace logs {

extern std::ostream* log_stream;

class LogCtx {
 public:
    LogCtx(std::ostream& str) : m_str{str} {}
    ~LogCtx() { m_str << '\n'; }
    template <class T>
    const LogCtx& operator<<(T&& t) const {
        m_str << std::forward<T>(t);
        return *this;
    }

 private:
    std::ostream& m_str;
};

#define DEBUG                                            \
    if (::flap::logs::log_stream) ::flap::logs::LogCtx { \
            *::flap::logs::log_stream                    \
        }

}  // namespace logs

void set_stream(std::ostream* stream);
}  // namespace flap

