/*
 * Data Structures and Algorithms Assignment #2: Sorting
 * George Ho, Spring 2017
 *
 * This code identifies the test case, applying mergesort for T1, T2, counting
 */

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

    dictionary.close();
    infile.close();
    outfile.close();

    return 0;
}

//  Prompts the user for the dictionary or input file and opens the file for
//  reading.
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

//  Prompts the user for an output file and opens the file for writing.
void openOutputStream(std::ofstream &out) {
    std::string outname;
    std::cout << "Enter name of output file: ";
    std::cin >> outname;
    out.open(outname.c_str());
}

// Loads dictionary line by line. Inserts all lines to hash table (i.e. does
// not ignore words with digits, etc.).
void loadDictionary(HashTable &hashTable, std::ifstream &dictionary) {
    std::string line;

    while (std::getline(dictionary, line)) {
        //std::for_each(line.begin(), line.end(), ::tolower);
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        hashTable.insert(line);
    }
}

// Spellchecks document.
void checkDocument(HashTable &hashTable, std::ifstream &infile,
        std::ofstream &outfile) {
    unsigned long lineNumber = 1;

    char ch;
    std::string buffer = "";

    enum class State {inWord, betweenWords, flushLongWord};
    State state = State::inWord;

    while (infile.get(ch)) {
        ch = std::tolower(ch);

        switch (state) {
            case State::inWord:
                if (((ch>=97) && (ch<=122)) || ((ch>=48) && (ch<=57))
                            || (ch==39) || (ch==45)) {
                    if (buffer.length() >= 20) {
                        outfile << "Long word at line " << lineNumber 
                            << ", starts: " << buffer << std::endl;
                        buffer = "";
                        state = State::flushLongWord;
                    }
                    else {
                        buffer.push_back(ch);
                    }
                }
                else {
                    if (!std::any_of(buffer.begin(), buffer.end(), ::isdigit)
                            && !hashTable.contains(buffer)) {
                        outfile << "Unknown word at line " << lineNumber
                            << ": " << buffer << std::endl;
                    }
                    buffer = "";
                    state = State::betweenWords;
                }
                break;

            case State::betweenWords:
                if (((ch>=97) && (ch<=122)) || ((ch>=48) && (ch<=57))
                            || (ch==39) || (ch==45)) {
                    buffer.push_back(ch);
                    state = State::inWord;
                }
                break;

            case State::flushLongWord:
                if (((ch>=97) && (ch<=122)) || ((ch>=48) && (ch<=57))
                            || (ch==39) || (ch==45)) {
                    state = State::betweenWords;
                }
                break;

        }

        if (ch == '\n') {
            lineNumber++;
        }
    }
}
