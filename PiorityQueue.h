#ifndef  _PQUEUE
#define  _PQUEUE
#include "Queue.h"

template <typename T>
class PiorityQueue : public Queue<T> // piority Queue is Queue
{
public:
	void enqueue(const T& e);
};

#endif // ! _PQUEUE


template<typename T>
void PiorityQueue<T>::enqueue(const T& val) {
	this->queue.InsertSorted(val);
}