#include <shezuka/network/TcpClient.h>
#include <shezuka/network/TcpListener.h>
#include <cassert>
#include <thread>
#include <string>

#define PORT 20000
#define BUFF_SIZE 1024
#define CLIENT_MESSAGE string("client message")
#define SERVER_MESSAGE string("server message")

using namespace std;
using TcpListener = shezuka::network::TcpListener;
using TcpClient = shezuka::network::TcpClient;

#define assert_socket_open(socket) \
if (!socket.is_open()) { socket.print_last_error(); assert(false); }

void server_thread_handler() {
    TcpListener listener;
    listener.listen(PORT);
    assert_socket_open(listener)

    TcpClient client;
    client.accept(&listener);
    assert_socket_open(client)

    char buff[BUFF_SIZE];
    ssize_t read_size = client.read(buff, BUFF_SIZE - 1);
    buff[read_size] = 0;
    assert(buff == CLIENT_MESSAGE);
    client.send(SERVER_MESSAGE.c_str(), SERVER_MESSAGE.size());
    this_thread::sleep_for(50ms);

    client.close();
    listener.close();
}

void client_thread_handler() {
    TcpClient client;
    this_thread::sleep_for(50ms);
    client.connect("127.0.0.1", PORT);
    assert_socket_open(client)
    client.send(CLIENT_MESSAGE.c_str(), CLIENT_MESSAGE.size());

    char buff[BUFF_SIZE];
    ssize_t read_size = client.read(buff, BUFF_SIZE - 1);
    buff[read_size] = 0;

    assert_socket_open(client)
    assert(buff == SERVER_MESSAGE);

    client.close();
}

int main() {
    thread server_thread(server_thread_handler);
    client_thread_handler();

    server_thread.join();

    return 0;
}