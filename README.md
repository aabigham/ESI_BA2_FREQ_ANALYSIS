# Security course labs files 

## Members 
- Amine-Ayoub Bigham 54985
- Zakaria Bendaimi 54247

## 1st lab : Frenquential analysis
Our file structure for this lab looks like this : 
```
1_freq
 ┣ cesar
 ┃ ┣ Makefile
 ┃ ┣ book.txt
 ┃ ┗ cesar.cpp
 ┣ preprocess
 ┃ ┣ Preprocess.java
 ┃ ┣ book-preprocessed.txt
 ┃ ┗ book.txt
 ┗ vigenere
   ┣ Makefile
   ┣ vigenere.cpp
   ┗ book.txt

```
### Instructions for this lab : 
First of all, you need to preprocess your text file via the java Preprocess file.
To do so : 
- go inside the `preprocess/` folder
- run `javac Preprocess.java` to compile the java program
- then run `java Preprocess inputFile.txt outputFile.txt ` to run the file

The language we used is C++17 and in each file you will find a Makefile to compile the program. 
To compile and run one of these program, open a terminal in the `cesar/` or `vigenere/` folder, then run the `make` command in your terminal. An executable (named accordingly) will be created.

Running that executable should be done like this : 
- `./nameOfExecutable [options] [file.txt] [shift]`

The options are :
- `-c` to **cipher** a file. 
- `-u` to **uncipher** a file. 

Some examples of running these programs : 
- `./cesar -c book.txt 4` will create a **ciphered** version of `book.txt`, using the cesar method with a **shift of 4**.
- `./cesar -u book-ciphered.txt` will create a **unciphered** version of `book-ciphered.txt`, **running a cryptanalysis** to find the key by itself (since no key was in argument). 
- `./cesar -u book-ciphered.txt 4` will create a **unciphered** version of `book-ciphered.txt`, using the cesar method with a shift of 4.
