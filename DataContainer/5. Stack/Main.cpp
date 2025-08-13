#include <iostream>
//#include "ExpStack.h"
#include "Stack.h"
#include <stack>

int main()
{
	//ExpStack stack;
	Stack<float> stackFloat;

	stackFloat.Push(15.0f);
	stackFloat.Push(35.0f);
	stackFloat.Push(25.0f);

	while (!stackFloat.IsEmpty())
	{
		std::cout << "POP: " << stackFloat.Pop() << "\n";
	}

	return 0;
}