/*
Data Structures and Algorithms Assignment #1: Stacks and Queues
George Ho, Spring 2017

This header file implements queues.
*/

#ifndef QUEUE_H
#define QUEUE_H

//  Class declaration for Queue
template <typename T>
class Queue: public SimpleList<T>
{
public:
  void push(T val);
  T pop();
  Queue(string queueName);
};

//  Push onto the queue: i.e. insert at the end of the SimpleList
template <typename T>
void Queue<T>::push(T val)
{
  SimpleList<T>::insertAtEnd(val);
}

//  Pop from the queue: i.e. remove from the start of the SimpleList
template <typename T>
T Queue<T>::pop()
{
  return SimpleList<T>::removeFromStart();
}

//  Constructor for the queue
template <typename T>
Queue<T>::Queue(string queueName):SimpleList<T>(queueName)
{}

#endif
