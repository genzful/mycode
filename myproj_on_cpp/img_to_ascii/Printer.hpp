#ifndef PRINTER_HPP
#define PRINTER_HPP
#include <string>
#include <iostream>
#include "map.hpp"

namespace Printer {



void print_ascii(const char* text) {
    // std::cout << "sometest" << std::endl;
    // std::cout << text << std::endl;
    std::string arg = text;
    char sym;
    std::cout << "input the sym ~~> ";
    std::cin >> sym;
    try {
        int var = std::stoi(arg);
    } catch (const std::exception& e) {
        throw std::runtime_error("argument not number!");
    }
    
    std::string numStr = arg;
    
    // filling line and print it for each row
    for (int row = 1; row <= 7; ++row) {
        std::string outputLine;
        for (size_t d = 0; d < numStr.length(); ++d) {
            std::string digitLine;
            MAP::getDigitLine(numStr[d], row, digitLine, sym);
            outputLine += digitLine + " ";
        }
        std::cout << outputLine << std::endl;
    }
}

}
// code

#endif