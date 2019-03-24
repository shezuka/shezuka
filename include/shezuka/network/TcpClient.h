#ifndef MEMORY_TCPCLIENT_H
#define MEMORY_TCPCLIENT_H

#include "SocketClient.h"
#include "SocketListener.h"

namespace shezuka {
    namespace network {
        class TcpClient: public SocketClient {


        public:
            TcpClient() = default;
            TcpClient(int descriptor, struct sockaddr_in *addr);

            ~TcpClient() override = default;

            void open() override;

            void accept(const SocketListener *listener) override;
        };
    }
}

#endif //MEMORY_TCPCLIENT_H
