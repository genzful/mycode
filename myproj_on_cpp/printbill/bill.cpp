#include <iostream> // for std::cin && std::cout
#include <string>   // for std::string

// func which set every line
void getDigitLine(char digit, int row, std::string& line) {
  switch (digit) {
  case '0':
    switch (row) {
    case 1:
      line = "$$$$";
      break;
    case 2:
      line = "$  $";
      break;
    case 3:
      line = "$  $";
      break;
    case 4:
      line = "$  $";
      break;
    case 5:
      line = "$  $";
      break;
    case 6:
      line = "$  $";
      break;
    case 7:
      line = "$$$$";
      break;
    }
    break;
  case '1':
    switch (row) {
    case 1:
      line = "   $";
      break;
    case 2:
      line = "   $";
      break;
    case 3:
      line = "   $";
      break;
    case 4:
      line = "   $";
      break;
    case 5:
      line = "   $";
      break;
    case 6:
      line = "   $";
      break;
    case 7:
      line = "   $";
      break;
    }
    break;
  case '2':
    switch (row) {
    case 1:
      line = "$$$$";
      break;
    case 2:
      line = "   $";
      break;
    case 3:
      line = "   $";
      break;
    case 4:
      line = "$$$$";
      break;
    case 5:
      line = "$   ";
      break;
    case 6:
      line = "$   ";
      break;
    case 7:
      line = "$$$$";
      break;
    }
    break;
  case '3':
    switch (row) {
    case 1:
      line = "$$$$";
      break;
    case 2:
      line = "   $";
      break;
    case 3:
      line = "   $";
      break;
    case 4:
      line = "$$$$";
      break;
    case 5:
      line = "   $";
      break;
    case 6:
      line = "   $";
      break;
    case 7:
      line = "$$$$";
      break;
    }
    break;
  case '4':
    switch (row) {
    case 1:
      line = "$  $";
      break;
    case 2:
      line = "$  $";
      break;
    case 3:
      line = "$  $";
      break;
    case 4:
      line = "$$$$";
      break;
    case 5:
      line = "   $";
      break;
    case 6:
      line = "   $";
      break;
    case 7:
      line = "   $";
      break;
    }
    break;
  case '5':
    switch (row) {
    case 1:
      line = "$$$$";
      break;
    case 2:
      line = "$   ";
      break;
    case 3:
      line = "$   ";
      break;
    case 4:
      line = "$$$$";
      break;
    case 5:
      line = "   $";
      break;
    case 6:
      line = "   $";
      break;
    case 7:
      line = "$$$$";
      break;
    }
    break;
  case '6':
    switch (row) {
    case 1:
      line = "$$$$";
      break;
    case 2:
      line = "$   ";
      break;
    case 3:
      line = "$   ";
      break;
    case 4:
      line = "$$$$";
      break;
    case 5:
      line = "$  $";
      break;
    case 6:
      line = "$  $";
      break;
    case 7:
      line = "$$$$";
      break;
    }
    break;
  case '7':
    switch (row) {
    case 1:
      line = "$$$$";
      break;
    case 2:
      line = "   $";
      break;
    case 3:
      line = "  $ ";
      break;
    case 4:
      line = " $  ";
      break;
    case 5:
      line = "$   ";
      break;
    case 6:
      line = "$   ";
      break;
    case 7:
      line = "$   ";
      break;
    }
    break;
  case '8':
    switch (row) {
    case 1:
      line = "$$$$";
      break;
    case 2:
      line = "$  $";
      break;
    case 3:
      line = "$  $";
      break;
    case 4:
      line = "$$$$";
      break;
    case 5:
      line = "$  $";
      break;
    case 6:
      line = "$  $";
      break;
    case 7:
      line = "$$$$";
      break;
    }
    break;
  case '9':
    switch (row) {
    case 1:
      line = "$$$$";
      break;
    case 2:
      line = "$  $";
      break;
    case 3:
      line = "$  $";
      break;
    case 4:
      line = "$$$$";
      break;
    case 5:
      line = "   $";
      break;
    case 6:
      line = "   $";
      break;
    case 7:
      line = "$$$$";
      break;
    }
    break;
  default:
    line = "    ";
  }
}

// main func
int main(int argc, char* argv[]) {
  // test for 2 arguments
  if (argc == 2) {
    if (argv[1] == "--help") {
      // --help output
      std::cout << "usage: ./bill <number which u want to print>" << std::endl;
    } else {
      try {
        // check for number in argv[]
        int var = std::stoi(argv[1]);
      } catch (const std::exception& e) {
        std::cout << "argument not number!";
        return 1;
      }
      std::string numStr = argv[1];
      char digits[10];

      // cycle for filling array digits [10]
      for (int i = 0; i < numStr.length(); i++) {
        digits[i] = numStr[i];
      }

      // filling line and print it for 
      for (int row = 0; row < 8; ++row) {
        std::string outputLine;
        for (int d = 0; d < numStr.length(); ++d) {
          std::string digitLine;
          getDigitLine(digits[d], row, digitLine);
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