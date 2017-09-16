#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include "hash.h"

void openInputStream(std::ifstream &in, bool openDict = true);
void openOutputStream(std::ofstream &out);
void loadDictionary(HashTable &hashTable, std::ifstream &dictionary);
void checkDocument(HashTable &hashTable, std::ifstream &infile,
        std::ofstream &outfile);

int main() {
    HashTable hashTable(100000);
    clock_t t1, t2;
    double timeDiff;

    std::ifstream dictionary;
    openInputStream(dictionary, true);

    t1 = clock();
    loadDictionary(hashTable, dictionary);
    t2 = clock();
    timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    std::cout << "Total time (in seconds) to load dictionary: "
        << timeDiff << std::endl;

    std::ifstream infile;
    std::ofstream outfile;
    openInputStream(infile, false);
    openOutputStream(outfile);

    t1 = clock();
    checkDocument(hashTable, infile, outfile);
    t2 = clock();
    timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    std::cout << "Total time (in seconds) to check document: "
        << timeDiff << std::endl;
}

//  Prompts the user for the dictionary or input file and opens the
//  file for reading
void openInputStream(std::ifstream &in, bool openDict) {
    std::string inname;
    if (openDict) {
        std::cout << "Enter name of dictionary: ";
    }
    else {
        std::cout << "Enter name of input file: ";
    }
    std::cin >> inname;
    in.open(inname.c_str());
}

//  Prompts the user for an output file and opens the file for writing
void openOutputStream(std::ofstream &out) {
    std::string outname;
    std::cout << "Enter name of output file: ";
    std::cin >> outname;
    out.open(outname.c_str());
}

void loadDictionary(HashTable &hashTable, std::ifstream &dictionary) {
    std::string line;

    while (std::getline(dictionary, line)) {
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        hashTable.insert(line);
    }
}

void checkDocument(HashTable &hashTable, std::ifstream &infile,
        std::ofstream &outfile) {
    unsigned long lineNumber = 1;
    std::string validChars = "abcdefghijklmnopqrstuvwxyz0123456789-'";

    char ch;
    std::string buffer = "";

    enum State {inWord, betweenWords, flushLongWord};
    State state = inWord;

    while (infile.get(ch)) {
        ch = std::tolower(ch);

        switch (state) {
            case inWord:
                if (validChars.find(ch) != std::string::npos) {
                    if (buffer.length() >= 20) {
                        outfile << "Long word at line " << lineNumber 
                            << ", starts: " << buffer << std::endl;
                        buffer = "";
                        state = flushLongWord;
                    }
                    else {
                        buffer.push_back(ch);
                    }
                }
                else {
                    if (std::any_of(buffer.begin(), buffer.end(), ::isdigit)
                            && !hashTable.contains(buffer)) {
                        outfile << "Unknown word at line " << lineNumber
                            << ": " << buffer << std::endl;
                    }
                }
                break;

            case betweenWords:
                if (validChars.find(ch) != std::string::npos) {
                    buffer.push_back(ch);
                    state = inWord;
                }
                break;

            case flushLongWord:
                if (validChars.find(ch) == std::string::npos) {
                    state = betweenWords;
                }
                break;

        }

        if (ch == '\n') {
            lineNumber++;
        }
    }
}
