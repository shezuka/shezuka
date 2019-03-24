#include <shezuka/network/SocketListener.h>

namespace shezuka {
    namespace network {
        SocketListener::~SocketListener() = default;

        void SocketListener::listen() {
            this->open();
        }

        void SocketListener::listen(ushort port) {
            set_port(port);
            this->listen();
        }
    }
}
