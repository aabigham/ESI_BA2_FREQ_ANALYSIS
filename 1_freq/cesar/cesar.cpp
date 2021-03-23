#include <iostream>
#include <fstream>
#include <istream>
#include <string.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>

void cipher(std::ifstream &fin, std::ofstream &fout, int shift);

void uncipher(std::ifstream &fin);

double getCoincidenceIndex(std::array<size_t, 26> freq, size_t text_len);

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Two argument needed.\n";
        return -1;
    }
    else if (strcmp(argv[1], "-c") && strcmp(argv[1], "-u"))
    {
        std::cerr << "Wrong options, must be \"-c\" to cipher or \"-u\" to uncipher your file.\n";
        return -1;
    }

    std::ifstream fin(argv[2], std::ios_base::binary);
    if (fin.fail())
    {
        std::cerr << "Input file could not be opened, are you sure it is a text file ?\n";
        return -1;
    }
    char *name_fin = strtok((char *)argv[2], ".");

    char *name_fout;
    if (!strcmp(argv[1], "-c"))
    {
        int shift = 5;
        name_fout = strcat(name_fin, "-ciphered.txt");
        std::ofstream fout(name_fout);
        for (char c; fin.get(c);)
        {
            if (c >= 'a' && c <= 'z')
                c = char(int(c + shift - 97) % 26 + 97);
            fout << c;
        }
        fout.close();
    }
    else if (!strcmp(argv[1], "-u"))
    {
        name_fout = strcat(name_fin, "-unciphered.txt");
        std::ofstream fout(name_fout, std::ios_base::binary);

        const std::array<double, 26> english = {
            0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
            0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
            0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
            0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
            0.01974, 0.00074};

        std::vector<std::pair<int, double>> chi_squares;
        for (int i = 0; i < 26; ++i)
        {
            int shift = 26 - i;
            size_t text_len = .0;
            std::array<size_t, 26> freq;
            std::fill_n(freq.begin(), 26, 0);
            for (char c; fin.get(c);)
            {
                if (c >= 'a' && c <= 'z')
                {
                    c = char(int(c + shift - 97) % 26 + 97);
                    ++text_len;
                    ++freq[int(c) - int('a')];
                }
            }
            fin.clear();
            fin.seekg(0);
            double chi = .0;
            for (size_t j = 0; j < 26; j++)
            {
                chi += (std::pow((freq[j] - (text_len * english[j])), 2) / (text_len * english[j]));
            }

            chi_squares.push_back(std::make_pair(shift, chi));
        }
        for (const auto &currPair : chi_squares)
        {
            std::cout << "Shift = " << currPair.first << ", Chi = " << currPair.second << std::endl;
        }

        fout.close();
    }

    fin.close();
    std::cout << name_fout << " created\n";
    return 0;
}

double getCoincidenceIndex(std::array<size_t, 26> freq, size_t text_len)
{
    double sum = .0;
    for (const auto &n : freq)
        sum += (double(n) / double(text_len)) * ((double(n) - 1) / (double(text_len) - 1));
    return sum;
}