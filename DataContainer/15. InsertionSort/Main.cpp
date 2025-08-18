#include <iostream>

#define ArraySize(array) sizeof(array) / sizeof((array)[0]);

template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

void InsertionSort(int* array, int length)
{
	if (length <= 1)
	{
		return;
	}

	for (int i = 1; i < length; ++i)
	{
		int keyValue = array[i];
		int j = i - 1;

		while (j >= 0 && keyValue < array[j])
		{
			array[j + 1] = array[j]; 
			--j;
		}

		// 키 삽입
		array[j + 1] = keyValue;
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

	InsertionSort(array, length);

	std::cout << "정렬 후 배열: ";
	PrintArray(array, length);

	return 0;
}