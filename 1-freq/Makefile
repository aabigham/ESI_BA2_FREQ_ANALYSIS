CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

EXEC = removeSpaces cesar vigenere

all: $(EXEC)

removeSpaces : removeSpaces.cpp
	$(CXX) $(LDFLAGS) -o $@ $^ $(LBLIBS)

cesar : cesar.cpp
	$(CXX) $(LDFLAGS) -o $@ $^ $(LBLIBS)

vigenere : vigenere.cpp
	$(CXX) $(LDFLAGS) -o $@ $^ $(LBLIBS)

clean:
	rm -rf $(EXEC)