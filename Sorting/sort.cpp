// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2017

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds one string
class Data {
public:
  string data;
  Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    string line;
    getline(input, line);
    l.push_back(new Data(line));
  }

  input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
  string filename;
  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->data << endl;
  }

  output.close();
}

void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  list<Data *> theList;
  loadDataList(theList);

  cout << "Data loaded.  Executing sort..." << endl;

  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

/*
Data Structures and Algorithms Assignment #2: Sorting
George Ho, Spring 2017

This code identifies the test case, applying mergesort for T1, T2, counting
sort for T3, and insertion sort for T4.
*/

//  Node object for T1 and T2
class NodeT12 {
public:
  Data* dataPtr;
  unsigned long long intPart;
};

//  Node object for T4
class NodeT4 {
public:
  Data* dataPtr;
  unsigned long long intPart;
  unsigned long long fracPart;
};

void determineTestCase(list<Data *> &l);
void initializeArrayT12(list<Data *> &l);
void initializeArrayT4(list<Data *> &l);
void copyToTheListT12(list<Data *> &l);
void copyToTheListT4(list<Data *> &l);
bool compareT12(const NodeT12 &first, const NodeT12 &second);
bool compareT4(const NodeT4 &first, const NodeT4 &second);
void countingSort(list<Data *> &l);
void insertionSort(int size);

int testCase, listSize;
NodeT12 arrayT12[1100000];
list<Data *> sortedListT3;
Data* ptrsT3[1000000];
short countsT3[1000000];
NodeT4 arrayT4[1100000];

void sortDataList(list<Data *> &l) {
  determineTestCase(l);
  switch(testCase) {
    case 1:
    case 2:
      initializeArrayT12(l);
      /*  std implementation of mergesort found to be faster than qsort() or
        sort() for this specific application, despite conventional wisdom.  */
      stable_sort(arrayT12, arrayT12 + listSize, compareT12);
      copyToTheListT12(l);
      break;
    case 3:
      countingSort(l);
      break;
    case 4:
      initializeArrayT4(l);
      insertionSort(listSize);
      copyToTheListT4(l);
      break;
  }
}

//  Identifies the current test case
void determineTestCase(list<Data *> &l) {
  listSize = l.size();
  list<Data *>::iterator it = l.begin();
  string str = (*it)->data.substr(0, 12);
  string str2 = (*(++it))->data.substr(0, 12);

  if(listSize <= 500000) {
    testCase = 1;
  }
  else if((*it)->data.length() <= 7) {
    testCase = 3;
  }
  else if(!(strcmp(str.c_str(), str2.c_str()))) {
    testCase = 4;
  }
  else {
    testCase = 2;
  }
}

//  Initializes arrayT12 for T1 and T2
void initializeArrayT12(list<Data *> &l) {
  list<Data *>::iterator it = l.begin();
  int decPos = 20;
  for (int i = 0; i < listSize; i++) {
    arrayT12[i] = NodeT12();
    decPos = 20;
    while(((*it)->data)[decPos] != '.') { decPos--; }
    arrayT12[i].dataPtr = (*it);
    arrayT12[i].intPart = strtoull((*it)->data.substr(0, decPos-1).c_str(), 0, 10);
    it++;
  }
}

//  Initializes arrayT4 for T4
void initializeArrayT4(list<Data *> &l) {
  list<Data *>::iterator it = l.begin();
  int decPos = 20;
  for (int i = 0; i < listSize; i++, it++) {
    arrayT4[i] = NodeT4();
    decPos = 20;
    while(((*it)->data)[decPos] != '.') { decPos--; }
    arrayT4[i].dataPtr = (*it);
    arrayT4[i].intPart = strtoull((*it)->data.substr(decPos-15, 16).c_str(), 0, 10);
    arrayT4[i].fracPart = strtoull((*it)->data.substr(decPos+1, 15).c_str(), 0, 10);
  }
}

//  Copy arrayT12 back to theList for T1 and T2
void copyToTheListT12(list<Data *> &l) {
  int i = 0;
  list<Data *>::iterator it = l.begin();
  list<Data *>::iterator it2 = l.end();
  while (it != it2) {
    *(it++) = arrayT12[i++].dataPtr;
  }
}

//  Copy arrayT4 back to theList for T4
void copyToTheListT4(list<Data *> &l) {
  int i = 0;
  list<Data *>::iterator it = l.begin();
  list<Data *>::iterator it2 = l.end();
  while (it != it2) {
    *(it++) = arrayT4[i++].dataPtr;
  }
}

//  Comparison for T1 and T2: returns true if first is less than second.
/*  Incorrectly returns false if the integer parts are equal, which happens
    with probability 1-(10e20 choose 10e6)/[(10e20)^(10e6)]
    (i.e. less than 1/1000000) */
bool compareT12(const NodeT12 &first, const NodeT12 &second) {
  return first.intPart < second.intPart;
}

//  Comparison function for T4: returns true if first is less than second
bool compareT4(const NodeT4 &first, const NodeT4 &second) {
  if (first.intPart != second.intPart) {
    return first.intPart < second.intPart;
  }
  else {
    return first.fracPart < second.fracPart;
  }
}

//  Counting sort for T3; copies sorted list back into theList
void countingSort(list<Data *> &l) {
  int i = 0;
  list<Data *>::iterator it = l.begin();
  list<Data *>::iterator it2 = l.end();

  while (it != it2) {
		i = round(1000*atof(((*it)->data).c_str()));
		ptrsT3[i] = *it;
		countsT3[i]++;
    it++;
	}

  for (int j = 0; j < 1000000; j++) {
		while (countsT3[j]--) {
      sortedListT3.push_back(ptrsT3[j]);
    }
	}

  l.swap(sortedListT3);
}

//  Insertion sort for T4
void insertionSort(int size) {
  NodeT4 temp;
  for (int i = 1; i < size; i++) {
    temp = arrayT4[i];
    int j = 0;
    for (j = i; j > 0 && compareT4(temp, arrayT4[j-1]); j--) {
      arrayT4[j] = arrayT4[j-1];
    }
    arrayT4[j] = temp;
  }
}
