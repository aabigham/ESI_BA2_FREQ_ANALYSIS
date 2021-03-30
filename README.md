# Security course labs files 

## Members 
- Amine-Ayoub Bigham 54985
- Zakaria Bendaimi 54247

## 1st lab : Frequential analysis
Our file structure for this lab looks like this : 
```
1_freq
 ┣ cesar
 ┃ ┣ Makefile
 ┃ ┣ book.txt
 ┃ ┗ cesar.cpp
 ┣ preprocess
 ┃ ┗ Preprocess.java
 ┗ vigenere
 ┃ ┣ Makefile
 ┃ ┣ book.txt
 ┃ ┗ vigenere.cpp
```
### Instructions for this lab : 
First of all, you need to preprocess your **english** text file via the java Preprocess file.

To do so : 
- Go inside the `preprocess/` folder
- Run `javac Preprocess.java` to compile the java program
- Then run `java Preprocess inputFile.txt outputFile.txt ` to run the file

The language we used is C++17 and in each file you will find a Makefile to compile the program. 
To compile and run one of these program, open a terminal in the `cesar/` or `vigenere/` folder, then run the `make` command in your terminal. An executable (accordingly named) will be created.

Running that executable should be done like this : 
- `./nameOfExecutable [options] [file.txt]`

The options are :
- `-c` to **cipher** a file. 
- `-u` to **uncipher** a file (the shift is optional when running this option).

If you choose to **cipher** a file, you will be asked for a key.

If you choose to **uncipher** a file, you will be prompted with the choice of using a key or not, **in that case, choose not to use a key to run the frequential analysis.**

Some examples of running these programs : 
- `./cesar -c book.txt` will **cipher** `book.txt`, you will be asked to enter a key.
- `./cesar -u book.txt` will **uncipher** `book.txt`, you will be asked if you want to enter a key
- `./vigenere -c book.txt` will **cipher** `book.txt`, you will be asked to enter a key.
- `./vigenere -u book.txt` will **uncipher** `book.txt`, you will be asked if you want to enter a key
