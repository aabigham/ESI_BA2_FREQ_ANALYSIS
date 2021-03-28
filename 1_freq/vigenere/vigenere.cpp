#include <iostream>
#include <fstream>
#include <string.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <algorithm>

// Coincidence index enlgish
constexpr double ic_english{0.0667};
// Letter frequency in english
constexpr static std::array<double, 26> english{
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
    0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
    0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
    0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
    0.01974, 0.00074};

std::string askKey();
void cipher(std::ifstream &fin, std::ofstream &fout, std::string key);
void uncipher(std::ifstream &fin, std::ofstream &fout, std::string key);
double getCoincidenceIndex(std::array<size_t, 26> freq, size_t text_len);
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

    // Opens the input file and check success
    std::ifstream fin(argv[2]);
    if (fin.fail())
    {
        std::cerr << "Input file could not be opened, are you sure it is a text file ?\n";
        return -1;
    }
    // Name of input file to re-use for the output file
    char *name_fin = strtok((char *)argv[2], ".");

    if (!strcmp(argv[1], "-c")) // Ciphering with a key
    {
        std::cout << "Tried to cipher with a key.\n";
        std::string key = askKey();
        char *name_fout = strcat(name_fin, "-ciphered.txt");
        std::ofstream fout(name_fout); // output file
        cipher(fin, fout, key);
        fout.close();
        std::cout << name_fout << " created.\n";
    }
    else if (!strcmp(argv[1], "-u")) // Unciphering
    {
        char b;
        do
        {
            std::cout << "Tried to unchiper. With a key ? [y/n]" << std::endl;
            std::cin >> b;
        } while (!std::cin.fail() && b != 'y' && b != 'n');

        if (b == 'y')
        {
            std::string key = askKey();
            std::cout << "Unciphering with a key...\n";
            char *name_fout = strcat(name_fin, "-unciphered.txt");
            std::ofstream fout(name_fout); // output file
            uncipher(fin, fout, key);
            fout.close();
            std::cout << name_fout << " created.\n";
        }
        else
        {
            std::cout << "Unciphering without a key...\n";
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

std::string askKey()
{
    std::string key;
    do
    {
        std::cout << "Enter your key : ";
        std::cin >> key;
    } while (!std::cin.fail() && key.size() == 0);
    for (size_t i = 0; i < key.size(); i++)
        key[i] = std::tolower(key[i]);
    return key;
}

void cipher(std::ifstream &fin, std::ofstream &fout, std::string key)
{
    int i = 0;
    for (char c; fin.get(c);)
    {
        if (c >= 'a' && c <= 'z')
            c = (char)(((int)c - 'a' + (int)key[(i++ % key.size())] - 'a') % 26) + 'a';
        fout << c; // Writing in output file
    }
}

void uncipher(std::ifstream &fin, std::ofstream &fout, std::string key)
{
    int i = 0;
    for (char c; fin.get(c);)
    {
        if (c >= 'a' && c <= 'z')
            c = (char)((((int)c - 'a' - (key[(i++ % key.size())] - 'a')) + 26) % 26) + 'a';
        fout << c; // Writing in output file
    }
}

double getCoincidenceIndex(std::array<size_t, 26> freq, size_t text_len)
{
    double sum = .0;
    for (const auto &n : freq)
        sum += (double(n) / double(text_len)) * ((double(n) - 1) / (double(text_len) - 1));
    return sum;
}

void uncipher(std::ifstream &fin, std::ofstream &fout)
{
    // Text lenght
    size_t text_len = 0L;
    for (char c; fin.get(c);)
        if (c >= 'a' && c <= 'z')
            ++text_len;
    fin.clear(); // Resetting file head
    fin.seekg(0);

    int maxKey = 30;
    // Coincidence index for each key
    std::vector<std::pair<int, double>> vic;

    for (int currKey = 2; currKey <= maxKey; currKey++)
    {
        // Frenquecy vector
        std::vector<std::array<size_t, 26>> vFreq(currKey);
        for (auto &arr : vFreq)
            std::fill(arr.begin(), arr.end(), 0);

        int i = 0;
        for (char c; fin.get(c);)
            if (c >= 'a' && c <= 'z')
                ++vFreq.at(i++ % currKey)[(int)c - 97];
        fin.clear();
        fin.seekg(0);

        double ics = .0;
        for (const auto &arr : vFreq)
        {
            ics += getCoincidenceIndex(arr, text_len / currKey);
        }
        // Push l'indice de coincidence pour clé courante
        vic.push_back({currKey, ics / currKey});
    }

    for (const auto &[key, ic] : vic)
        std::cout << "Key " << key << " : " << ic << std::endl;

    //int key_len;

    fout << 'x';
}
