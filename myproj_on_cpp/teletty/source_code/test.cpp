#include <iostream>
#include <netinet/in.h> // Для htons
#include <iomanip>

int main() {
    unsigned short port = 8080; // Порядок байтов хоста
    unsigned short netPort = htons(port); // Преобразование в сетевой порядок

    std::cout << "Хост: " << std::hex << port << std::endl;
    std::cout << "Сеть: " << std::hex << netPort << std::endl;
    // На Little-Endian машинах выведет:
    // Хост: 1f90 (0x1f90)
    // Сеть: 901f (0x901f)
    return 0;
}
