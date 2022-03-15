#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>

#include "utils.hpp"

namespace vigenere
{
    void cipher(char *name_fin, char *name_fout, std::string key)
    {
        std::ifstream fin(name_fin);
        std::ofstream fout(name_fout);

        int i = 0;
        char currChar;
        while (fin.get(currChar))
        {
            if (currChar >= 'a' && currChar <= 'z')
                currChar = (char)(((int)currChar - 'a' + (int)key[(i++ % key.size())] - 'a') % 26) + 'a';
            fout << currChar;
        }

        fin.close();
        fout.close();
    }

    void decipher(char *name_fin, char *name_fout, std::string key)
    {
        std::ifstream fin(name_fin);
        std::ofstream fout(name_fout);

        int i = 0;
        char currChar;
        while (fin.get(currChar))
        {
            if (currChar >= 'a' && currChar <= 'z')
                currChar = (char)((((int)currChar - 'a' + (int)key[(i++ % key.size())] - 'a') % 26) % 26) + 'a';
            fout << currChar;
        }

        fin.close();
        fout.close();
    }

    int findKeyLength(char *name_fin, char *name_fout)
    {
        std::ifstream fin(name_fin);
        std::ofstream fout(name_fout);

        size_t text_length = amine::getTextLength(fin);
        int maximum_key = 50; // Completely arbitrary

        std::vector<std::pair<int, double>> ci_vector; // coincidence index vector for each <key length,ci> we are trying
        for (int currLength = 2; currLength <= maximum_key; currLength++)
        {
            // Frenquecy vector for current length
            std::vector<std::array<size_t, 26>> v_freq(currLength);
            for (auto &arr : v_freq)
                std::fill(arr.begin(), arr.end(), 0);

            // decalage allows us to loop on the subtexts only
            int decalage = 0;
            char c;
            while (fin.get(c))
            {
                if (c >= 'a' && c <= 'z')
                    ++v_freq.at(decalage++ % currLength)[(int)c - 97];
            }
            amine::resetFileHead(fin);

            // Coincidence indexes for the current length
            double cis = .0;
            for (const auto &currFreqArray : v_freq)
                cis += amine::getCoincidenceIndex(currFreqArray, text_length / currLength);

            // Push the coincidence index for the current length of key
            ci_vector.push_back({currLength, cis / currLength});
        }

        fin.close();
        fout.close();

        // Setting precision for each coincidence index, makes it easier for us to see
        for (auto &&currPair : ci_vector)
        {
            std::stringstream strstr;
            strstr << std::setprecision(4) << currPair.second;
            currPair.second = std::stod(strstr.str());
            strstr.str(std::string());
            std::cout << "Key Length " << currPair.first << ", Ci : " << std::setprecision(4) << currPair.second << std::endl;
        }

        // Guessing key length
        auto maxPair = ci_vector.at(0);
        for (auto &&currPair : ci_vector)
        {
            if (currPair.second > maxPair.second)
                maxPair = currPair;
        }
        int guessedLength = maxPair.first;

        std::cout << std::endl;
        std::cout << "Guessed key length is : "
                  << guessedLength
                  << " (Don't worry, it's probably a multiple of your key)" << std::endl;

        return guessedLength;
    }

    void decipher(char *name_fin, char *name_fout)
    {
        int guessedLength = findKeyLength(name_fin, name_fout);
        std::cout << "Applying the guessed key length now... Basically applying the cesar bruteforce on each subtext"
                  << std::endl;

        std::ifstream fin(name_fin);
        std::ofstream fout(name_fout);

        size_t text_length = amine::getTextLength(fin);

        // for each subtext, its own <shift, chi square> vector, just like in cesar
        std::vector<std::vector<std::pair<int, double>>> v_v_chi_squares;

        // Applying every shift possible on the ciphered text file
        for (int currentShift = 1; currentShift <= 26; ++currentShift)
        {
            std::vector<std::array<size_t, 26>> v_freq(guessedLength); // Char frequency for the text with current shift
            for (auto &arr : v_freq)
                std::fill(arr.begin(), arr.end(), 0);

            int decalage = 0;
            char currChar;
            while (fin.get(currChar))
            {
                if (currChar >= 'a' && currChar <= 'z')
                {
                    currChar = char(int(currChar + currentShift - 97) % 26 + 97);
                    ++v_freq[decalage++ % guessedLength][(int)currChar - 97];
                }
            }
            amine::resetFileHead(fin);

            std::vector<std::pair<int, double>> v_chi_squares;
            for (int i = 0; i < guessedLength; i++)
            { // Computing chi square for the current shifted frequency of each character
                double chi = .0;
                for (size_t j = 0; j < 26; j++)
                {
                    chi += (std::pow((v_freq[i][j] - ((text_length / 4.) * amine::english[j])), 2) /
                            ((text_length / 4.) * amine::english[j]));
                }
                v_chi_squares.push_back({currentShift, chi / 10000.});
            }
            v_v_chi_squares.push_back(v_chi_squares);
        }

        // nice formatting to see the datas
        for (const auto &currVector : v_v_chi_squares)
        {
            for (const auto &currPair : currVector)
                std::cout << "Shift = " << currPair.first << ", Chi = " << currPair.second << std::endl;
            std::cout << std::endl;
        }

        // For each letter, we need to find its corresponding shift
        int *shifts = new int[guessedLength];
        for (int i = 0; i < guessedLength; i++)
        {
            int j = 0;
            auto min_pair = v_v_chi_squares[j][i];
            while (j < 26)
            {
                if (v_v_chi_squares[j][i].second < min_pair.second)
                {
                    min_pair = v_v_chi_squares[j][i];
                }
                j++;
            }
            shifts[i] = 26 - min_pair.first;
        }

        std::string guessed_keyword;
        for (int i = 1; i <= guessedLength; i++)
        {
            std::cout << "Alphabet shift for letter " << i << " is: " << shifts[i - 1] << std::endl;
            guessed_keyword += char(shifts[i - 1] + 97);
        }
        std::cout << std::endl
                  << "Your key was : " << guessed_keyword << std::endl
                  << "Deciphering...\n\n";

        int decalage = 0;
        char currChar;
        while (fin.get(currChar)) // basically cesar here
        {
            if (currChar >= 'a' && currChar <= 'z')
                currChar = char(int(currChar + (26 - shifts[decalage++ % guessedLength]) - 97) % 26 + 97);
            fout << currChar;
        }
        delete[] shifts;

        fin.close();
        fout.close();
    }
}