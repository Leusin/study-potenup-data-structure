#include <iostream>
#include <vector>
#include "Vector.h"

int main() 
{
	Vector<int> myV;

	const int count = 100;
	for (int i = 0; i < count; ++i) 
	{
		myV.PushBack(i + 1);
	}

	// begin(), end() 만 선언하면 이렇게 쓸 수 있다
	// (신기하다)
	for (auto& e: myV)
	{
		std::cout << e << " ";
	}

	return 0;
}