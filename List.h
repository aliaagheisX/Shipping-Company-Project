#pragma once
#include"LinkedList.h"
// This is the implementation of the list adt
template<typename T>
class List
{
protected:
	LinkedList<T> list;
public:
	
	int  getSize() const;
	bool isEmpty() const;
	bool insert(int newPosition, const T& newEntry);
	bool remove(int position);
	T getEntry(int position) const;
	void setEntry(int position, const T& newEntry);
	void Print(UI* ptr) const;
};



template<typename T>
 bool List<T>::isEmpty() const
{
	return list.isEmpty();
}


template<typename T>
int List<T>::getSize() const
 {
	 return list.getSize();
 }

template<typename T>
bool List<T>::insert(int newPosition, const T& newEntry)
{
	return list.Insert(newEntry, newPosition);
}

template<typename T>
inline bool List<T>::remove(int position)
{
	return list.removeIndex(position);
}

template<typename T>
T List<T>::getEntry(int position) const
{

	return list[position];

}

template<typename T>
void List<T>::setEntry(int position, const T& newEntry)
{
	list[position] = newEntry;
}


template<typename T>
void List<T>::Print(UI* ptr) const {
	list.Print(ptr);
}
