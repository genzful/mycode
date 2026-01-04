#include <iostream> // for std::cin && std::cout
#include <string>   // for std::string

using namespace std;

// func which set every line
void getDigitLine(char digit, int row, string& line) {
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

int main() {
  int num;
  cout << "Enter a number: ";
  cin >> num;
  string numStr = to_string(num);
  char digits[10];

  for (int i = 0; i < numStr.length(); i++) {
    digits[i] = numStr[i];
  }

  for (int row = 0; row < 8; ++row) {
    string outputLine;
    for (int d = 0; d < numStr.length(); ++d) {
      string digitLine;
      getDigitLine(digits[d], row, digitLine);
      outputLine += digitLine + " ";
    }
    cout << outputLine << endl;
  }
  return 0;
}