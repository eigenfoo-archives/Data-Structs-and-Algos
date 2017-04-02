/*
Data Structures and Algorithms Assignment #1: Stacks and Queues
George Ho, Spring 2017

This header file provides function prototypes and template functions to search
a list (from the provided C++ list class) for a SimpleList, and to process an
input line.
*/

/*  Ensure that template functions can still write to outfile stream. They
do not need to read input (they will be passed parsed commands)   */
extern ofstream outfile;

void openInputStream(ifstream &in);
void openOutputStream(ofstream &out);
void parseAndProcessLine(string inputLine);

//  Searches a given list for a specified SimpleList
template <typename T>
SimpleList<T>* searchForSimpleList(list<SimpleList<T> *> searchList,
                                  string listName)
{
  for (typename list<SimpleList<T> *>::const_iterator it = searchList.begin();
      it != searchList.end(); ++it)
  {
    if ((*it)->getListName() == listName)
    {
      return *it;
    }
  }
  return NULL;
}

//  Process a command, given the parsed command, the relevant list of
//  SimpleLists, and the correctly typecasted value to push
template <typename T>
void processLine(list<SimpleList<T> *> &listSL, string words[], T value)
{
  if (words[0] == "create")
  {
    if (searchForSimpleList(listSL, words[1]) != NULL)
    {
      outfile << "ERROR: This name already exists!" << endl;
    }
    else
    {
      //  inputLine was null-terminated, so we must compare to a
      //  null-terminated string
      if (words[2] == "stack\0")
      {
        Stack<T>* ptrSL = new Stack<T>(words[1]);
        listSL.push_front(ptrSL);
      }
      else if (words[2] == "queue\0")
      {
        Queue<T>* ptrSL = new Queue<T>(words[1]);
        listSL.push_front(ptrSL);
      }
    }
  }
  else if (words[0] == "push")
  {
    SimpleList<T> *ptr = searchForSimpleList(listSL, words[1]);
    if (ptr == NULL)
    {
      outfile << "ERROR: This name does not exist!" << endl;
    }
    else
    {
      ptr->push(value);
    }
  }
  else if (words[0] == "pop")
  {
    SimpleList<T> *ptr = searchForSimpleList(listSL, words[1]);
    if (ptr == NULL)
    {
      outfile << "ERROR: This name does not exist!" << endl;
    }
    else if (ptr->isEmpty())
    {
      outfile << "ERROR: This list is empty!" << endl;
    }
    else
    {
      outfile << "Value popped: " << ptr->pop() << endl;
    }
  }
}
