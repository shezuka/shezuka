#include <shezuka/strings/explode.h>

#include <cstring>

namespace shezuka {
    namespace strings {
        char *exploder::allocate_zero_memory(size_t size) noexcept {
            char *mem = new char[size];
            bzero(mem, size);
            return mem;
        }

        char *exploder::copy_memory(const char *src, char *dest, size_t size) noexcept {
            if (!dest) dest = allocate_zero_memory(size);
            memcpy(dest, src, size);
            return dest;
        }

        size_t exploder::allocate_result_size(char ***result, size_t used_size, size_t current_size,
                                              size_t requested_size) noexcept {
            if (used_size < current_size && current_size <= requested_size) return current_size;

            if (!*result) {
                (*result) = new char *[requested_size];
                bzero(*result, requested_size);
                return requested_size;
            }

            char **tmp = *result;
            *result = new char *[requested_size];
            for (size_t i = 0; i < requested_size; i++) {
                *((*result) + i) = *(tmp + i);
            }
            delete[]tmp;

            return requested_size;
        }

        exploder::exploder(const char *src, size_t src_size, char const *delim, size_t delim_size) noexcept {
            _src = copy_memory(src, nullptr, src_size);
            _src_size = src_size;

            _delim = copy_memory(delim, _delim, delim_size);
            _delim_size = delim_size;
        }

        exploder::exploder(exploder &&other) noexcept {
            _src            = other._src;
            _src_size       = other._src_size;
            _delim          = other._delim;
            _delim_size     = other._delim_size;
            _result         = other._result;
            _result_size    = other._result_size;

            other._src = nullptr;
            other._delim = nullptr;
            other._result = nullptr;
        }

        exploder::~exploder() noexcept {
            if (_src) delete[]_src;
            if (_delim) delete[]_delim;
            if (_result) delete[]_result;
        }

        exploder *exploder::process() noexcept {
            char *src_pointer = _src;
            char *delim_pointer = nullptr;
            size_t src_pos = 0;
            size_t result_current_size = 0;

            while (src_pos < _src_size) {
                for (size_t i = 0; i < _delim_size && (i + src_pos) < _src_size; i++) {
                    if (*(_src + src_pos + i) != *(_delim + i)) {
                        delim_pointer = nullptr;
                        break;
                    }

                    delim_pointer = (_src + src_pos);
                }

                if (delim_pointer) {
                    *delim_pointer = 0;
                    if (!strlen(src_pointer)) {
                        src_pointer = _src + src_pos + _delim_size;
                        continue;
                    }

                    result_current_size = allocate_result_size(&_result, _result_size, result_current_size,
                                                               _result_size + 20);
                    _result[_result_size++] = src_pointer;
                    src_pointer = _src + src_pos + _delim_size;
                } else if (src_pos + 1 == _src_size && strlen(src_pointer)) {
                    result_current_size = allocate_result_size(&_result, _result_size, result_current_size,
                                                               _result_size + 1);
                    _result[_result_size++] = src_pointer;
                }

                src_pos++;
            }

            return this;
        }

        size_t exploder::size() const noexcept {
            return _result_size;
        }

        const char *exploder::operator[](size_t n) const noexcept {
            return *(_result + n);
        }

        const char *exploder::at(size_t n) const noexcept {
            return (*this)[n];
        }

        exploder explode(const char *str, const char *delim) noexcept {
            if (!str || !delim) return exploder{};
            exploder e{str, strlen(str) + 1, delim, strlen(delim)};
            e.process();
            return e;
        }

        exploder explode(const std::string &str, const char *delim) noexcept {
            return explode(str.c_str(), delim);
        }
    }
}