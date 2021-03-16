#include "myfunctions.h"
#include <iostream>

void remove_whitespaces(std::fstream fin, std::fstream fout)
{
    std::string str;
    while (fin >> str)
    {
        std::cout << str;
        fout << str;
    }
    fin.close();
    fout.close();
}

/*void cesar(std::string str)
{
    // TODO
}

void vigenere(std::string str)
{
    // TODO
}*/