#include <shezuka/network/TcpListener.h>
#include <shezuka/network/TcpClient.h>
#include <stdexcept>
#include <thread>

#define PORT 20000

using namespace std;
using TcpListener = shezuka::network::TcpListener;
using TcpClient = shezuka::network::TcpClient;

void server_thread_handler() {
    TcpListener listener;
    listener.listen(PORT);
    if (!listener.is_open()) listener.throw_last_error();

    TcpClient accepted;
    accepted.accept(&listener);
    if (!accepted.is_open()) accepted.throw_last_error();
}

void client_thread_handler() {
    TcpClient client;
    client.connect("127.0.0.1", PORT);
}

int main() {
    thread server_thread(server_thread_handler);
    client_thread_handler();

    server_thread.join();

    return 0;
}