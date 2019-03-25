#ifndef MEMORY_TCPLISTENER_H
#define MEMORY_TCPLISTENER_H

#include "SocketListener.h"

namespace shezuka {
    namespace network {
        class TcpListener: public SocketListener {
        public:
            ~TcpListener() override;

            void open() override;
        };
    }
}

#endif //MEMORY_TCPLISTENER_H
