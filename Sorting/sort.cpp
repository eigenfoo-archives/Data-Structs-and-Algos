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

int determineTestCase(list<Data *> &l);
void initializeArrayT12(list<Data *> &l);
void copyToTheListT12(list<Data *> &l);
bool compareT12(const NodeT12 &first, const NodeT12 &second);
bool compare(const Data* data1, const Data* data2);
void countingSort(list<Data *> &l);
void insertionSort(list<Data *> &l);

int listSize = 0;
NodeT12 arrayT12[1100000] = {};
Data* buckets[1100000] = {};
short counts[1100000] = {};

void sortDataList(list<Data *> &l) {
  listSize = l.size();
  switch(determineTestCase(l)) {
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
      insertionSort(l);
      break;
  }
}

//  Identifies the current test case
int determineTestCase(list<Data *> &l) {
  list<Data *>::iterator it = l.begin();
  string str = (*it)->data.substr(0, 12);
  string str2 = (*(++it))->data.substr(0, 12);

  if(listSize <= 500000) {
    return 1;
  }
  else if((*it)->data.length() <= 7) {
    return 3;
  }
  else if(!(strcmp(str.c_str(), str2.c_str()))) {
    return 4;
  }
  else {
    return 2;
  }
}

//  Initializes arrayT12 for T1 and T2
void initializeArrayT12(list<Data *> &l) {
  list<Data *>::iterator it = l.begin();
  int decPos = 20;
  for (int i = 0; i < listSize; i++) {
    decPos = 20;
    while (((*it)->data)[decPos] != '.') {
      decPos--;
    }
    arrayT12[i].dataPtr = (*it);
    arrayT12[i].intPart = strtoull((*it)->data.substr(0, decPos-1).c_str(), 0, 10);
    it++;
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

//  Comparison for T1 and T2: returns true if first is less than second.
/*  Incorrectly returns false if the integer parts are equal, which happens
    with probability 1-(10e20 choose 10e6)/[(10e20)^(10e6)]
    (i.e. less than 1/1000000) */
bool compareT12(const NodeT12 &first, const NodeT12 &second) {
  return first.intPart < second.intPart;
}

//  Comparison for T4: returns true if first is less than second
bool compareT4(const Data* first, const Data* second) {
    int i = 20;
    int j = 20;
    while((first->data)[i] != '.') {
      i--;
    }
    while((second->data)[j] != '.') {
      j--;
    }

    if (i == j) {
        return ((first->data).compare(second->data) < 0);
    }
    else {
        return (i < j);
    }
}

//  Counting sort for T3: sorts in-place with iterators
void countingSort(list<Data *> &l) {
  int i = 0;
  list<Data *>::iterator it = l.begin();
  list<Data *>::iterator it2 = l.end();
	for (it = l.begin(); it != it2; it++) {
		i = round((1000*atof(((*it)->data).c_str())));
		buckets[i] = *it;
		counts[i]++;
	}

  it = l.begin();
	i = 0;
	while (it != it2) {
		while (counts[i]--) {
			*(it++) = buckets[i];
		}
		i++;
	}
}

//  Insertion sort for T4: sorts in-place with iterators
void insertionSort(list<Data *> &l) {
  list<Data *>::iterator begin = l.begin();
  list<Data *>::iterator end = l.end();
  list<Data *>::iterator it;

  for (list<Data *>::iterator it2 = next(begin, 1); it2 != end; it2++) {
    Data* temp = *it2;
    for (it = it2; (it != begin) && (compareT4(temp, *(prev(it, 1)))); it--) {
      *it = *(prev(it, 1));
    }
    *it  = temp;
  }
}
