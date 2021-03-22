#include <iostream>
#include <fstream>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        std::cout << "Two argument needed.\n";
        exit(1);
    }
    else if (strcmp(argv[1], "-c") && strcmp(argv[1], "-u"))
    {
        std::cout << "Wrong options, must be \"-c\" to cipher or \"-u\" to uncipher your file.\n";
        exit(1);
    }
    std::fstream fin;
    fin.open(argv[2]);
    if (fin.fail())
    {
        std::cout << "Input file could not be opened, are you sure it is a text file ?\n";
        exit(1);
    }

    int key = 5;
    char *name_fin = strtok((char *)argv[2], ".");
    char *name_fout;
    if (!strcmp(argv[1], "-u"))
    {
        key = -key;
        name_fout = strcat(name_fin, "-unciphered.txt");
    }
    else
    {
        name_fout = strcat(name_fin, "-ciphered.txt");
    }
    std::cout << key << " is the key\n";

    std::ofstream fout(name_fout);
    std::string content;
    fin >> content;
    for (auto &c : content)
        if (c >= 'a' && c <= 'z')
            c = char(int(c + key - 97) % 26 + 97);
    fout << content;

    fin.close();
    fout.close();
    std::cout << name_fout << " created\n";

    return 0;
}
