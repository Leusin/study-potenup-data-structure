#include <iostream>
#include <array>

// 배열 클래스
template<typename T, int size> // 템플릿 비타입 매개변수
class Array
{
public:
	Array()
	{
		memset(data, 0, sizeof(T) * size); // 성분을 0으로 초기화
	}

	~Array()
	{
	}

	int GetSize() const { return size; };

	T& operator[](int index)
	{
		// ?
		if (index < 0 || index > size - 1)
		{
			__debugbreak();
			return data[0];
		}

		return data[index];
	}

private:
	T data[size];
};

int main()
{
	//
	// 1. 스택에 할당되는 배열
	//
	int array[5] /* = { } */; // 균일한 배열 원소들을 0으로 초기화준다
	memset(array, 0, sizeof(int) * 5);

	//
	// 2. 동적 배열(Dynamic Array)
	// 실행 중에 저장될 메모리 공간이 정해진다.
	// 
	int* heapArray = new int[5] /* {} */;
	
	memset(heapArray, 0, sizeof(int) * 5);
	delete[] heapArray;

	Array<int, 10> templateClassArray;

	for (int i = 0; i < templateClassArray.GetSize(); ++i)
	{
		templateClassArray[i] = i + 1;
	}


	std::cin.get();

	return 0;
}