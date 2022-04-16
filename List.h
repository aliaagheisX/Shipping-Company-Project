#pragma once
#include"LinkedList.h"
// This is the implementation of the list adt
template<typename T>
class List
{
protected:
	LinkedList<T> List;
public:
	
	int  getLength() const;
	bool isEmpty() const;
	bool insert(int newPosition, const T& newEntry);
	bool remove(int position);
	T getEntry(int position) const;
	void setEntry(int position, const T& newEntry);
};



template<typename T>
 bool List<T>::isEmpty() const
{
	return List.isEmpty();
}


template<typename T>
int List<T>::getLength() const
 {
	 return List.getSize();
 }

template<typename T>
bool List<T>::insert(int newPosition, const T& newEntry)
{
	List.Insert(newEntry, newPosition);
}

template<typename T>
inline bool List<T>::remove(int position)
{
	List.removeIndex(position);
}

template<typename T>
T List<T>::getEntry(int position) const
{

	return List[position];

}

template<typename T>
void List<T>::setEntry(int position, const T& newEntry)
{
	List[position] = newEntry;
}