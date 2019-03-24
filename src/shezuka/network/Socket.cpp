#include <shezuka/network/Socket.h>

#include <unistd.h>

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
            return reinterpret_cast<struct sockaddr*>(_addr);
        }


    }
}
