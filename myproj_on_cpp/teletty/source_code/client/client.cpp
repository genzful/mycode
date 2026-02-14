#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include "database.hpp"
#include <fstream>
#include <filesystem>

const char* homeDir = getenv("HOME");
std::string currentUser;

namespace fs = std::filesystem;

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

void createDIR() {
    const char* home = getenv("HOME");
    if (home) {
        fs::create_directories(std::string(homeDir) + "/.gchat");
    }
}

void addFriend(Client& client, string name) {
    std::string msg = "1 " + name;
    client.sendData(msg.c_str());
    std::string ans = client.receiveData();
    
    if (ans == "0") {
        std::cout << "Такого юзера нет(" << endl;
    } else if (ans == "1") {
        std::cout << "Юзер найден и добавлен в чаты" << endl;
        
        if (!currentUser.empty()) {
            std::string friendPath = std::string(homeDir) + "/.gchat/" + currentUser + "/" + name;
            
            if (!fs::exists(friendPath)) {
                fs::create_directories(friendPath);
                std::cout << "Создана папка для друга: " << name << endl;
            }
        }
        
    } else {
        std::cerr << "error with db" << endl;
    }
}

void startChat() {}

int main() {
    Client client;
    std::string msg;
    const std::string serverAddress = "127.0.0.1";
    const int port = 7252;
    createDIR();
    std::string welcome_msg = "";
    int chat;
    char choise;
    char auth;

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

    std::cout << "Логин/Рег" << std::endl; std::cin >> auth;

    if (auth == '1') {
        std::cout << "Напишите свое имя: ";
        std::cin >> msg;
        client.sendData(msg.c_str());
        if (client.receiveData() == "0") {
            std::cout << "имя принято" << std::endl;
            
            currentUser = msg;
            std::string userPath = std::string(homeDir) + "/.gchat/" + msg;
            
            std::ifstream f(userPath.c_str());
            if (!f) {
                fs::create_directory(userPath);
                std::cout << "Создана папка для пользователя: " << msg << std::endl;
            } else {
                std::cout << "Папка пользователя уже существует" << std::endl;
            }
            f.close();
        }
    } else if (auth == '2') {
        std::cout << "Напишите свое имя: ";
        std::cin >> msg;
        client.sendData(msg.c_str());
        if (client.receiveData() == "1") {
            std::cout << "имя принято" << std::endl;
        } else {
            std::cout << "Имя не принято!\nПопробуйте другое в сл раз" << std::endl;
            client.disconnect();
            return 1;
        }
    }

    // render main page of chats

    std::cout << "1 - Добавить имя\n2 - Выбрать чат для общения\n\t~> ";
    std::cin >> choise;
    switch (choise) {
        case '1':
            std::string ip; std::cout << "Имя для добавления ~> "; std::cin >> ip;
            addFriend(client, ip);
    }
    
    // request to database for a messages in this chat
    // request to server for connection
    // render chat page with msgs
    // cycle for chating
    
    client.disconnect();
    
    return 0;
}
