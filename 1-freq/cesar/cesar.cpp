#include <iostream>
#include <fstream>
#include <string.h>
int main(int argc, char const *argv[])
{
    std::cout << "Cesar\n";

    if(argc !=2){
        std::cout << "One argument needed.\n";
             exit(1);
    }

    std::fstream fin;
    fin.open(argv[1]);

    if (fin.fail())
      {
          std::cout << "Input file could not be opened.\n";
          exit(1);
      }


    char *token = strtok((char *)argv[1], ".txt");
    char *s_out = strcat(token, "-ciphered.txt");

     std::ofstream fout(s_out);
     std::string str;
      fin >> str;
      int key=5;
    for (size_t i = 0; i < str.size(); i++)
    {
      
        if(str.at(i)>='a'&&str.at(i)<='z'){
            str.at(i)= char(int(str.at(i)+key-97)%26+97);
        }
        /* code */
    }
    

             fout << str;

        fin.close();
        fout.close();
        std::cout << s_out << " created\n";


    return 0;
}
