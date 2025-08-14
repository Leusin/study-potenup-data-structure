#pragma once

const int maxQueueCount = 100;

template<typename T>
class Queue
{
public:
	Queue()
	{
		Clear();
	}

	~Queue()
	{
	}

	void Clear()
	{
		memset(data, 0, sizeof(T) * maxQueueCount);
		front = 0;
	}

	bool IsEmpty() const
	{
		return front == rear;
	}

	bool IsFull() const
	{
		// rear 의 다음 위치가 front 와 같으면 가득 찬 상태 
		return (rear + 1) % maxQueueCount == front;
	}

	bool Enqueue(T newData)
	{
		if (IsFull())
		{
			std::cout << "Error: 큐가 가득 차 있습니다.\n";
			return false;
		}

		// 뒤(rear) 다음 위치에 새 데이터 추가
		rear = (rear + 1) % maxQueueCount;
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
		
		front = (front + 1) % maxQueueCount;
		outValue = data[front];

		return true;
	}

private:
	int front = 0;
	int rear = 0;
	T data[maxQueueCount];
};