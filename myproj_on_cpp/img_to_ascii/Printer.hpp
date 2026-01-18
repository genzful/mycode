#ifndef PRINTER_HPP
#define PRINTER_HPP
#include <string>
#include <iostream>
#include "map.hpp"
#include <algorithm>
#include <cctype>

std::string toUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return result;
}

namespace Printer {

void print_ascii(const char* text) {
    std::string arg = text;
    char sym;
    std::cout << "input the sym ~~> ";
    std::cin >> sym;
    
    std::string numStr = toUpper(arg);
    
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