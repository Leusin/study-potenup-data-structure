#pragma once

#include <iostream>

template<typename T, int Size = 10>
class Deque
{
public:
	Deque()
		: size(Size + 1)
	{
		Clear();
	}

	~Deque()
	{
	}

	void Clear()
	{
		memset(data, 0, sizeof(T) * (size));
		front = 0;
	}

	bool IsEmpty() const
	{
		return front == rear;
	}

	bool IsFull() const
	{
		// rear 의 다음 위치가 front 와 같으면 가득 찬 상태 
		return (rear + 1) % size == front;
	}

	bool AddRear(const T& newData)
	{
		if (IsFull())
		{
			std::cout << "Error: 덱이 가득 차 있습니다.\n";
			return false;
		}

		// 뒤(rear) 다음 위치에 새 데이터 추가
		rear = (rear + 1) % size;
		data[rear] = newData;

		return true;
	}

	bool AddFront(const T& newData)
	{
		if (IsFull())
		{
			std::cout << "Error: 덱이 가득 차 있습니다.\n";
			return false;
		}

		// 뒤(rear) 다음 위치에 새 데이터 추가
		data[front] = newData;
		front = (front - 1 + size) % size;

		return true;
	}

	bool DeleteFront(T& outValue)
	{
		if (IsEmpty())
		{
			std::cout << "Error: 덱이 비어 있습니다.\n";
			return false;
		}

		front = (front + 1) % size;
		outValue = data[front];

		//data[front] = 0;
		memset(data + front/*= &data[front]*/, 0, sizeof(T));

		return true;
	}

	bool DeleteRear(T& outValue)
	{
		if (IsEmpty())
		{
			std::cout << "Error: 덱이 비어 있습니다.\n";
			return false;
		}

		outValue = data[rear];
		memset(data + rear/*= &data[front]*/, 0, sizeof(T));

		rear = (rear - 1 + size) % size;

		return true;
	}

	void Print()
	{
		std::cout << "덱 내용:";
		int max = front < rear ? rear : rear + size;

		for (int i = front + 1; i <= max; i++)
		{
			std::cout << " " << data[i % size];
		}

		std::cout << "\n";
	}

private:
	int front = 0;
	int rear = 0;
	int size = 0;
	T data[Size + 1] = {};
};