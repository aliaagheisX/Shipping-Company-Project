#pragma once
#include "LinkedList.h"

template<typename T>
class Queue
{
protected:
	LinkedList<T> queue;
public:
	void enqueue(const T&);
	bool dequeue();

	const T peekFront() const;

	bool isEmpty() const;
	int getSize() const;
	void Print(UI* ptr) const ;
};

template<typename T>
void Queue<T>::enqueue(const T& val) {
	queue.addBack(val);
}

template<typename T>
bool Queue<T>::dequeue() {
	return queue.removeFront();
}


template<typename T>
const T Queue<T>::peekFront() const{
	return queue.getIterator()->getValue();
}


template<typename T>
bool Queue<T>::isEmpty() const {
	return queue.isEmpty();
}

template<typename T>
int Queue<T>::getSize() const {
	return queue.getSize();
}

template<typename T>
void Queue<T>::Print(UI* ptr) const
{
	queue.Print(ptr);
}


