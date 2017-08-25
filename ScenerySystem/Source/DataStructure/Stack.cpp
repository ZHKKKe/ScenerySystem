#include "Stack.h"

using namespace std;

// ------------------------------------------------------
// Function implementation for class Stack
// ------------------------------------------------------
//
template <class T>
bool Stack<T>::Push(T elem)
{
	if (elemNum >= MAX_S_SIZE)
		return false;

	elems[++elemNum] = elem;
	top = &elems[elemNum];
	return true;
}

//
template <class T>
T Stack<T>::Pop()
{
	if (elemNum < 0)
	{
		top = &elems[0];	
				// TODO: throw exception
	}

	T tmp = elems[elemNum--];
	top = &elems[elemNum];	
	return tmp;
}

//
template <class T>
T Stack<T>::Top()
{
	if (elemNum < 0)
	{
		// TODO: throw exception
	}

	return elems[elemNum];
}

//
template <class T>
int Stack<T>::Size()
{
	return elemNum + 1;
}

template <class T>
bool Stack<T>::IsEmpty()
{
	if (elemNum == -1)
		return true;

	return false;
}

//
template <class T>
bool Stack<T>::IsFull()
{
	if (elemNum >= MAX_S_SIZE)
		return true;

	return false;
}