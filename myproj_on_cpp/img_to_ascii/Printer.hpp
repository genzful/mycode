#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <string>
#include <iostream>
#include <vector>
#include "map.hpp"
#include <algorithm>
#include <cctype>

std::vector<std::string> splitUtf8(const std::string& str) {
    std::vector<std::string> utf8_chars;
    
    for (size_t i = 0; i < str.length();) {
        unsigned char c = (unsigned char)str[i];
        int char_len = 1;
        
        if (c < 128) {
            char_len = 1;
        } else if ((c & 0xE0) == 0xC0) {
            char_len = 2;
        } else if ((c & 0xF0) == 0xE0) {
            char_len = 3;
        } else if ((c & 0xF8) == 0xF0) {
            char_len = 4;
        }
        
        utf8_chars.push_back(str.substr(i, char_len));
        i += char_len;
    }
    
    return utf8_chars;
}

std::string toUpperUtf8(const std::string& str) {
    std::vector<std::string> chars = splitUtf8(str);
    std::string result;
    
    for (const auto& ch : chars) {
        if (ch.length() == 1) {
            result += (char)std::toupper((unsigned char)ch[0]);
        } else if (ch.length() == 2 && (unsigned char)ch[0] == 0xD0) {
            unsigned char first = ch[0];
            unsigned char second = ch[1];
            
            if (second >= 0xB0 && second <= 0xBF) {
                result += ch;
            } else if (second >= 0x80 && second <= 0x8F) {
                result += std::string(1, (char)first) + std::string(1, (char)(second + 0x30));
            } else {
                result += ch;
            }
        } else {
            result += ch;
        }
    }
    
    return result;
}

namespace Printer {

void print_ascii(const char* text) {
    std::string arg = text;
    char sym;
    std::cout << "input the sym ~~> ";
    std::cin >> sym;
    
    std::string numStr = toUpperUtf8(arg);
    
    std::vector<std::string> utf8_chars = splitUtf8(numStr);
    
    for (int row = 1; row <= 7; ++row) {
        std::string outputLine;
        for (const auto& utf8_char : utf8_chars) {
            std::string digitLine;
            MAP::getDigitLine(utf8_char, row, digitLine, sym);
            outputLine += digitLine + " ";
        }
        std::cout << outputLine << std::endl;
    }
}

}

#endif