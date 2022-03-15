#include <iostream>

#include "vigenere_utils.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 4) // Must have 4 args: executable, flag, input file, output file
    {
        std::cerr << "Wrong number of arguments.\n";
        return -1;
    }
    if (strcmp(argv[1], "-c") && strcmp(argv[1], "-d")) // Checking flags arguments
    {
        std::cerr << "Please use \"-c\" to cipher and \"-d\" to decipher your file.\n";
        return -1;
    }

    /* Arguments have been checked at this point */

    // Name of input and output file
    char *name_fin = (char *)argv[2];
    char *name_fout = (char *)argv[3];

    // Flag conditions
    if (strcmp(argv[1], "-c") == 0)
    {
        std::cout << "Trying to cipher, please enter your key:\n";
        std::string key = amine::askVigenereKey();
        std::cout << "Ciphering with key: " << key << "...\n";
        vigenere::cipher(name_fin, name_fout, key);
        std::cout << "Ciphering done! " << name_fout << " created.\n";
    }

    if (strcmp(argv[1], "-d") == 0)
    {
        char answer = amine::askYesNo(); // asking if you want to decipher with a key or not

        if (answer == 'y')
        {
            std::cout << "Trying to decipher with a key, please enter your key:\n";
            std::string key = amine::askVigenereKey();
            std::cout << "Deciphering with key: " << key << "...\n";
            vigenere::decipher(name_fin, name_fout, key);
        }
        if (answer == 'n')
        {
            std::cout << "Deciphering with no key...\n";
            vigenere::decipher(name_fin, name_fout);
        }
        std::cout << "Deciphering done! " << name_fout << " created.\n";
    }

    return 0;
}
