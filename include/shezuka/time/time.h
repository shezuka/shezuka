#ifndef MEMORY_TIME_H
#define MEMORY_TIME_H

namespace shezuka {
    namespace time {
        // ===> UNIX Timestamp <===
        long timestamp() noexcept; // in seconds
        long timestamp_milliseconds() noexcept;
        long timestamp_nanoseconds() noexcept;
    }
}

#endif //MEMORY_TIME_H
