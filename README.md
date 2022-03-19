# Frequential Analysis

- [Frequential Analysis](#frequential-analysis)
  - [Author](#author)
  - [Instructions](#instructions)
    - [Packages](#packages)
    - [How to preprocess your book](#how-to-preprocess-your-book)
    - [Compiling](#compiling)
    - [Run the Ciphers](#run-the-ciphers)
    - [Run the deciphers (you will be asked to enter a shift and if you decline, the program will run the cryptanalysis instead)](#run-the-deciphers-you-will-be-asked-to-enter-a-shift-and-if-you-decline-the-program-will-run-the-cryptanalysis-instead)
  - [Automation script](#automation-script)

## Author

- Amine-Ayoub Bigham

## Instructions

### Packages

First, you will need java and c++ building tools (if not already installed): 

```bash
$ sudo apt update 
$ sudo apt install build-essential default-jdk default-jre 
```

### How to preprocess your book

An already preprocessed book is available in the repo (`mybook.txt`). However, if you want to use your own personal book, please put it inside the folder and run:

```bash
$ javac PreprocessText.java
$ java PreprocessText <your_input_book.txt> <your_preprocessed_output.txt>
```

You now have a preprocessed book file that can be used to run the algorithms on. 

### Compiling

To compile the different files: 

- run `make` in your terminal, you will now have two binaries : `cesar` and `vigenere`   

### Run the Ciphers

- `./cesar -c <mybook.txt> <ciphered.txt>`
- `./vigenere -c <mybook.txt> <ciphered.txt>`

### Run the deciphers (you will be asked to enter a shift and if you decline, the program will run the cryptanalysis instead)

- `./cesar -d <ciphered.txt> <deciphered.txt>`
- `./vigenere -d <ciphered.txt> <deciphered.txt>`

## Automation script

The `script.sh` file will run everything for you in the perfect order, using the example book already present in the repo:

- `chmod +x script.sh`
- `./script.sh` 