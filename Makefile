all: cesar vigenere

cesar:cesar.cpp
	g++ -std=c++17 -Wall -Werror -Wextra -pedantic -g -fsanitize=address -O2 $^ -o $@

vigenere:vigenere.cpp
	g++ -std=c++17 -Wall -Werror -Wextra -pedantic -g -fsanitize=address -O2 $^ -o $@

clean: 
	rm -rf cesar vigenere *ciphered* *deciphered*