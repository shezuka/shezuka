#include <shezuka/time/time.h>

#include <chrono>
#include <ctime>

namespace shezuka {
    namespace time {
        using namespace std::chrono;

        long timestamp() noexcept {
            return static_cast<long>(std::time(nullptr));
        }

        long timestamp_milliseconds() noexcept {
            return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        }

        long timestamp_nanoseconds() noexcept {
            return duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
        }
    }
}