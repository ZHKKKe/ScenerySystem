#include "Queue.h"

using namespace std;

// ------------------------------------------------------
// Function implementation for class Queue
// ------------------------------------------------------
template <class T>
Queue<T>::Queue()
{
	head = new QueueNode<T>();
	tail = head;
}

//
template <class T>
bool Queue<T>::IsEmpty()
{
	if (head == tail)
		return true;
	return false;
}

//
template <class T>
void Queue<T>::EnQueue(T elem)
{
	QueueNode<T> *q = new QueueNode<T>(elem);
	tail->next = q;
	tail = tail->next;
}

//
template <class T>
T Queue<T>::DeQueue()
{
	if (head == tail)
	{
		// TODO: throw exception
	}				

	QueueNode<T> *q = head->next;
	QueueNode<T> *tmp = head;
	head = head->next;
	delete(tmp);
	tmp = NULL;
	return q->elem;
}
