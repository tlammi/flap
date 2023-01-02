#include "logs.hpp"

namespace flap {
namespace logs {

std::ostream* log_stream{&std::cerr};

}  // namespace logs
void set_log_stream(std::ostream* stream) { logs::log_stream = stream; }
}  // namespace flap
