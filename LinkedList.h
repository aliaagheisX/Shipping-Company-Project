#pragma once

#include "Node.h"


#include<exception>
using namespace std;

template<typename T>
class LinkedList {
    Node<T>* head;
    Node<T>* tail;
    int size;
public:
    //initalizers
    LinkedList(); //default constructor
    LinkedList(const LinkedList<T>&); //copy constructor
    LinkedList<T>& operator=(const LinkedList <T>&); //assignment operator overloading

//adders
    void addFront(const T& val);
    void addBack(const T& val);
    bool Insert(const T& val, const int& index);
    void InsertSorted(const T& e);

    //removers
    bool removeFront();
    bool removeBack();
    bool removeIndex(int index);
    bool removeValue(const T val);

    //getters
    T& getFront() const;
    T& getBack() const;
    Node<T>* getIterator() const; 
    T& operator[](int index) const;

    bool isEmpty() const;
    int getSize() const;

    //destructor
    ~LinkedList();
};


template<typename T>//default constructor
LinkedList<T>::LinkedList() {
    head = tail = nullptr;
    size = 0;
}

template<typename T>//Copy constructor
LinkedList<T>::LinkedList(const LinkedList<T>& c) {
    Node<T>* copy = c.head;

    while (copy) {
        addBack(copy->getValue());
        copy = copy->getNext();
    }
}


template <typename T>//assignment overloading
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& c) {
    if (this != &c) {//check for not self assignement

        //Delete all Nodes
        while (size) removeFront();

        //copy
        Node<T>* copy = c.head;
        while (copy) {
            addBack(copy->value);
            copy = copy->next;
        }
    }
    return *this;
}



/// <Adding>
/// -- Add Front
/// -- Add Back
/// -- Add By Index
template<typename T>
void LinkedList<T>::addFront(const T& val) {
    Node<T>* newNode = new Node<T>(val, head); // make newNode point to head

    head = newNode;

    if (size == 0) tail = newNode; //specialCaseHandel[0] : if Empty

    size++;
}


template<typename T>
void LinkedList<T>::addBack(const T& val) {

    Node<T>* newNode = new Node<T>(val);

    // specialCaseHandel[0] : if Empty
    if (size == 0) head = newNode; 
    else tail->setNext(newNode); // if  not the prev last element point to it

    tail = newNode;//it become the tail
    size++;
}


template<typename T>
bool LinkedList<T>::Insert(const T& val, const int& index) {

    if (index > size) throw exception("No Index DUDE!"); // check if it's okay to insert



    if (index == 0) addFront(val);

    else if (index == size) addBack(val);
    else {
        Node<T>* newNode = new Node<T>(val);
        Node<T>* temp = head;
        for (int i = 0; i < index - 1; i++) temp = temp->getNext();

        newNode->setNext( temp->getNext() ); // let the nextptr of newNode Be The Same from it's Previous
        temp->setNext(newNode); // make the nextPtr of previousNode = new 
        size++;
    }
    return true;
}

template<typename T>
void LinkedList<T>::InsertSorted(const T& val) {
    Node<T>* it = head;

    if (!it || it->getValue() < val)//insert new head
        addFront(val);
    else {
        while (it->getNext() && val < it->getNext()->getValue())
            it = it->getNext();

        if (!it->getNext())
            addBack(val);

        else {
            Node<T>* newNode = new Node<T>(val, it->getNext());
            it->setNext(newNode);
            size++;
        }
    }
}
template<typename T>
T& LinkedList<T>::operator[](int index) const {
    /*if (index >= size) throw exception("OUT OF RANGE");

    Node<T>* ptr = head;
    for (int i = 0; i < index; i++)
        ptr = ptr->next;
    return ptr->value;*/
    
}


template<typename T>
bool LinkedList<T>::removeFront() {
    if (size == 0) throw exception("Empty DUDE!"); // case: no elements to remove

    Node<T>* temp = head->getNext();//store  element after head

    delete head; //delete head

    head = temp; //newHead = temp

    size--;

    return true;
}

template<typename T>
bool LinkedList<T>::removeBack() {
    if (size == 0) throw exception("Empty DUDE!"); // case: no elements to remove

    //1- get Previous tail
    Node<T>* prevTail = head;
    while (prevTail && prevTail->getNext() != tail) prevTail = prevTail->getNext();//loop till next == tail or not the end

    //2-delete tail
    delete tail;

    //3-make tail point to new tail
    tail = prevTail;

    // Handel if become Empty DO NOTHING
    // if not set NEXT to null
    if (tail) tail->setNext(nullptr); 

    size--;
    return true;
}

template<typename T>
bool LinkedList<T>::removeIndex(int index) {
    if (index >= size) throw exception("No Index DUDE!"); // case: index doesn't exist

    if (index == 0) removeFront();
    else if (index == size - 1) removeBack();
    else {
        //1- get node before it
        Node<T>* prevIndex = head;
        for (int i = 0; i < index - 1; i++)
            prevIndex = prevIndex->getNext();

        //2-store what we want to delete
        Node<T>* nodeIndex = prevIndex->getNext();

        //3-make the previous pointing to the next of the deleted node 
        prevIndex->setNext(nodeIndex->getNext());

        //4-delete node
        delete nodeIndex;

        size--;
    }
    return true;
}


template<typename T>
bool LinkedList<T>::removeValue(const T val) {
    if (size == 0) throw exception("No Value DUDE!");

    Node<T>* target = head; //target node with value
    Node<T>* prev = nullptr;

    //loop till found
    while (target  && target->getValue() != val) 
        prev = target,
        target = target->getNext();

    //if not found
    if (!target) return false;

    //handel if head to remove
    if (target == head) return removeFront();
    
    //handel if tail to remove
    if (target == tail) tail = prev;

    prev->setNext(target->getNext());

    delete target;
    size--;
    return true;
}


template<typename T>
T& LinkedList<T>::getFront() const {
    if (head)
        return head->getValue();
    throw exception("No Head DUDE!");
}

template<typename T>
T& LinkedList<T>::getBack() const {
    if (tail)
        return tail->getValue();
    throw exception("No tail DUDE!");
}


//return head iterator
template<typename T>
Node<T>* LinkedList<T>::getIterator() const {
    return head;
}



template<typename T>
bool LinkedList<T>::isEmpty() const { return size == 0; }


template<typename T>
int LinkedList<T>::getSize() const { return size; }




template<typename T>
LinkedList<T>::~LinkedList() {
    while (size != 0) removeFront();
}


