#include <shezuka/network/SocketClient.h>

namespace shezuka {
    namespace network {
        SocketClient::~SocketClient() = default;

        void SocketClient::normilize_port_by_address() {
            _port = ::htons(_addr->sin_port);
        }

        void SocketClient::connect() {
            this->open();
        }

        void SocketClient::set_hostname(const char *hostname) {
            _hostname = hostname;
        }

        void SocketClient::set_hostname(const std::string &hostname) {
            _hostname = hostname;
        }

        void SocketClient::connect(const char *hostname, ushort port) {
            set_hostname(hostname);
            set_port(port);
            connect();
        }

        void SocketClient::connect(const std::string &hostname, ushort port) {
            set_hostname(hostname);
            set_port(port);
            connect();
        }
    }
}