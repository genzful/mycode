#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include "database.hpp"
#include <string>
#include <cstring>

using namespace std;

const int LISTENPORT = 7252;        // port for listen
const int BUFFER_SIZE = 1024;       // buffer size
const int MAX_CONNECTIONS = 10;     // max connection

// func of logging
void error_log(const string& err) {}

class Server {
private:
    int server_fd;                   // descriptor
    int client2;                     // client
    struct sockaddr_in server_addr;  // address
    // Theme render;
public:
    Server() : server_fd(-1) {}

    void start() {
        // creating of socket
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0) {
            error_log("cant create socket");
            exit(1);
        }

        int opt = 1;
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            error_log("error of setting socket");
            close(server_fd);
            exit(1);
        }

        server_addr.sin_family = AF_INET;              // IPv4
        server_addr.sin_port = htons(LISTENPORT);      // port
        server_addr.sin_addr.s_addr = INADDR_ANY;      // any ip

        if (bind(server_fd, reinterpret_cast<struct sockaddr*>(&server_addr),
                sizeof(server_addr)) < 0) {
            error_log("cant connet socket");
            close(server_fd);
            exit(1);
        }

        // now we listen
        if (listen(server_fd, MAX_CONNECTIONS) < 0) {
            error_log("cant listen");
            close(server_fd);
            exit(1);
        }

        // main cycle
        while (true) {
            struct sockaddr_in client_addr; // ip of client
            socklen_t client_len = sizeof(client_addr);
            
            int client_fd = accept(server_fd, 
                                  reinterpret_cast<struct sockaddr*>(&client_addr),
                                  &client_len);
            
            if (client_fd < 0) {
                error_log("cant handle client");
                continue;
            }

            //      inet_ntoa(client_addr.sin_addr)
            //      ntohs(client_addr.sin_port)

            handleClient(client_fd);
            
            close(client_fd);
        }
    }

    void handleClient(int client_fd) {
        const char* welcome_msg = "welcome to genzat\n";
        send(client_fd, welcome_msg, strlen(welcome_msg), 0);
        
        while (true) {
            char buffer[BUFFER_SIZE];
            memset(buffer, 0, BUFFER_SIZE);
            
            int bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
            
            if (bytes_received <= 0) {
                break;
            }
            
            buffer[bytes_received] = '\0';
            send(client_fd, buffer, bytes_received, 0);
        }
    }

    ~Server() {
        if (server_fd >= 0) {
            close(server_fd);
        }
    }
};

int main() {
    Server server;
    server.start();
    return 0;
}