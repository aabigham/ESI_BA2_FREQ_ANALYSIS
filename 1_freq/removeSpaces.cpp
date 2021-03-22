#include <iostream>
#include <fstream>
#include <string.h>

/**
 * Takes one fin in argument and creates an output text file containing
 * all of the content of the first file without the whitespaces.
 * */
int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout << "One argument needed.\n";
        exit(1);
    }

    std::fstream fin;
    fin.open(argv[1]);
    if (fin.fail())
    {
        std::cout << "Input file could not be opened.\n";
        exit(1);
    }

    char *token = strtok((char *)argv[1], ".txt");
    char *s_out = strcat(token, "-out.txt");

    std::ofstream fout(s_out);
    std::string str;
    while (fin >> str)
    {
        fout << str;
    }

    fin.close();
    fout.close();
    std::cout << s_out << " created\n";

    return 0;
}
