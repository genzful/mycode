#include <iostream>
#include "Printer.hpp"

int main(int argc, char* argv[]) {
    const char* arg = argv[1];
    std::cout << arg << std::endl;
    Printer::print_ascii(arg);
}