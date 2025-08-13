#include "ExpStack.h"

#include <Windows.h>

ExpStack::ExpStack()
	:count(0)
{
	Clear();
}

void ExpStack::Clear()
{
	memset(data, 0, sizeof(float) * stackCount);
	count = 0;
}

bool ExpStack::IsEmpty() const
{
	return count == 0;
}

bool ExpStack::IsFull() const
{
	return count == stackCount;
}

int ExpStack::Count() const
{
	return count;
}

bool ExpStack::Push(float exp)
{
	if (IsFull())
	{
		MessageBoxA(nullptr, "스택이 가득 차 추가 불가", "Stack Push Error", MB_OK);

		std::cout << "스택이 가득차 추가 불가\n";

		return false;
	}

	data[count] = exp;
	++count;

	return true;
}

float ExpStack::Pop()
{
	if (IsEmpty())
	{
		MessageBoxA(nullptr, "스택이 비어 추출 불가", "Stack Push Error", MB_OK);

		std::cout << "스택이 비어 추출 불가\n";

		return -1.f;
	}

	--count;
	return data[count];
}