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
#include <string>           //  string
#include <list>             //  list
#include <sstream>          //  stringstream
#include <stdlib.h>         //  atoi, atof
#include "SimpleList.cpp"
#include "Stack.cpp"
#include "Queue.cpp"
#include "main.h"

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

  /*  Print a PROCESSING COMMAND line without an endl, so as to avoid newlines
  at the beginning and end of the output file. This also accounts for the
  strange placement of endl's at the start of all printed lines.  */
  getline(infile, inputLine);
  outfile << "PROCESSING COMMAND: " << inputLine;
  parseAndProcessLine(inputLine);

  while (getline(infile, inputLine))
  {
    outfile << endl << "PROCESSING COMMAND: " << inputLine;
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
    int foo;
    if (!words[2].empty())
    {
      foo = atoi(words[2].c_str());
    }
    processLine(listSLi, words, foo);
  }
  else if (words[1].substr(0, 1) == "d")
  {
    double foo;
    if (!words[2].empty())
    {
      foo = atof(words[2].c_str());
    }
    processLine(listSLd, words, foo);
  }
  else if (words[1].substr(0, 1) == "s")
  {
    processLine(listSLs, words, words[2]);
  }
}
