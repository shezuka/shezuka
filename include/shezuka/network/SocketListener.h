#ifndef MEMORY_SERVERSOCKET_H
#define MEMORY_SERVERSOCKET_H

#include "Socket.h"

namespace shezuka {
    namespace network {
        class SocketListener: public Socket {
        public:
            ~SocketListener() override = 0;
        };
    }
}

#endif //MEMORY_SERVERSOCKET_H
