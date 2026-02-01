#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include "database.hpp"
#include <string>
#include <cstring>
#include <map>
#include <unordered_map>
#include <iostream>

using namespace std;

const int LISTENPORT = 7252;        // port for listen
const int BUFFER_SIZE = 1024;       // buffer size
const int MAX_CONNECTIONS = 1000;     // max connection
const string path_for_logs = "connections.log"; // path to logs of connections
const string path_to_err = "stderr.log"; // path to errors
const char* IP_FOR_LISTEN = "127.0.0.1";

// func of logging
void error_log(const string& err) {
    fstream fs;
    fs.open(path_to_err, fstream::out | fstream::app);
    fs << err << '\n';
    fs.close();
}

class Server {
private:
    unordered_map<string, int> connected;      // ip -> descriptor
    int server_fd;                   // descriptor
    int client2;                     // client
    struct sockaddr_in server_addr;  // address
    // Theme render;
public:
    Server() : server_fd(-1) {}

    void start() {
        // creating of socket - ИСПРАВЛЕНО!
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0) {
            error_log("Socket creation failed");
            return;
        }

        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(LISTENPORT);
        
        if (strcmp(IP_FOR_LISTEN, "0.0.0.0") == 0) {
            server_addr.sin_addr.s_addr = INADDR_ANY;
        } else {
            if (inet_pton(AF_INET, IP_FOR_LISTEN, &server_addr.sin_addr) <= 0) {
                error_log("Invalid IP address: " + string(IP_FOR_LISTEN));
                close(server_fd);
                return;
            }
        }

        if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            error_log("Bind failed");
            close(server_fd);
            return;
        }

        if (listen(server_fd, MAX_CONNECTIONS) < 0) {
            error_log("Listen failed");
            close(server_fd);
            return;
        }
        
        cout << "Server started on " << IP_FOR_LISTEN << ":" << LISTENPORT << endl;
    

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

            handleClient(client_fd);
            
            close(client_fd);
        }
    }

    void handleClient(int client_fd) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        if (getpeername(client_fd, (struct sockaddr*)&client_addr, &client_len) < 0) {
            error_log("Can't get client address");
            close(client_fd);
            return;
        }
        
        // get ip to str
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
        
        // save client
        connected[string(client_ip)] = client_fd;
        
        // send welcome
        const char* welcome_msg = "Welcome to genzat chat server!\nsend me your name: ";
        send(client_fd, welcome_msg, strlen(welcome_msg), 0);
        char name_buffer[BUFFER_SIZE];
        memset(name_buffer, 0, BUFFER_SIZE);
        int name_received = recv(client_fd, name_buffer, BUFFER_SIZE - 1, 0);
        
        cout << name_buffer << endl;
        printMapArrow();

        if (connected.size() > 1) {
            string clients_msg = "Connected to chat\n";
            send(client_fd, clients_msg.c_str(), clients_msg.length(), 0);
        }

        send(client_fd, "Waiting for other clients...\n", strlen("Waiting for other clients...\n"), 0);

        while (true) {
            char buffer[BUFFER_SIZE];
            memset(buffer, 0, BUFFER_SIZE);
            
            int bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
            
            if (bytes_received <= 0) {
                connected.erase(string(client_ip));
                break;
            }
            
            buffer[bytes_received] = '\0';
            
            if (buffer[bytes_received - 1] == '\n') {
                buffer[bytes_received - 1] = '\0';
            }
            
            if (connected.size() > 1) {
                for (const auto& pair : connected) {
                    if (pair.first != string(client_ip)) {
                        string full_msg = string(buffer) + "\n";
                        send(pair.second, full_msg.c_str(), full_msg.length(), 0);
                    }
                }
            } else {
                const char* waiting_msg = "Waiting for other clients...\n";
                send(client_fd, waiting_msg, strlen(waiting_msg), 0);
            }
        }
    }

    void printMapArrow() {
        for (const auto& pair : connected) {
            cout << pair.first << " ~> " << pair.second << endl;
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