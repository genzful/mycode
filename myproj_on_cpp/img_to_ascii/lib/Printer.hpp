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

bool is_latin(const std::string& str) {
    for (char c : str) {
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            return false;
        }
    }
    return true;
}

namespace Printer {

void print_ascii(const char* text) {
    if (is_latin(text)) {
        std::string arg = text;
        char sym;
        std::cout << "input the sym ~~> ";
        std::cin >> sym;
        
        std::string numStr = toUpper(arg);
        
        for (int row = 1; row <= 7; ++row) {
            std::string outputLine;
            for (const auto& ch : numStr) {
                std::string digitLine;
                MAP::getDigitLine(ch, row, digitLine, sym);
                outputLine += digitLine + " ";
            }
            std::cout << outputLine << std::endl;
        }
    } else {
        std::cout << "utf-8 is not supported yet...";
    }
}

}

#endif