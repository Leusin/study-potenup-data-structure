#include <iostream>

void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

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