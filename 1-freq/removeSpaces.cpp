#include <iostream>
#include <fstream>

/**
 * Takes one fin in argument and creates an output text file containing
 * all of the content of the first file without the whitespaces.
 * */
int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout << "One arguments needed.\n";
        exit(1);
    }

    std::fstream fin;
    fin.open(argv[1]);
    if (fin.fail())
    {
        std::cout << "Input file could not be opened.\n";
        exit(1);
    }

    std::ofstream fout("out.txt");
    std::string str;
    while (fin >> str)
    {
        fout << str;
    }

    fin.close();
    fout.close();

    return 0;
}
