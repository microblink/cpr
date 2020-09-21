#include "cpr/timeout.h"

#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace cpr {

long Timeout::Milliseconds() const {
    static_assert(std::is_same<std::chrono::milliseconds, decltype(ms)>::value,
                  "Following casting expects milliseconds.");

#if __cpp_exceptions >= 199711L
    if (ms.count() > std::numeric_limits<long>::max()) {
        throw std::overflow_error(
                "cpr::Timeout: timeout value overflow: " + std::to_string(ms.count()) + " ms.");
    }
    if (ms.count() < std::numeric_limits<long>::min()) {
        throw std::underflow_error(
                "cpr::Timeout: timeout value underflow: " + std::to_string(ms.count()) + " ms.");
    }
#endif

    return static_cast<long>(ms.count());
}

} // namespace cpr
