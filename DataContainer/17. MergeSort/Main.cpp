#include <iostream>
#include "MergeSort.h"

#define ArraySize(array) sizeof(array) / sizeof((array)[0])

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
	// 배열.
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	int length = (int)ArraySize(array);

	PrintArray(array, length);

	MergeSort(array, length);

	PrintArray(array, length);

	return 0;
}