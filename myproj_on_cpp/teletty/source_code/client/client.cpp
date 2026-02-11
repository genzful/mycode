#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

// client
class Client {
private:
    int sock;
    struct sockaddr_in server_addr;
    
public:
    Client() : sock(-1) {}
    
    bool connectToServer(const std::string& address, int port) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        
        if (sock == -1) {
            std::cerr << "Ошибка создания сокета" << std::endl;
            return false;
        }
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);

        if (inet_pton(AF_INET, address.c_str(), &server_addr.sin_addr) <= 0) {
            std::cerr << "Неверный адрес или адрес не поддерживается" << std::endl;
            close(sock);
            return false;
        }
        if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "Ошибка подключения к серверу" << std::endl;
            close(sock);
            return false;
        }
        
        std::cout << "Успешно подключено к " << address << ":" << port << std::endl;
        return true;
    }

    bool sendData(const std::string& data) {
        if (send(sock, data.c_str(), data.length(), 0) < 0) {
            std::cerr << "Ошибка отправки данных" << std::endl;
            return false;
        }
        return true;
    }
    
    std::string receiveData(size_t bufferSize = 4096) {
        char buffer[bufferSize];
        memset(buffer, 0, bufferSize);
        
        ssize_t bytesReceived = recv(sock, buffer, bufferSize - 1, 0);
        if (bytesReceived < 0) {
            std::cerr << "Ошибка приема данных" << std::endl;
            return "";
        }
        
        return std::string(buffer, bytesReceived);
    }
    
    void disconnect() {
        if (sock != -1) {
            close(sock);
            sock = -1;
            std::cout << "Соединение закрыто" << std::endl;
        }
    }
    
    ~Client() {
        disconnect();
    }
};

int main() {
    Client client;
    std::string msg;
    const std::string serverAddress = "127.0.0.1";
    const int port = 7252;
    std::string welcome_msg = "";

    if (!client.connectToServer(serverAddress, port)) {
        std::cout << "не удалось подключиться к серваку" << std::endl;
    }
    
    welcome_msg = client.receiveData();
    if (!welcome_msg.empty()) {
        std::cout << welcome_msg << std::endl;
    } else {
        std::cerr << "Сервер в отключке" << std::endl;
        client.disconnect();
        return 1;
    }

    while (true) {
        std::cin >> msg;
        client.sendData(msg.c_str());
        std::string resp = client.receiveData();
        if (resp == "this name already exists") {
            std::cout << resp << std::endl;
            return 1;
        }
        std::cout << resp;
    }
    
    client.disconnect();
    
    return 0;
}
