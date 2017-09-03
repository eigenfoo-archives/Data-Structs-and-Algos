/*
Data Structures and Algorithms Assignment #1: Stacks and Queues
George Ho, Spring 2017

This header file implements stacks.
*/

#ifndef STACK_H
#define STACK_H

//  Class declaration for Stack
template <typename T>
class Stack: public SimpleList<T>
{
public:
  void push(T val);
  T pop();
  explicit Stack(string stackName);
};

//  Push onto the stack: i.e. insert at the start of the SimpleList
template <typename T>
void Stack<T>::push(T val)
{
  SimpleList<T>::insertAtStart(val);
}

//  Pop from the stack: i.e. remove from the start of the SimpleList
template <typename T>
T Stack<T>::pop()
{
  return SimpleList<T>::removeFromStart();
}

//  Constructor for the stack
template <typename T>
Stack<T>::Stack(string stackName):SimpleList<T>(stackName)
{}

#endif
