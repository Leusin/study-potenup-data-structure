#pragma once

template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

int Partition(int* array, int left, int right);
void QuicSort(int* array, int start, int end);