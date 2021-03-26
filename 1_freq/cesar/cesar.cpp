#include <iostream>
#include <fstream>
#include <string.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <algorithm>

// Letter frequency in english
constexpr static std::array<double, 26> english = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
    0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
    0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
    0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
    0.01974, 0.00074};

// Ciphers "fin" into "fout" according to the shift (can also uncipher)
void cipher(std::ifstream &fin, std::ofstream &fout, int shift);

// Unciphers "fin" into "fout" without the shift
void uncipher(std::ifstream &fin, std::ofstream &fout);

int main(int argc, char const *argv[])
{
    if (argc != 3 && argc != 4) // Checks the number or arguments
    {
        std::cerr << "Wrong number of arguments.\n";
        return -1;
    }
    else if (strcmp(argv[1], "-c") && strcmp(argv[1], "-u")) // Checks the options
    {
        std::cerr << "Wrong options, must be \"-c\" to cipher or \"-u\" to uncipher your file.\n";
        return -1;
    }
    else if (!strcmp(argv[1], "-c") && argc == 3) // If ciphering is chosen but no shift in argument
    {
        std::cerr << "You need a shift value to cipher your file.\n";
        return -1;
    }

    // Opens the input file and check success
    std::ifstream fin(argv[2]);
    if (fin.fail())
    {
        std::cerr << "Input file could not be opened, are you sure it is a text file ?\n";
        return -1;
    }
    // Name of input file to re-use for the output file
    char *name_fin = strtok((char *)argv[2], ".");

    if (!strcmp(argv[1], "-c")) // Ciphering with a shift
    {
        std::cout << "Tried to cipher with a shift.\n";
        try
        {
            int shift = std::stoi(argv[3]);
            if (!(shift >= 1 && shift <= 26))
            {
                std::cerr << "The shift must be between 1 and 26.\n";
                return -1;
            }
            char *name_fout = strcat(name_fin, "-ciphered.txt");
            std::ofstream fout(name_fout); // output file
            cipher(fin, fout, shift);
            fout.close();
            std::cout << name_fout << " created.\n";
        }
        catch (const std::exception &e)
        {
            std::cerr << "Wrong shift value, are you sure it is a number ?\n";
        }
    }
    else if (!strcmp(argv[1], "-u")) // Unciphering
    {
        if (argc == 3) // Unciphering without shift
        {
            std::cout << "tried to uncipher without a shift" << std::endl;
            char *name_fout = strcat(name_fin, "-unciphered.txt");
            std::ofstream fout(name_fout, std::ios_base::binary); // output file
            uncipher(fin, fout);
            fout.close();
            std::cout << name_fout << " created.\n";
        }
        else // Unciphering with shift
        {
            std::cout << "tried to uncipher with a shift" << std::endl;
            try
            {
                int shift = std::stoi(argv[3]);
                if (!(shift >= 1 && shift <= 26))
                {
                    std::cerr << "The shift must be between 1 and 26.\n";
                    return -1;
                }
                shift = 26 - shift;
                char *name_fout = strcat(name_fin, "-unciphered.txt");
                std::ofstream fout(name_fout); // output file
                cipher(fin, fout, shift);
                fout.close();
                std::cout << name_fout << " created.\n";
            }
            catch (const std::exception &e)
            {
                std::cerr << "Wrong shift value, are you sure it is a number ?\n";
            }
        }
    }
    fin.close();
    return 0;
}

void cipher(std::ifstream &fin, std::ofstream &fout, int shift)
{
    // Foreach character, applying the shift
    for (char c; fin.get(c);)
    {
        if (c >= 'a' && c <= 'z')
            c = char(int(c + shift - 97) % 26 + 97);
        fout << c; // Writing in output file
    }
}

void uncipher(std::ifstream &fin, std::ofstream &fout)
{
    // Vector holding the shift value and its chi-squared satistic for the file
    std::vector<std::pair<int, double>> chi_squares;

    // Applying every shift possible on the ciphered text file
    for (int i = 0; i < 26; ++i)
    {
        int shift = 26 - i;
        size_t text_len = 0L;

        // Char frequency for the text with current shift
        std::array<size_t, 26> freq;
        std::fill_n(freq.begin(), 26, 0);

        // Foreach character, applying the shift and incrementing frequency
        for (char c; fin.get(c);)
        {
            if (c >= 'a' && c <= 'z')
            {
                c = char(int(c + shift - 97) % 26 + 97);
                ++text_len;
                ++freq[int(c) - int('a')];
            }
        }
        fin.clear(); // Resetting file head
        fin.seekg(0);

        // Computing chi square for the current shifted frequency, for each character
        double chi = .0;
        for (size_t j = 0; j < 26; j++)
            chi += (std::pow((freq[j] - (text_len * english[j])), 2) / (text_len * english[j]));

        chi_squares.push_back(std::make_pair(shift, chi / 10000));
    }
    for (const auto &[shift, chi] : chi_squares)
        std::cout << "Shift = " << shift << ", Chi = " << chi << std::endl;

    auto it = std::min_element(chi_squares.cbegin(),
                               chi_squares.cend(),
                               [](const std::pair<int, double> p1, const std::pair<int, double> p2) {
                                   return p1.second < p2.second;
                               });

    int shift = chi_squares.at(std::distance(chi_squares.cbegin(), it)).first;
    shift = 26 - shift;
    std::cout << "Guessed key = " << shift << " (lowest chi)." << std::endl;
    cipher(fin, fout, 26 - shift);
}
