CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra -pedantic -g -fsanitize=address -O3

SRC = cesar.cpp 
EXEC = cesar

all: $(EXEC)

$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(EXEC) *unciphered* *ciphered*