#include <iostream>

void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

/// <summary>
/// 동작 방식
/// 1. 첫 번쨰 원소 부터 마지막 원소까지 순회한다
/// 2. 현재 원소와 다음 원소를 비교해 더 작은/큰 원소가 앞에 오도록 교환한다.
/// 3. 모든 원소가 정렬할 떄까지 배열의 마지막 위치에 도달할때까지 반복한다
/// </summary>
void Sort(int* array, int length)
{
	for (int i = 0; i < length - 1; ++i)
	{
		for (int j = 0; j < length - 1 - i; ++j)
		{
			if (array[j] > array[j + 1])
			{
				Swap(array[j], array[j + 1]);
			}
		}
	}
}

void PrintArray(int* array, int length)
{
	for (int i = 0; i < length; i++)
	{
		std::cout << array[i];

		if (i != length - 1)
		{
			std::cout << ", ";
		}
		else
		{
			std::cout << "\n";
		}
	}
}

int main()
{
	int array[10] = { 4, 3, 2, 1, 0, 9, 8, 7, 6, 5};

	int length = sizeof(array) / sizeof(int);

	std::cout << "정렬 전 :";
	PrintArray(array, length);

	Sort(array, length);

	std::cout << "정렬 후 :";
	PrintArray(array, length);

	return 0;
}