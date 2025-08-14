#include <iostream>

#include "Queue.h";

int main()
{
	Queue<int> q;

	int out;

	for (int i = 0; i < 10; i++)
	{
		q.Enqueue(i);
	}
	q.Enqueue(3);
	q.Enqueue(5);
	q.Enqueue(4);
	q.Enqueue(2);

	q.Print();

	int v;
	q.Dequeue(v);
	q.Dequeue(v);
	q.Dequeue(v);
	q.Dequeue(v);

	q.Print();

	return 0; 
}