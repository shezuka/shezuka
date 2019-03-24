#ifndef MEMORY_SOCKETCLIENT_H
#define MEMORY_SOCKETCLIENT_H

#include "Socket.h"

namespace shezuka {
    namespace network {
        class SocketClient: public Socket {
        public:
            ~SocketClient() override;
        };
    }
}

#endif //MEMORY_SOCKETCLIENT_H
