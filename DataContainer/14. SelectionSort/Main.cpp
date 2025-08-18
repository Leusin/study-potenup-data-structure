#include <iostream>
#include <windows.h>

#define ArraySize(array) sizeof(array) / sizeof((array)[0]);

template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

/// <summary>
/// 동작 방식
/// 1. 가장 작은/큰 값을 찾는다
/// 2. 가장 엎의 원소와 교환한다.
/// 3. 교환한 원소를 제외한 나머지 리스트를 대상으로 1, 2를 반복한다.
/// 
/// 특징
/// 시간: O(N^2)
/// 장: 이동 횟수가 미리 결정된다
/// 단: 안정성을 만족하지 않는다
/// </summary>
void SelectionSort(int* array, int length)
{
	// 예외 처리
	if (length <= 1)
	{
		return;
	}

	// 외부에서는 0 ~ (n-1)
	for (int i = 0; i < length - 1; ++i)
	{
		int minIndex = i;

		// 내부 루프는 i ~ n 까지
		for (int j = i; j < length; ++j)
		{
			if (array[j] < array[minIndex])
			{
				minIndex = j;
			}
		}

		// 교환
		if (i != minIndex)
		{
			Swap(array[i], array[minIndex]);
		}
	}
}

// 배열 출력 함수.
void PrintArray(int array[], int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix];

		if (ix < length - 1)
		{
			std::cout << ", ";
		}
	}

	std::cout << "\n";
}

int main()
{
	// 자료 집합.
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	int length = ArraySize(array);

	SelectionSort(array, length);

	std::cout << "정렬 후 배열: ";
	PrintArray(array, length);

	return 0;
}