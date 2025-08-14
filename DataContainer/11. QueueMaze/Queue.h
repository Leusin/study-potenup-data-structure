#pragma once

template<typename T, int Size = 10>
class Queue
{
public:
	Queue()
		: size(Size + 1)
	{
		Clear();
	}

	~Queue()
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

	bool Enqueue(const T& newData)
	{
		if (IsFull())
		{
			std::cout << "Error: 큐가 가득 차 있습니다.\n";
			return false;
		}

		// 뒤(rear) 다음 위치에 새 데이터 추가
		rear = (rear + 1) % size;
		data[rear] = newData;

		return true;
	}

	bool Dequeue(T& outValue)
	{
		if (IsEmpty())
		{
			std::cout << "Error: 큐가 비어 있습니다.\n";
			return false;
		}

		front = (front + 1) % size;
		outValue = data[front];

		//data[front] = 0;
		memset(data + front/*= &data[front]*/, 0, sizeof(T));

		return true;
	}

	void Print()
	{
		std::cout << "큐 내용:";
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