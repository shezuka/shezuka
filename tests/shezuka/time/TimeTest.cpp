#include <shezuka/time/time.h>
#include <cassert>

using namespace shezuka::time;

int main() {
    auto seconds = timestamp();
    assert(seconds > 1e9L && seconds < 1e10L);

    auto milliseconds = timestamp_milliseconds();
    assert(milliseconds > 1e12L && milliseconds < 1e13L && milliseconds > seconds);

    auto nanoseconds = timestamp_nanoseconds();
    assert(nanoseconds > 1e18L && nanoseconds < 1e19L);

    return 0;
}
