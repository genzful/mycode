#ifndef MAP_HPP
#define MAP_HPP

#include <string>

namespace MAP {

// func which change $ on ur sym
void replaceDollarWithSym(std::string& str, char sym) {
    for (char& c : str) {
        if (c == '$') {
            c = sym;
        }
    }
}

void getDigitLine(const std::string digit, const int& row, std::string& line, const char sym) {
    std::string pattern;
    
    if (digit.length() == 1) {
        char ch = digit[0];
        
        // digits
        if (ch >= '0' && ch <= '9') {
            switch (ch) {
            case '0':
                switch (row) {
                case 1: pattern = "$$$$"; break;
                case 2: pattern = "$  $"; break;
                case 3: pattern = "$  $"; break;
                case 4: pattern = "$  $"; break;
                case 5: pattern = "$  $"; break;
                case 6: pattern = "$  $"; break;
                case 7: pattern = "$$$$"; break;
                default: pattern = "    ";
                }
                break;
            case '1':
                switch (row) {
                case 1: pattern = "   $"; break;
                case 2: pattern = "   $"; break;
                case 3: pattern = "   $"; break;
                case 4: pattern = "   $"; break;
                case 5: pattern = "   $"; break;
                case 6: pattern = "   $"; break;
                case 7: pattern = "   $"; break;
                default: pattern = "    ";
                }
                break;
            case '2':
                switch (row) {
                case 1: pattern = "$$$$"; break;
                case 2: pattern = "   $"; break;
                case 3: pattern = "   $"; break;
                case 4: pattern = "$$$$"; break;
                case 5: pattern = "$   "; break;
                case 6: pattern = "$   "; break;
                case 7: pattern = "$$$$"; break;
                default: pattern = "    ";
                }
                break;
            case '3':
                switch (row) {
                case 1: pattern = "$$$$"; break;
                case 2: pattern = "   $"; break;
                case 3: pattern = "   $"; break;
                case 4: pattern = "$$$$"; break;
                case 5: pattern = "   $"; break;
                case 6: pattern = "   $"; break;
                case 7: pattern = "$$$$"; break;
                default: pattern = "    ";
                }
                break;
            case '4':
                switch (row) {
                case 1: pattern = "$  $"; break;
                case 2: pattern = "$  $"; break;
                case 3: pattern = "$  $"; break;
                case 4: pattern = "$$$$"; break;
                case 5: pattern = "   $"; break;
                case 6: pattern = "   $"; break;
                case 7: pattern = "   $"; break;
                default: pattern = "    ";
                }
                break;
            case '5':
                switch (row) {
                case 1: pattern = "$$$$"; break;
                case 2: pattern = "$   "; break;
                case 3: pattern = "$   "; break;
                case 4: pattern = "$$$$"; break;
                case 5: pattern = "   $"; break;
                case 6: pattern = "   $"; break;
                case 7: pattern = "$$$$"; break;
                default: pattern = "    ";
                }
                break;
            case '6':
                switch (row) {
                case 1: pattern = "$$$$"; break;
                case 2: pattern = "$   "; break;
                case 3: pattern = "$   "; break;
                case 4: pattern = "$$$$"; break;
                case 5: pattern = "$  $"; break;
                case 6: pattern = "$  $"; break;
                case 7: pattern = "$$$$"; break;
                default: pattern = "    ";
                }
                break;
            case '7':
                switch (row) {
                case 1: pattern = "$$$$"; break;
                case 2: pattern = "   $"; break;
                case 3: pattern = "  $ "; break;
                case 4: pattern = " $  "; break;
                case 5: pattern = "$   "; break;
                case 6: pattern = "$   "; break;
                case 7: pattern = "$   "; break;
                default: pattern = "    ";
                }
                break;
            case '8':
                switch (row) {
                case 1: pattern = "$$$$"; break;
                case 2: pattern = "$  $"; break;
                case 3: pattern = "$  $"; break;
                case 4: pattern = "$$$$"; break;
                case 5: pattern = "$  $"; break;
                case 6: pattern = "$  $"; break;
                case 7: pattern = "$$$$"; break;
                default: pattern = "    ";
                }
                break;
            case '9':
                switch (row) {
                case 1: pattern = "$$$$"; break;
                case 2: pattern = "$  $"; break;
                case 3: pattern = "$  $"; break;
                case 4: pattern = "$$$$"; break;
                case 5: pattern = "   $"; break;
                case 6: pattern = "   $"; break;
                case 7: pattern = "$$$$"; break;
                default: pattern = "    ";
                }
                break;
            default:
                pattern = "    ";
            }
        }
        // english letters
        else if (ch >= 'A' && ch <= 'Z') {
            switch (ch) {
            case 'A':
                switch (row) {
                case 1: pattern = " $$ "; break;
                case 2: pattern = "$  $"; break;
                case 3: pattern = "$  $"; break;
                case 4: pattern = "$$$$"; break;
                case 5: pattern = "$  $"; break;
                case 6: pattern = "$  $"; break;
                case 7: pattern = "$  $"; break;
                default: pattern = "    ";
                }
                break;
            
            case 'B':
                switch (row) {
                case 1: pattern = "$$$ "; break;
                case 2: pattern = "$  $"; break;
                case 3: pattern = "$  $"; break;
                case 4: pattern = "$$$ "; break;
                case 5: pattern = "$  $"; break;
                case 6: pattern = "$  $"; break;
                case 7: pattern = "$$$ "; break;
                default: pattern = "    ";
                }
                break;
            
            case 'C':
                switch (row) {
                case 1: pattern = " $$$"; break;
                case 2: pattern = "$   "; break;
                case 3: pattern = "$   "; break;
                case 4: pattern = "$   "; break;
                case 5: pattern = "$   "; break;
                case 6: pattern = "$   "; break;
                case 7: pattern = " $$$"; break;
                default: pattern = "    ";
                }
                break;
            
            case 'D':
                switch (row) {
                case 1: pattern = "$$$ "; break;
                case 2: pattern = "$  $"; break;
                case 3: pattern = "$  $"; break;
                case 4: pattern = "$  $"; break;
                case 5: pattern = "$  $"; break;
                case 6: pattern = "$  $"; break;
                case 7: pattern = "$$$ "; break;
                default: pattern = "    ";
                }
                break;
            
            case 'E':
                switch (row) {
                case 1: pattern = "$$$$"; break;
                case 2: pattern = "$   "; break;
                case 3: pattern = "$   "; break;
                case 4: pattern = "$$$ "; break;
                case 5: pattern = "$   "; break;
                case 6: pattern = "$   "; break;
                case 7: pattern = "$$$$"; break;
                default: pattern = "    ";
                }
                break;
            
            case 'F':
                switch (row) {
                case 1: pattern = "$$$$"; break;
                case 2: pattern = "$   "; break;
                case 3: pattern = "$   "; break;
                case 4: pattern = "$$$ "; break;
                case 5: pattern = "$   "; break;
                case 6: pattern = "$   "; break;
                case 7: pattern = "$   "; break;
                default: pattern = "    ";
                }
                break;
            
            case 'G':
                switch (row) {
                case 1: pattern = " $$$"; break;
                case 2: pattern = "$   "; break;
                case 3: pattern = "$   "; break;
                case 4: pattern = "$ $$"; break;
                case 5: pattern = "$  $"; break;
                case 6: pattern = "$  $"; break;
                case 7: pattern = " $$ "; break;
                default: pattern = "    ";
                }
                break;
            
            case 'H':
                switch (row) {
                case 1: pattern = "$  $"; break;
                case 2: pattern = "$  $"; break;
                case 3: pattern = "$  $"; break;
                case 4: pattern = "$$$$"; break;
                case 5: pattern = "$  $"; break;
                case 6: pattern = "$  $"; break;
                case 7: pattern = "$  $"; break;
                default: pattern = "    ";
                }
                break;
            
            case 'I':
                switch (row) {
                case 1: pattern = "$$$$"; break;
                case 2: pattern = "  $ "; break;
                case 3: pattern = "  $ "; break;
                case 4: pattern = "  $ "; break;
                case 5: pattern = "  $ "; break;
                case 6: pattern = "  $ "; break;
                case 7: pattern = "$$$$"; break;
                default: pattern = "    ";
                }
                break;
            
            case 'J':
                switch (row) {
                case 1: pattern = "$$$$"; break;
                case 2: pattern = "   $"; break;
                case 3: pattern = "   $"; break;
                case 4: pattern = "   $"; break;
                case 5: pattern = "$  $"; break;
                case 6: pattern = "$  $"; break;
                case 7: pattern = " $$ "; break;
                default: pattern = "    ";
                }
                break;
            
            case 'K':
                switch (row) {
                case 1: pattern = "$  $"; break;
                case 2: pattern = "$ $ "; break;
                case 3: pattern = "$$  "; break;
                case 4: pattern = "$   "; break;
                case 5: pattern = "$$  "; break;
                case 6: pattern = "$ $ "; break;
                case 7: pattern = "$  $"; break;
                default: pattern = "    ";
                }
                break;
            
            case 'L':
                switch (row) {
                case 1: pattern = "$   "; break;
                case 2: pattern = "$   "; break;
                case 3: pattern = "$   "; break;
                case 4: pattern = "$   "; break;
                case 5: pattern = "$   "; break;
                case 6: pattern = "$   "; break;
                case 7: pattern = "$$$$"; break;
                default: pattern = "    ";
                }
                break;
            
            case 'M':
                switch (row) {
                case 1: pattern = "$   $"; break;
                case 2: pattern = "$$ $$"; break;
                case 3: pattern = "$ $ $"; break;
                case 4: pattern = "$   $"; break;
                case 5: pattern = "$   $"; break;
                case 6: pattern = "$   $"; break;
                case 7: pattern = "$   $"; break;
                default: pattern = "     ";
                }
                break;
            
            case 'N':
                switch (row) {
                case 1: pattern = "$   $"; break;
                case 2: pattern = "$$  $"; break;
                case 3: pattern = "$ $ $"; break;
                case 4: pattern = "$  $$"; break;
                case 5: pattern = "$   $"; break;
                case 6: pattern = "$   $"; break;
                case 7: pattern = "$   $"; break;
                default: pattern = "     ";
                }
                break;
            
            case 'O':
                switch (row) {
                case 1: pattern = " $$ "; break;
                case 2: pattern = "$  $"; break;
                case 3: pattern = "$  $"; break;
                case 4: pattern = "$  $"; break;
                case 5: pattern = "$  $"; break;
                case 6: pattern = "$  $"; break;
                case 7: pattern = " $$ "; break;
                default: pattern = "    ";
                }
                break;
            
            case 'P':
                switch (row) {
                case 1: pattern = "$$$ "; break;
                case 2: pattern = "$  $"; break;
                case 3: pattern = "$  $"; break;
                case 4: pattern = "$$$ "; break;
                case 5: pattern = "$   "; break;
                case 6: pattern = "$   "; break;
                case 7: pattern = "$   "; break;
                default: pattern = "    ";
                }
                break;
            
            case 'Q':
                switch (row) {
                case 1: pattern = " $$ "; break;
                case 2: pattern = "$  $"; break;
                case 3: pattern = "$  $"; break;
                case 4: pattern = "$  $"; break;
                case 5: pattern = "$  $"; break;
                case 6: pattern = "$ $ "; break;
                case 7: pattern = "  $$"; break;
                default: pattern = "    ";
                }
                break;
            
            case 'R':
                switch (row) {
                case 1: pattern = "$$$ "; break;
                case 2: pattern = "$  $"; break;
                case 3: pattern = "$  $"; break;
                case 4: pattern = "$$$ "; break;
                case 5: pattern = "$ $ "; break;
                case 6: pattern = "$  $"; break;
                case 7: pattern = "$  $"; break;
                default: pattern = "    ";
                }
                break;
            
            case 'S':
                switch (row) {
                case 1: pattern = " $$$"; break;
                case 2: pattern = "$   "; break;
                case 3: pattern = "$   "; break;
                case 4: pattern = " $$ "; break;
                case 5: pattern = "   $"; break;
                case 6: pattern = "   $"; break;
                case 7: pattern = "$$$ "; break;
                default: pattern = "    ";
                }
                break;
            
            case 'T':
                switch (row) {
                case 1: pattern = "$$$$$$"; break;
                case 2: pattern = "  $  "; break;
                case 3: pattern = "  $  "; break;
                case 4: pattern = "  $  "; break;
                case 5: pattern = "  $  "; break;
                case 6: pattern = "  $  "; break;
                case 7: pattern = "  $  "; break;
                default: pattern = "     ";
                }
                break;
            
            case 'U':
                switch (row) {
                case 1: pattern = "$  $"; break;
                case 2: pattern = "$  $"; break;
                case 3: pattern = "$  $"; break;
                case 4: pattern = "$  $"; break;
                case 5: pattern = "$  $"; break;
                case 6: pattern = "$  $"; break;
                case 7: pattern = " $$ "; break;
                default: pattern = "    ";
                }
                break;
            
            case 'V':
                switch (row) {
                case 1: pattern = "$   $"; break;
                case 2: pattern = "$   $"; break;
                case 3: pattern = "$   $"; break;
                case 4: pattern = "$   $"; break;
                case 5: pattern = " $ $ "; break;
                case 6: pattern = " $ $ "; break;
                case 7: pattern = "  $  "; break;
                default: pattern = "     ";
                }
                break;
            
            case 'W':
                switch (row) {
                case 1: pattern = "$   $"; break;
                case 2: pattern = "$   $"; break;
                case 3: pattern = "$   $"; break;
                case 4: pattern = "$ $ $"; break;
                case 5: pattern = "$ $ $"; break;
                case 6: pattern = "$ $ $"; break;
                case 7: pattern = " $ $ "; break;
                default: pattern = "     ";
                }
                break;
            
            case 'X':
                switch (row) {
                case 1: pattern = "$   $"; break;
                case 2: pattern = " $ $ "; break;
                case 3: pattern = "  $  "; break;
                case 4: pattern = "  $  "; break;
                case 5: pattern = "  $  "; break;
                case 6: pattern = " $ $ "; break;
                case 7: pattern = "$   $"; break;
                default: pattern = "     ";
                }
                break;
            
            case 'Y':
                switch (row) {
                case 1: pattern = "$   $"; break;
                case 2: pattern = " $ $ "; break;
                case 3: pattern = "  $  "; break;
                case 4: pattern = "  $  "; break;
                case 5: pattern = "  $  "; break;
                case 6: pattern = "  $  "; break;
                case 7: pattern = "  $  "; break;
                default: pattern = "     ";
                }
                break;
            
            case 'Z':
                switch (row) {
                case 1: pattern = "$$$$$"; break;
                case 2: pattern = "    $"; break;
                case 3: pattern = "   $ "; break;
                case 4: pattern = "  $  "; break;
                case 5: pattern = " $   "; break;
                case 6: pattern = "$    "; break;
                case 7: pattern = "$$$$$"; break;
                default: pattern = "     ";
                }
                break;
            
            default:
                pattern = "    ";
            }
        }
    }
    
    replaceDollarWithSym(pattern, sym);
    line = pattern;
}

} // namespace MAP

#endif