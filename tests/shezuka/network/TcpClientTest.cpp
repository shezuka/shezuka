#include <shezuka/network/TcpClient.h>

using TcpClient = shezuka::network::TcpClient;

int main() {
    TcpClient client;
    client.connect("google.com", 80);
    if (!client.is_open()) client.throw_last_error();
    client.close();
    return 0;
}