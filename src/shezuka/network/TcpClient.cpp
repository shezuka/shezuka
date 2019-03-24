#include <shezuka/network/TcpClient.h>
#include <shezuka/network/TcpListener.h>
#include <strings.h>
#include <netdb.h>

namespace shezuka {
    namespace network {
        void TcpClient::open() {
            close();

            _descriptor = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (_descriptor == -1) {
                close();
                return;
            }

            struct hostent *server = gethostbyname(_hostname.c_str());
            if (!server) {
                close();
                return;
            }

            _addr = new struct sockaddr_in;
            socklen_t len = sizeof(decltype(*_addr));
            ::bzero(_addr, len);
            _addr->sin_family = AF_INET;
            _addr->sin_port = ::htons(_port);
            ::bcopy(*server->h_addr_list, (char*)&_addr->sin_addr.s_addr, server->h_length);

            if (::connect(_descriptor, this->sockaddr_ptr(), len) == -1) {
                close();
                return;
            }
        }

        TcpClient::TcpClient(int descriptor, struct sockaddr_in *addr) {
            this->_descriptor = descriptor;
            this->_addr = addr;

            normilize_port_by_address();
        }

        void TcpClient::accept(const SocketListener *listener) {
            this->close();

            _addr = new struct sockaddr_in;
            socklen_t len = sizeof(decltype(*_addr));
            ::bzero(_addr, len);
            _descriptor = ::accept(listener->descriptor(), reinterpret_cast<sockaddr *>(_addr), &len);
            if (is_open()) {
                normilize_port_by_address();
            }
        }

        ssize_t TcpClient::read(char *buff, size_t buff_size) {
            auto res = ::recv(_descriptor, buff, buff_size, 0);
            if (res <= 0) close();
            return res;
        }

        ssize_t TcpClient::send(const char *data, size_t data_size) {
            auto res = ::send(_descriptor, data, data_size, 0);
            if (res <= 0) close();
            return res;
        }
    }
}
