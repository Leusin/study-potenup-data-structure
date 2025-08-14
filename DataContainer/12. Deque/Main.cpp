#include <iostream>
#include "Deque.h"

int main()
{
	Deque<int> dq;

	for (int i = 1; i < 11; i++)
	{
		if (i % 2 == 0)
		{
			dq.AddFront(i);
		}
		else
		{
			dq.AddRear(i);
		}
	}

	dq.Print();

	return 0;
}