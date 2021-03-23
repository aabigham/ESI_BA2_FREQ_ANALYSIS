#include <iostream>
#include <fstream>
#include <string.h>
#include <iostream>
#include <unordered_map>

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

    std::ifstream fin(argv[2], std::ios_base::binary);
    if (fin.fail())
    {
        std::cout << "Input file could not be opened, are you sure it is a text file ?\n";
        exit(1);
    }
    char *name_fin = strtok((char *)argv[2], ".");

    char *name_fout;
    if (!strcmp(argv[1], "-c"))
    {
        int key = 5;
        name_fout = strcat(name_fin, "-ciphered.txt");
        std::ofstream fout(name_fout);
        for (char c; fin.get(c);)
        {
            if (c >= 'a' && c <= 'z')
                c = char(int(c + key - 97) % 26 + 97);
            fout << c;
        }
        fout.close();
    }
    else
    {
        name_fout = strcat(name_fin, "-unciphered.txt");
        std::ofstream fout(name_fout, std::ios_base::binary);

        size_t freq[26];
        std::fill_n(freq, 26, 0);

        for (char c; fin.get(c);)
            if (c >= 'a' && c <= 'z')
                ++freq[int(c) - int('a')];

        for (size_t i = 0; i < 26; i++)
            std::cout << char(i + 97) << " = " << freq[i] << '\n';

        //int key = 26 - key;
        fout.close();
    }

    fin.close();
    std::cout << name_fout << " created\n";

    return 0;
}
