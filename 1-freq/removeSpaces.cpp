#include <iostream>
#include <fstream>

void remove_whitespaces(std::fstream fin, std::fstream fout);

int main(int argc, char const *argv[])
{
    std::cout << "Remove Spaces\n";
    //remove_whitespaces(std::fstream{"book.txt"}, std::fstream{"book_clean.txt"});
    return 0;
}

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
