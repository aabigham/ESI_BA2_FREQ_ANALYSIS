#include <iostream>

#include "cesar_utils.hpp"

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
        std::cout << "Trying to cipher, please enter your shift:\n";
        int shift = amine::askCesarShift();
        std::cout << "Ciphering with shift of value " << shift << "...\n";
        cesar::cipher(name_fin, name_fout, shift);
        std::cout << "Ciphering done! " << name_fout << " created.\n";
    }

    if (strcmp(argv[1], "-d") == 0)
    {
        char answer = amine::askYesNo(); // asking if you want to decipher with a key or not

        if (answer == 'y')
        {
            std::cout << "Trying to decipher with a shift, please enter your shift:\n";
            int shift = amine::askCesarShift();
            std::cout << "Deciphering with shift of value " << shift << "...\n";
            cesar::decipher(name_fin, name_fout, shift);
        }
        if (answer == 'n')
        {
            std::cout << "Deciphering with no shift...\n";
            cesar::decipher(name_fin, name_fout);
        }
        std::cout << "Deciphering done! " << name_fout << " created.\n";
    }

    return 0;
}