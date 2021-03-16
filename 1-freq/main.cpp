#include <iostream>
#include "myfunctions.h"

int main(int argc, char const *argv[])
{
    std::cout << "Hello World\n";
    remove_whitespaces(std::fstream{"books.txt"}, std::fstream{"book-out.txt"});

    return 0;
}
