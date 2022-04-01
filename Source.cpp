#include <iostream>
#include "PiorityQueue.h"
using namespace std;
int main() {
	PiorityQueue<int> q;
	q.enqueue(5);
	q.enqueue(3);
	q.enqueue(5);
	q.enqueue(8);
	q.enqueue(1);
	while (!q.isEmpty()){
		cout <<q.peekFront() << ' ';
		q.dequeue();
	}
	return 0;
}