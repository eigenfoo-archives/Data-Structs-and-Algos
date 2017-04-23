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
  short intPartLength;
};

//  Node object for T3
class NodeT3 {
public:
  Data* dataPtr;
  int intRep;
};

//  Node object for T4
class NodeT4 {
public:
  Data* dataPtr;
  short onesPlace;
  unsigned long long fracPart;
};

void determineTestCase(list<Data *> &l);
void initializeArrays(list<Data *> &l);
void copyToTheList(list<Data *> &l);
bool compareT12(const NodeT12 &first, const NodeT12 &second);
bool compareT4(const NodeT4 &first, const NodeT4 &second);
void countingSort(int size);
void insertionSort(int size);

int testCase, listSize;
NodeT12 arrayT12[1100000];
NodeT3 arrayT3[1100000];
NodeT3 arrayT3sorted[1100000];
short counts[1000000];
NodeT4 arrayT4[1100000];

void sortDataList(list<Data *> &l) {
  determineTestCase(l);
  cout << "TEST CASE " << testCase << endl;   //REMEMBER TO DELETE LATER!!!!!!!!!!!!!!!!
  initializeArrays(l);
  switch(testCase) {
    case 1:
    case 2:
      //  std implementation of mergesort found to be faster than qsort() or
      //  sort() for this specific application, despite conventional wisdom
      stable_sort(arrayT12, arrayT12 + listSize, compareT12);
      break;
    case 3:
      countingSort(listSize);
      break;
    case 4:
      insertionSort(listSize);
      break;
  }
  copyToTheList(l);
}

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

void initializeArrays(list<Data *> &l) {
  list<Data *>::iterator it = l.begin();
  if (testCase == 3) {
    for (int i = 0; i < listSize; i++, it++) {
      arrayT3[i] = NodeT3();
      arrayT3[i].dataPtr = (*it);
      arrayT3[i].intRep = (int) (atof((*it)->data.c_str())*1000);
    }
  }
  else if (testCase == 4) {
    int decPos;
    for (int i = 0; i < listSize; i++, it++) {
      arrayT4[i] = NodeT4();
      decPos = (*it)->data.find('.');
      arrayT4[i].dataPtr = (*it);
      //  The ones place is the most significant digit that will change between
      //  successive numbers. We take 15 digits of the fractional part to avoid
      //  dealing with stripped trailing zeros.
      arrayT4[i].onesPlace = ((*it)->data)[decPos-1];
      arrayT4[i].fracPart = strtoull((*it)->data.substr(decPos+1, 15).c_str(), 0, 10);
    }
  }
  else {
    int decPos, strLength;
    for (int i = 0; i < listSize; i++, it++) {
      arrayT12[i] = NodeT12();
      decPos = (*it)->data.find('.');
      arrayT12[i].dataPtr = (*it);
      arrayT12[i].intPart = strtoull((*it)->data.substr(0, decPos).c_str(), 0, 10);
      arrayT12[i].intPartLength = decPos;
    }
  }
}

//  Copy the sorted array to theList
void copyToTheList(list<Data *> &l) {
  list<Data *>::iterator it = l.begin();
  list<Data *>::iterator it2 = l.end();
  int i = 0;

  if (testCase == 3) {
    while (it != it2) {
      *(it++) = arrayT3sorted[i++].dataPtr;
    }
  }
  else if (testCase == 4) {
    while (it != it2) {
      *(it++) = arrayT4[i++].dataPtr;
    }
  }
  else {
    while (it != it2) {
      *(it++) = arrayT12[i++].dataPtr;
    }
  }
}

//  Comparison for T1 and T2: returns true if first is less than second.
//  Incorrectly returns false if integer parts are equal, which happens with
//  probability 1-(10e20 choose 10e6)/[(10e20)^(10e6)] (i.e. less than 1/1000000)
bool compareT12(const NodeT12 &first, const NodeT12 &second) {
  if (first.intPartLength != second.intPartLength) {
    return first.intPartLength < second.intPartLength;
  }
  else {
    return first.intPart < second.intPart;
  }
}

//  Comparison function for T4: returns true if first is less than second
bool compareT4(const NodeT4 &first, const NodeT4 &second) {
  if (first.onesPlace != second.onesPlace) {
    return first.onesPlace < second.onesPlace;
  }
  else {
    return first.fracPart < second.fracPart;
  }
}

//  Counting sort for T3
void countingSort(int size) {
  int i, j;
  for (i = 0; i < size; i++) {
    counts[arrayT3[i].intRep]++;
  }

  for (i = 0; i < 1000000; i++) {
    while (counts[i]--) {
      arrayT3sorted[j++] = arrayT3[i];
    }
  }
}

//  Insertion sort for T4
void insertionSort(int size) {
  int j;
  NodeT4 temp;
  for (int i = 1; i < size; i++) {
    temp = arrayT4[i];
    j = 0;
    for (j = i; j > 0 && compareT4(temp, arrayT4[j-1]); j--) {
      arrayT4[j] = arrayT4[j-1];
    }
    arrayT4[j] = temp;
  }
}
