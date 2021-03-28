CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra -pedantic -g -fsanitize=address -O2

SRC = vigenere.cpp 
EXEC = vigenere

all: $(EXEC)

$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(EXEC) *unciphered* *ciphered*