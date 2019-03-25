#include <shezuka/network/TcpListener.h>

#include <cstring>

namespace shezuka {
    namespace network {
        TcpListener::~TcpListener() = default;

        void TcpListener::open() {
            if (is_open()) close();

            _descriptor = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (_descriptor == -1) {
                close();
                return;
            }

            int reuse_opt = 1;
            if (::setsockopt(_descriptor, SOL_SOCKET, SO_REUSEPORT, &reuse_opt, sizeof(decltype(reuse_opt)))) {
                close();
                return;
            }

            _addr = new struct sockaddr_in;
            ::bzero(_addr, sizeof(decltype(*_addr)));
            _addr->sin_family = AF_INET;
            _addr->sin_port = ::htons(_port);
            _addr->sin_addr.s_addr = INADDR_ANY;

            if (::bind(_descriptor, this->sockaddr_ptr(), sizeof(*_addr)) || ::listen(_descriptor, 100)) {
                close();
                return;
            }
        }
    }
}
