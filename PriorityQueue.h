#pragma once
#include"PriorityKey.h"
#include"UI.h"
const int MAX_ARRAY = 1000;
#include<exception>


template<typename T>
class PriorityQueue
{

private:
	PriorityKey<T>** arr;
	const int capacity;
	int size;

	void bubbleUP();

	int minChild(int index);

	void bubbleDown();

	void swap(PriorityKey<T>*& val1, PriorityKey<T>*& val2);


public:
	PriorityQueue(int s = MAX_ARRAY);

	void enqueue(T& val, int key);

	bool dequeue();

	T& peekFront() ;

	int getSize() const { return size; };

	void Print(UI * ,char seperator = ',') const;

	bool isEmpty() const;

	~PriorityQueue();


};


template<typename T>
PriorityQueue<T>::PriorityQueue(int s) : capacity(s), size(0) {
	arr = new  PriorityKey<T> *[capacity];
}

template<typename T>
void PriorityQueue<T>::enqueue(T& val, int key) {

	if (size == capacity) throw std::exception("Piority Queue is FULL");

	PriorityKey<T>* newHeap = new PriorityKey<T>(val, key);
	arr[size++] = newHeap;
	bubbleUP();

}

template<typename T>
bool PriorityQueue<T>::dequeue() {
	if (size == 0) throw std::exception("Piority Queue is Empty");

	swap(arr[0], arr[size - 1]); //swap between root[least node]

	delete arr[size - 1]; //delete the least node

	size--;
	bubbleDown(); //return it to binary again

	return true;
}


template<typename T>
T& PriorityQueue<T>::peekFront()  {
	if (size == 0) throw std::exception("Piority Queue is Empty");

	return arr[0]->getValue();
}

template<typename T>
void PriorityQueue<T>::Print(UI* ptr, char seperator) const {
	if (size == 0) return;
	for (int i = 0; i < size - 1; i++) {
		ptr->Print(arr[i]->getValue(), seperator);
	}
	ptr->Print(arr[size - 1]->getValue(), '\0');

}

template<typename T>
bool PriorityQueue<T>::isEmpty() const
{
	return (size==0);
}

template<typename T>
PriorityQueue<T>::~PriorityQueue() {
	for (int i = 0; i < size; i++) delete arr[i];
}





template<typename T>
void PriorityQueue<T>::bubbleUP() {
	int index = size - 1;
	int parent = (index - 1) / 2;

	while (index > 0 && arr[index]->getKey() < arr[parent]->getKey()) { ///Change Here if you Want MAX HEAP
		swap(arr[index], arr[parent]);
		index = parent;
		parent = (index - 1) / 2;

	}
}

template<typename T>
void PriorityQueue<T>::bubbleDown() {
	int index = 0;
	int minchild = minChild(index); // get smaller child of index

	while (arr[minchild]->getKey() < arr[index]->getKey()) { // check if it's valid
		swap(arr[minchild], arr[index]); // swap if index not a valid parent

		index = minchild;
		minchild = minChild(index);
	}
}


template<typename T>
int PriorityQueue<T>::minChild(int index) { // return same index if no child

	if (2 * index + 1 >= size) return index; // no left child => no child
	///Change Here if you Want MAX HEAP
	if (2 * index + 2 >= size)  return 2 * index + 1;
	else  return (arr[2 * index + 2]->getKey() < arr[2 * index + 1]->getKey()) ? 2 * index + 2 : 2 * index + 1;
};


template<typename T>
void PriorityQueue<T>::swap(PriorityKey<T>*& val1, PriorityKey<T>*& val2) {
	PriorityKey<T>* temp = val1;
	val1 = val2;
	val2 = temp;
}



