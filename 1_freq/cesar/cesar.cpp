#include <iostream>
#include <fstream>
#include <string.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <algorithm>

// Letter frequency in english
constexpr static std::array<double, 26> english{
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
    0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
    0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
    0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
    0.01974, 0.00074};

int askShift();
void cipher(std::ifstream &fin, std::ofstream &fout, int shift); // Can cipher or unciper with a shift
void uncipher(std::ifstream &fin, std::ofstream &fout);

int main(int argc, char const *argv[])
{
    if (argc != 3) // Checks the number or arguments
    {
        std::cerr << "Wrong number of arguments.\n";
        return -1;
    }
    else if (strcmp(argv[1], "-c") && strcmp(argv[1], "-u")) // Checks the options
    {
        std::cerr << "Wrong options, must be \"-c\" to cipher or \"-u\" to uncipher your file.\n";
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
        std::cout << "Trying to cipher with a shift.\n";
        int shift = askShift();
        std::cout << "Ciphering with shift " << shift << "...\n";
        char *name_fout = strcat(name_fin, "-ciphered.txt");
        std::ofstream fout(name_fout); // output file
        cipher(fin, fout, shift);
        fout.close();
        std::cout << name_fout << " created.\n";
    }
    else if (!strcmp(argv[1], "-u")) // Unciphering
    {
        char b;
        do
        {
            std::cout << "Do you want to use a shift to uncipher ? [y/n]" << std::endl;
            std::cin >> b;
        } while (!std::cin.fail() && b != 'y' && b != 'n');

        if (b == 'y')
        {
            int shift = askShift();
            std::cout << "Unciphering with shift " << shift << "...\n";
            shift = 26 - shift;
            char *name_fout = strcat(name_fin, "-unciphered.txt");
            std::ofstream fout(name_fout); // output file
            cipher(fin, fout, shift);
            fout.close();
            std::cout << name_fout << " created.\n";
        }
        else
        {
            std::cout << "Unciphering without shift ...\n";
            char *name_fout = strcat(name_fin, "-unciphered.txt");
            std::ofstream fout(name_fout, std::ios_base::binary); // output file
            uncipher(fin, fout);
            fout.close();
            std::cout << name_fout << " created.\n";
        }
    }
    fin.close();
    return 0;
}

int askShift()
{
    int shift;
    bool valid;
    do
    {
        std::cout << "Enter your shift, must be between 1 and 26 : ";
        std::cin >> shift;
        valid = true;
        if (!(shift >= 1 && shift <= 26))
        {
            valid = false;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!valid);
    return shift;
}

// This function can cipher and uncipher at the same time
void cipher(std::ifstream &fin, std::ofstream &fout, int shift)
{
    // Foreach character (that is in the alphabet), applying the shift
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

    // Text lenght
    size_t text_len = 0L;
    for (char c; fin.get(c);)
        if (c >= 'a' && c <= 'z')
            ++text_len;
    fin.clear(); // Resetting file head
    fin.seekg(0);

    // Applying every shift possible on the ciphered text file
    for (int currShift = 1; currShift <= 26; ++currShift)
    {
        // Char frequency for the text with current shift
        std::array<size_t, 26> freq;
        std::fill_n(freq.begin(), 26, 0);

        // Foreach character, applying the shift and incrementing frequency
        for (char c; fin.get(c);)
        {
            if (c >= 'a' && c <= 'z')
            {
                c = char(int(c + currShift - 97) % 26 + 97); // applying shift on current char
                ++freq[int(c) - int('a')];                   // incrementing its frequency
            }
        }
        fin.clear(); // Resetting file head
        fin.seekg(0);

        // Computing chi square for the current shifted frequency of each character
        double chi = .0;
        for (size_t j = 0; j < 26; j++)
            chi += (std::pow((freq[j] - (text_len * ::english[j])), 2) / (text_len * ::english[j]));

        chi_squares.push_back(std::make_pair(currShift, chi / 10000));
    }

    // finding the minimum chi
    auto min = chi_squares.at(0);
    for (const auto &currPair : chi_squares)
    {
        if (currPair.second < min.second)
            min = currPair;
        std::cout << "Shift = " << currPair.first
                  << ", Chi = " << currPair.second << std::endl;
    }
    int gShift = 26 - min.first; // Guessed shift
    std::cout << "Guessed shift = " << gShift << std::endl;
    cipher(fin, fout, 26 - gShift);
}
