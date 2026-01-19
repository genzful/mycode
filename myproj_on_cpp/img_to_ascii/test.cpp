#include <iostream>
#include <string>
#include <ranges>

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::string text = "фывфывы";
    for (char it : text) {
        std::cout << it;
    }
    char c = 'A';
    std::string str(1, c);  // Создать строку из 1 символа c
    std::cout << sizeof(str);
}