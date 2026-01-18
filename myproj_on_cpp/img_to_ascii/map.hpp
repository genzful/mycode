#ifndef MAP_HPP
#define MAP_HPP

namespace MAP {

void getDigitLine(char digit, int row, std::string& line, const char sym) {
    std::string pattern;
    
    switch (digit) {
    case '0':
        switch (row) {
        case 1:
            pattern = "$$$$";
            break;
        case 2:
            pattern = "$  $";
            break;
        case 3:
            pattern = "$  $";
            break;
        case 4:
            pattern = "$  $";
            break;
        case 5:
            pattern = "$  $";
            break;
        case 6:
            pattern = "$  $";
            break;
        case 7:
            pattern = "$$$$";
            break;
        default:
            pattern = "    ";
        }
        break;
    case '1':
        switch (row) {
        case 1:
            pattern = "   $";
            break;
        case 2:
            pattern = "   $";
            break;
        case 3:
            pattern = "   $";
            break;
        case 4:
            pattern = "   $";
            break;
        case 5:
            pattern = "   $";
            break;
        case 6:
            pattern = "   $";
            break;
        case 7:
            pattern = "   $";
            break;
        default:
            pattern = "    ";
        }
        break;
    case '2':
        switch (row) {
        case 1:
            pattern = "$$$$";
            break;
        case 2:
            pattern = "   $";
            break;
        case 3:
            pattern = "   $";
            break;
        case 4:
            pattern = "$$$$";
            break;
        case 5:
            pattern = "$   ";
            break;
        case 6:
            pattern = "$   ";
            break;
        case 7:
            pattern = "$$$$";
            break;
        default:
            pattern = "    ";
        }
        break;
    case '3':
        switch (row) {
        case 1:
            pattern = "$$$$";
            break;
        case 2:
            pattern = "   $";
            break;
        case 3:
            pattern = "   $";
            break;
        case 4:
            pattern = "$$$$";
            break;
        case 5:
            pattern = "   $";
            break;
        case 6:
            pattern = "   $";
            break;
        case 7:
            pattern = "$$$$";
            break;
        default:
            pattern = "    ";
        }
        break;
    case '4':
        switch (row) {
        case 1:
            pattern = "$  $";
            break;
        case 2:
            pattern = "$  $";
            break;
        case 3:
            pattern = "$  $";
            break;
        case 4:
            pattern = "$$$$";
            break;
        case 5:
            pattern = "   $";
            break;
        case 6:
            pattern = "   $";
            break;
        case 7:
            pattern = "   $";
            break;
        default:
            pattern = "    ";
        }
        break;
    case '5':
        switch (row) {
        case 1:
            pattern = "$$$$";
            break;
        case 2:
            pattern = "$   ";
            break;
        case 3:
            pattern = "$   ";
            break;
        case 4:
            pattern = "$$$$";
            break;
        case 5:
            pattern = "   $";
            break;
        case 6:
            pattern = "   $";
            break;
        case 7:
            pattern = "$$$$";
            break;
        default:
            pattern = "    ";
        }
        break;
    case '6':
        switch (row) {
        case 1:
            pattern = "$$$$";
            break;
        case 2:
            pattern = "$   ";
            break;
        case 3:
            pattern = "$   ";
            break;
        case 4:
            pattern = "$$$$";
            break;
        case 5:
            pattern = "$  $";
            break;
        case 6:
            pattern = "$  $";
            break;
        case 7:
            pattern = "$$$$";
            break;
        default:
            pattern = "    ";
        }
        break;
    case '7':
        switch (row) {
        case 1:
            pattern = "$$$$";
            break;
        case 2:
            pattern = "   $";
            break;
        case 3:
            pattern = "  $ ";
            break;
        case 4:
            pattern = " $  ";
            break;
        case 5:
            pattern = "$   ";
            break;
        case 6:
            pattern = "$   ";
            break;
        case 7:
            pattern = "$   ";
            break;
        default:
            pattern = "    ";
        }
        break;
    case '8':
        switch (row) {
        case 1:
            pattern = "$$$$";
            break;
        case 2:
            pattern = "$  $";
            break;
        case 3:
            pattern = "$  $";
            break;
        case 4:
            pattern = "$$$$";
            break;
        case 5:
            pattern = "$  $";
            break;
        case 6:
            pattern = "$  $";
            break;
        case 7:
            pattern = "$$$$";
            break;
        default:
            pattern = "    ";
        }
        break;
    case '9':
        switch (row) {
        case 1:
            pattern = "$$$$";
            break;
        case 2:
            pattern = "$  $";
            break;
        case 3:
            pattern = "$  $";
            break;
        case 4:
            pattern = "$$$$";
            break;
        case 5:
            pattern = "   $";
            break;
        case 6:
            pattern = "   $";
            break;
        case 7:
            pattern = "$$$$";
            break;
        default:
            pattern = "    ";
        }
        break;
    default:
        pattern = "    ";
    }
    
    replaceDollarWithSym(pattern, sym);
    line = pattern;
}

}

#endif