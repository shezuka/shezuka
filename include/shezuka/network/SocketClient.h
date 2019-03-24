#ifndef MEMORY_SOCKETCLIENT_H
#define MEMORY_SOCKETCLIENT_H

#include <string>
#include "Socket.h"

namespace shezuka {
    namespace network {
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
        };
    }
}

#endif //MEMORY_SOCKETCLIENT_H
