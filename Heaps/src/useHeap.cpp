// 
// This program allows the user to manipulate a binary heap.
// The program only inserts string ids with associated keys
// into the heap. The heap class, however, is capable of storing
// arbitrary pointers along with each heap item.
//

#include <iostream>
#include <string>
#include <cstdlib>

#include "heap.h"

using namespace std;

// Read an integer from standard input; if a non-integer is in the
// buffer, the state is fixed and the user is re-prompted;
// either way, the remainder of the buffer is cleared
void getInteger(string message, int &ref)
{
  bool inputGood = false;
  while (!inputGood) {
    inputGood = true;

    cout << message;
    cin >> ref;

    if (!cin) {
      // Non-integer in input buffer, get out of "fail" state
      cin.clear();
      inputGood = false;
    }
    while (cin.get() != '\n'); // clear buffer
  }
}

int main()
{
  int capacity = 0;
  int option;
  string stringTmp;
  int key, id;
  int retVal;

  // Have user choose capacity for binary heap
  getInteger("Choose a capacity for the binary heap: ", capacity);

  // Create the heap
  heap myHeap1(capacity);

  while (1) {
    cout << "\nOptions:" << endl;
    cout << "1 - Insert a new item into the binary heap" << endl;
    cout << "2 - Set the key of a specified item" << endl;
    cout << "3 - Delete a specified item" << endl;
    cout << "4 - Perform a deleteMin" << endl;
    cout << "5 - Quit" << endl;

    // Have the user choose an option
    getInteger("Choose an option: ", option);
    switch(option) {

    case 1:
      // Get data to insert into heap from the user and insert it

      cout << "Enter an id string (to insert): ";
      getline(cin, stringTmp);

      getInteger("Enter an associated integer key: ", key);

      retVal = myHeap1.insert(stringTmp, key);

      cout << "\nCall to 'insert' returned: " << retVal << endl;

      break;

    case 2:
      // Get id string and new key from user and change the key

      cout << "Enter an id string (to change its key): ";
      getline(cin, stringTmp);

      getInteger("Enter an associated integer key: ", key);

      retVal = myHeap1.setKey(stringTmp, key);
      cout << "\nCall to 'setKey' returned: " << retVal << endl;

      break;

    case 3:
      // Get id string from user and delete it from the heap

      cout << "Enter an id string (to delete): ";
      getline(cin, stringTmp);

      retVal = myHeap1.remove(stringTmp, &key);
      cout << "\nCall to 'delete' returned: " << retVal << endl;

      if (retVal == 0) {
	cout << "\nDeleted item with string id \"" << stringTmp
	     << "\" and key " << key << endl;
      }

      break;

    case 4:
      // Perform the deleteMin operation on the heap

      retVal = myHeap1.deleteMin(&stringTmp, &key);
      cout << "\nCall to 'deleteMin' returned: " << retVal << endl;

      if (retVal == 0) {
	cout << "\nDeleted item with string id \"" << stringTmp
	     << "\" and key " << key << endl;
      }

      break;

    case 5:
      cout << "\nGoodbye!" << endl;
      exit(0);

    default:
      cerr << "Error, that input is not valid!" << endl;
      exit (1);
    }
  }

  cerr << "Error, we should never get here!" << endl;
  exit (1);
}
