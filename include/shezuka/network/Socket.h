#ifndef MEMORY_SOCKET_H
#define MEMORY_SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>

namespace shezuka {
    namespace network {
        class Socket {
        protected:
            int _descriptor = 0;
            ushort _port = 0;
            struct sockaddr_in *_addr = nullptr;

            struct sockaddr *sockaddr_ptr() const;

        public:
            virtual ~Socket() = 0;

            virtual bool is_open() const noexcept;

            virtual void open() = 0;

            void close();

            virtual int descriptor() const;

            virtual ushort port() const;

            virtual void set_port(ushort port);

            virtual void print_last_error() const noexcept;

            virtual void throw_last_error() const;
        };
    }
}

#endif //MEMORY_SOCKET_H
