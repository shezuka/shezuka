#ifndef MEMORY_ARRAYPOINTER_H
#define MEMORY_ARRAYPOINTER_H

#include <cstddef>
#include <strings.h>

namespace shezuka {
    namespace memory {
        template<typename T>
        class ArrayMemory {
            size_t _size = 0;
            T *_data = nullptr;

        private:
            void declare(size_t size) noexcept {
                if (_data == nullptr) {
                    _data = new T[size];
                    _size = size;
                    return;
                }

                T *tmp = _data;
                _data = new T[size];
                bzero(_data, size);
                for (size_t i = 0; i < size && i < _size; i++) {
                    _data[i] = tmp[i];
                }
                delete[]tmp;

                _size = size;
            }

        public:
            ~ArrayMemory() noexcept {
                if (_data) delete[]_data;
            }

            void reduce(size_t size) noexcept {
                declare((size > _size)
                        ? 0
                        : (_size - size));
            }

            void raise(size_t size) noexcept {
                declare(_size + size);
            }

            void set_size(size_t size) noexcept {
                declare(size);
            }

            size_t size() const noexcept {
                return _size;
            }

            bool equals(const T* other, size_t other_size) const noexcept {
                if (_size != other_size) return false;

                for (size_t i = 0; i < _size; i++) {
                    if (_data[i] != other[i]) return false;
                }

                return true;
            }

            T operator*() noexcept {
                return *_data;
            }

            T operator[](int index) noexcept {
                return _data[index];
            }

            T operator[](size_t index) noexcept {
                return _data[index];
            }

            explicit operator const T*() const noexcept {
                return _data;
            }

            explicit operator T*() noexcept {
                return _data;
            }
        };
    }
}

#endif //MEMORY_ARRAYPOINTER_H
