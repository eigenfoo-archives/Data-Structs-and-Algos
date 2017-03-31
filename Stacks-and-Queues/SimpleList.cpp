/*
Data Structures and Algorithms Assignment #1: Stacks and Queues
George Ho, Spring 2017

This code implements an abstract base class, SimpleList, from which stacks and
queues are derived. SimpleList is implemented as a linear, singly-linked list.
*/

//  Class declaration for SimpleList
template <typename T>
class SimpleList
{
public:
  virtual void push(T val) = 0;
  virtual T pop() = 0;
  string getListName();
  bool isEmpty();
  SimpleList(string name);

private:
  struct Node;
  Node *start;
  Node *end;
  string listName;

protected:
  void insertAtStart(T val);
  void insertAtEnd(T val);
  T removeFromStart();
};

//  Returns the name of the SimpleList
template <typename T>
string SimpleList<T>::getListName()
{
  return listName;
}

//  Checks if the SimpleList is empty. Note that start == NULL is sufficient to
//  guarantee that a SimpleList is empty.
template <typename T>
bool SimpleList<T>::isEmpty()
{
  return (start == NULL);
}

//  Constructor for SimpleList
template <typename T>
SimpleList<T>::SimpleList(string name)
{
  listName = name;
  start = NULL;
  end = NULL;
}

//  Class definition for Node
template <typename T>
struct SimpleList<T>::Node
{
  T entry;
  Node *next;

  Node(T value, Node* ptr)
  {
    entry = value;
    next = ptr;
  }
};

//  Inserts a Node at the start of the SimpleList (for stacks)
template <typename T>
void SimpleList<T>::insertAtStart(T value)
{
  Node *newNode = new Node(value, start);
  start = newNode;
}

//  Inserts a Node at the end of the SimpleList (for queues)
template <typename T>
void SimpleList<T>::insertAtEnd(T value)
{
  Node *newNode = new Node(value, NULL);
  /*  When pushing onto an empty queue, make sure start points to the new Node.
  Otherwise, make the current end Node point to the new Node.  */
  ((end == NULL) ? start : (end->next)) = newNode;
  end = newNode;
}

//  Removes a Node from the start of the SimpleList (for both stacks and queues)
template <typename T>
T SimpleList<T>::removeFromStart()
{
  Node *ptr = start;
  T value = ptr->entry;
  /*  When removing the last Node, make sure end points to NULL, and not to
  garbarge. Note that start is also made to point to NULL on the next line.  */
  if (ptr->next == NULL)
  {
    end = NULL;
  }
  start = ptr->next;
  delete ptr;
  return value;
}
