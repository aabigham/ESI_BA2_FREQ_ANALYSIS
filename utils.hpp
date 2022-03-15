#include <array>
#include <fstream>
#include <iomanip>
#include <array>

namespace amine
{
    // English language letter frequency
    constexpr static std::array<double, 26> english{
        0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
        0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
        0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
        0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
        0.01974, 0.00074};

    char askYesNo()
    {
        char answer;
        do
        {
            std::cout << "Do you want to use a shift/key to decipher ? (type 'n' to run the cryptanalysis) [y/n] "
                      << std::endl;
            std::cin >> answer;
        } while (!std::cin.fail() && answer != 'y' && answer != 'n');
        return answer;
    }

    /**
     * Asks the cesar shift value to the user
     * */
    int askCesarShift()
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

    void resetFileHead(std::ifstream &fin)
    {
        fin.clear();
        fin.seekg(0);
    }

    size_t getTextLength(std::ifstream &fin)
    {
        size_t text_len = 0L;
        char currChar;
        while (fin.get(currChar))
        {
            if (currChar >= 'a' && currChar <= 'z')
                ++text_len;
        }
        amine::resetFileHead(fin);
        return text_len;
    }

    //

    std::string askVigenereKey()
    {
        std::string key;
        bool valid;
        do
        {
            std::cout << "Please enter your key (at least one character):\n";
            std::cin >> key;
            valid = true;
            for (size_t i{}; i < key.size() && valid; ++i)
                if (!(std::isalpha(static_cast<unsigned char>(key[i])) || std::isspace(static_cast<unsigned char>(key[i]))))
                {
                    valid = false;
                }
        } while (!valid);

        for (size_t i = 0; i < key.size(); i++)
            key[i] = std::tolower(key[i]);

        return key;
    }

    double getCoincidenceIndex(std::array<size_t, 26> freq, size_t text_len)
    {
        double sum = .0;
        for (const auto &n : freq)
            sum += (double(n) / double(text_len)) * ((double(n) - 1) / (double(text_len) - 1));
        return sum;
    }
}