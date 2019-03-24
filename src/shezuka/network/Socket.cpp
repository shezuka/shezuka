#include <shezuka/network/Socket.h>

#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <stdexcept>

namespace shezuka {
    namespace network {
        Socket::~Socket() {
            this->close();
        }

        bool Socket::is_open() const noexcept {
            return _addr && _descriptor > 0;
        }

        ushort Socket::port() const {
            return _port;
        }

        void Socket::set_port(ushort port) {
            _port = port;
        }

        void Socket::close() {
            if (_descriptor > 0) {
                ::close(_descriptor);
                _descriptor = 0;
            }

            if (_addr) {
                delete _addr;
                _addr = nullptr;
            }
        }

        struct sockaddr *Socket::sockaddr_ptr() const {
            return reinterpret_cast<struct sockaddr *>(_addr);
        }

        void Socket::throw_last_error() const {
            throw std::runtime_error("socket error: " + std::string(strerror(errno)));
        }

        int Socket::descriptor() const {
            return _descriptor;
        }


    }
}
