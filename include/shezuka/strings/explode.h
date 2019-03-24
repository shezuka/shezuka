#ifndef MEMORY_EXPLODE_H
#define MEMORY_EXPLODE_H

#include <cstddef>
#include <memory>
#include <string>

namespace shezuka {
    namespace strings {
        class exploder {
            char *_src = nullptr;
            size_t _src_size = 0;

            char *_delim = nullptr;
            size_t _delim_size = 0;

            char **_result = nullptr;
            size_t _result_size = 0;

        private:
            inline static char *allocate_zero_memory(size_t size) noexcept;

            inline static char *copy_memory(const char *src, char *dest, size_t size) noexcept;

            inline static size_t
            allocate_result_size(char ***result, size_t used_size, size_t current_size, size_t requested_size) noexcept;

        public:
            exploder() = default;

            exploder(exploder &&other) noexcept;

            exploder(const char *src, size_t src_size, char const *delim, size_t delim_size) noexcept;

            ~exploder() noexcept;

            exploder *process() noexcept;

            size_t size() const noexcept;

            const char *operator[](size_t n) const noexcept;

            const char *at(size_t n) const noexcept;
        };

        exploder explode(const char *str, const char *delim) noexcept;

        exploder explode(const std::string &str, const char *delim) noexcept;
    }
}

#endif //MEMORY_EXPLODE_H
