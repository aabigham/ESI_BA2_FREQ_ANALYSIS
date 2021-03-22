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
 ┣ vigenere
 ┃ ┣ Makefile
 ┃ ┣ vigenere.cpp
 ┃ ┗ book.txt
 ┗ removeSpaces.cpp
```
### Instructions for this lab : 
In each file you will find a Makefile used for compiling the program. 

To compile and run one of these program, open a terminal in the `cesar/` or `vigenere/` folder and then run the `make` command in your terminal. An executable will be created.

Running that executable will look like this : 
- `./nameOfExecutable [options] [file.txt]`

The options are :
- `-c` to **cipher** a file. 
- `-u` to **uncipher** a file. 

Some examples of running these programs: 
- `./cesar -c book.txt` will create a ciphered version the `book.txt` file, using the cesar method.
- `./cesar -u book-ciphered.txt` will create a ciphered version the `book-ciphered.txt` file, using the cesar method.
