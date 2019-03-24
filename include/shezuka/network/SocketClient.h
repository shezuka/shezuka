#ifndef MEMORY_SOCKETCLIENT_H
#define MEMORY_SOCKETCLIENT_H

#include <string>
#include "Socket.h"
#include "SocketListener.h"

namespace shezuka {
    namespace network {
        class SocketListener;

        class SocketClient : public Socket {
        protected:
            std::string _hostname;

            void normilize_port_by_address();

        public:
            ~SocketClient() override;

            virtual void set_hostname(const char *hostname);

            virtual void set_hostname(const std::string &hostname);

            virtual void connect();

            virtual void connect(const char *hostname, ushort port);

            virtual void connect(const std::string &hostname, ushort port);

            virtual void accept(const SocketListener *listener) = 0;

            virtual ssize_t read(char *buff, size_t buff_size) = 0;

            virtual ssize_t send(const char *data, size_t data_size) = 0;
        };
    }
}

#endif //MEMORY_SOCKETCLIENT_H
