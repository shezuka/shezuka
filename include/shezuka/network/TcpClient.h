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

            ssize_t read(char *buff, size_t buff_size) override;

            ssize_t send(const char *data, size_t data_size) override;
        };
    }
}

#endif //MEMORY_TCPCLIENT_H
