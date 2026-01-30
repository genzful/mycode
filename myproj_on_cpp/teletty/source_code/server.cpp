#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include "form.hpp"
#include <string>
#include <cstring>

using namespace std;

const int LISTENPORT = 7252;
const int BUFFER = 1024;

void error_log(const string& err) {}

class Server {
private:
    struct sockaddr_in server_addr;
    int client;
    int server = socket(AF_INET, SOCK_STREAM, 0);
public:
    Server() {}

    void start() {
        struct sockaddr_in server_addr;
        int client;
        int server = socket(AF_INET, SOCK_STREAM, 0);
        if (server < 0) {
            error_log("error of creating of socket");
            exit(1);
        }

        server_addr.sin_port = htons(LISTENPORT);
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        
        int binding = bind(server, reinterpret_cast<struct sockaddr*>(&server_addr),
            sizeof(server_addr));

        if (binding < 0) {
        error_log("cannot bind socket for server");
        exit(1);
        }

        socklen_t size = sizeof(server_addr);
        listen(server, 1);

        client = accept(server, reinterpret_cast<struct sockaddr*>(&server_addr), &size);
        if (server < 0) {
            error_log("cant accept");
        }

        char buffer[BUFFER];
        while (server > 0) {
            send(server, "some text", BUFFER, 0);
        }
    }

    ~Server() {
        close(server);
        close(client);
    }
};

int main() {
    Server server;
    server.start();
    return 0;
}