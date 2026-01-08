#include <iostream> // for std::cin && std::cout
#include <string>   // for std::string

// func which change $ on ur sym
void replaceDollarWithSym(std::string& str, char sym) {
    for (char& c : str) {
        if (c == '$') {
            c = sym;
        }
    }
}

// func which set every line
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

// main func
int main(int argc, char* argv[]) {
    // test for 2 arguments
    if (argc == 2) {
        std::string arg = argv[1];
        if (arg == "--help") {
            // --help output
            std::cout << "usage: ./bill <number which u want to print>" << std::endl;
        } else {
            char sym;
            std::cout << "input the sym ~~> ";
            std::cin >> sym;
            try {
                // check for number in argv[]
                int var = std::stoi(arg);
            } catch (const std::exception& e) {
                std::cout << "argument not number!";
                return 1;
            }
            
            std::string numStr = arg;
            
            // filling line and print it for each row
            for (int row = 1; row <= 7; ++row) {
                std::string outputLine;
                for (size_t d = 0; d < numStr.length(); ++d) {
                    std::string digitLine;
                    getDigitLine(numStr[d], row, digitLine, sym);
                    outputLine += digitLine + " ";
                }
                std::cout << outputLine << std::endl;
            }
        }
    } else {
        std::cout << "bill printer need only 2 arguments\n --help for help" << std::endl;
    }
    return 0;
}