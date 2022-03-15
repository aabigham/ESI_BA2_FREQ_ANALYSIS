#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>

#include "utils.hpp"

namespace cesar
{
    void cipher(char *name_fin, char *name_fout, int shift)
    {
        std::ifstream fin(name_fin);
        std::ofstream fout(name_fout);

        char currChar;
        while (fin.get(currChar)) // Applying shift and writing in output file
        {
            if (currChar >= 'a' && currChar <= 'z')
                currChar = char(int(currChar + shift - 97) % 26 + 97);
            fout << currChar;
        }

        fin.close();
        fout.close();
    }

    void decipher(char *name_fin, char *name_fout, int shift)
    {
        cipher(name_fin, name_fout, 26 - shift); // deciphering is basically ciphering with inverse
    }

    void decipher(char *name_fin, char *name_fout)
    {
        std::ifstream fin(name_fin);
        std::ofstream fout(name_fout);

        size_t text_length = amine::getTextLength(fin);

        // Vector holding a shift and its chi-squared stat for the input file (26 pairs)
        std::vector<std::pair<int, double>> v_chi_squares;

        // Brute force: trying to apply every shift possible on the ciphered text file
        for (int currShift = 1; currShift <= 26; ++currShift)
        {
            std::array<size_t, 26> arr_freq; // basically, for each shift, the character frequency array of the text
            std::fill_n(arr_freq.begin(), 26, 0);

            // Foreach character, applying the shift and incrementing frequency
            char currChar;
            while (fin.get(currChar))
            {
                if (currChar >= 'a' && currChar <= 'z')
                {
                    currChar = char(int(currChar + currShift - 97) % 26 + 97); // applying shift on current char
                    ++arr_freq[int(currChar) - int('a')];                      // incrementing its frequency
                }
            }
            amine::resetFileHead(fin);

            // Computing chi square for the current shifted frequency of each character
            double chi = .0;
            for (size_t j = 0; j < 26; j++)
            {
                chi += (std::pow((arr_freq[j] - (text_length * amine::english[j])), 2) / (text_length * amine::english[j]));
            }

            v_chi_squares.push_back(std::make_pair(currShift, chi / 10000));
        }
        fin.close();
        fout.close();

        // Tring to find the smallest chi to discover the shift
        std::pair<int, double> smallest_chi = v_chi_squares.at(0);
        for (const auto &currPair : v_chi_squares)
        {
            if (currPair.second < smallest_chi.second)
                smallest_chi = currPair;
            std::cout << "Shift = " << currPair.first << ", with Chi = " << currPair.second << std::endl;
        }
        int guessed_shift = 26 - smallest_chi.first; // inverse cause it's a ciphered file
        std::cout << "Guessed shift is: " << guessed_shift << std::endl;
        decipher(name_fin, name_fout, guessed_shift);
    }
}