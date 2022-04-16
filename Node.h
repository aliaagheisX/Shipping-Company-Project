#pragma once
template < typename T>
class Node
{
private:
	T value; // A data value
	Node<T>* next; // Pointer to next node
public:
	Node();
	Node(const T& v);
	Node(const T& v, Node<T>* n);

	void setItem(const T& v);
	void setNext(Node<T>* n);

	T getValue() const;
	Node<T>* getNext() const;
}; 


template < typename T>
Node<T>::Node() : next(nullptr) {}

template < typename T>
Node<T>::Node(const T& v) : value(v), next(nullptr) {}


template < typename T>
Node<T>::Node(const T& v, Node<T>* n) : value(v), next(n) {}

template < typename T>
void Node<T>::setItem(const T& v)
{
	value = v;
}

template < typename T>
void Node<T>::setNext(Node<T>* n)
{
	next = n;
}

template < typename T>
T Node<T>::getValue() const
{
	return value;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}