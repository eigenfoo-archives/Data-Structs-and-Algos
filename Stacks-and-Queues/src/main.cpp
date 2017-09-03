/*
Data Structures and Algorithms Assignment #1: Stacks and Queues
George Ho, Spring 2017

This code takes in an input file of commands (to create, push to or pop from
stacks and queues of ints, doubles and strings), and parses and processes the
commands as described in the assignment prompt.
*/

using namespace std;

#include <iostream>         //  cout, cin
#include <fstream>          //  ifstream, ofstream, open
#include <string>           //  string class
#include <list>             //  list class
#include <sstream>          //  stringstream
#include <stdlib.h>         //  atoi, atof

#include "SimpleList.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "main.hpp"

ifstream infile;
ofstream outfile;
list<SimpleList<int> *> listSLi;
list<SimpleList<double> *> listSLd;
list<SimpleList<string> *> listSLs;

int main()
{
  openInputStream(infile);
  openOutputStream(outfile);

  string inputLine;
  while (getline(infile, inputLine))
  {
    parseAndProcessLine(inputLine);
  }

  return 0;
}

//  Prompts the user for an input file and opens the file for reading
void openInputStream(ifstream &in)
{
  string inname;
  cout << "Enter name of input file: ";
  cin >> inname;
  in.open(inname.c_str());
}

//  Prompts the user for an output file and opens the file for writing
void openOutputStream(ofstream &out)
{
  string outname;
  cout << "Enter name of output file: ";
  cin >> outname;
  out.open(outname.c_str());
}

//  Splits an input line, and processes the line depending on the datatype
void parseAndProcessLine(string inputLine)
{
  outfile << "PROCESSING COMMAND: " << inputLine << endl;

  /*  Splits the input line into words using string streams. If there are only
  2 words (i.e. the command is pop), words[2] will be empty.  */
  string buffer;
  stringstream strstream(inputLine);
  string* words = new string[3];
  int i = 0;
  while (strstream >> buffer)
  {
    words[i++] = buffer;
  }

  //  Process line depending on datatype
  if (words[1].substr(0, 1) == "i")
  {
    int value;
    if (!words[2].empty())
    {
      value = atoi(words[2].c_str());
    }
    processLine(listSLi, words, value);
  }
  else if (words[1].substr(0, 1) == "d")
  {
    double value;
    if (!words[2].empty())
    {
      value = atof(words[2].c_str());
    }
    processLine(listSLd, words, value);
  }
  else if (words[1].substr(0, 1) == "s")
  {
    processLine(listSLs, words, words[2]);
  }
}
