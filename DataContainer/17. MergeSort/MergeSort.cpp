#include "MergeSort.h"
#include <iostream>

void Merge(int* array, int* leftArray, int leftArratLength, int* rightArray, int rightArratLength)
{
	int leftIndex = 0;
	int rightIndex = 0;
	int mergedIndex = 0;

	// 왼쪽 배열, 오른쪽 배열 비교하면서 병합 
	while (leftIndex < leftArratLength && rightIndex < rightArratLength)
	{
		if (leftArray[leftIndex] <= rightArray[rightIndex])
		{
			array[mergedIndex++] = leftArray[leftIndex++];
		}
		else
		{
			array[mergedIndex++] = rightArray[rightIndex++];
		}
	}
	
	// 왼쪽 나머지
	while (leftIndex < leftArratLength)
	{
		array[mergedIndex++] = leftArray[leftIndex++];
	}

	// 오른쪽 나머지
	while (rightIndex < rightArratLength)
	{
		array[mergedIndex++] = rightArray[rightIndex++];
	}
}

void MergeSort(int* array, int length)
{
	// 예외 처리. base case
	if (length <= 1)
	{
		return;
	}

	//
	// 1. 분할
	//

	// 분할될 배열 공간 확보
	int mid = length / 2;
	int remain = length - mid;

	int* leftArray = new int[mid];
	memcpy(leftArray, array, sizeof(int) * mid);

	int* rightArray = new int[remain];
	memcpy(rightArray, array + mid, sizeof(int) * remain);

	//
	// 2. 재귀
	//

	// 왼쪽
	MergeSort(leftArray, mid);
	// 오른쪽
	MergeSort(rightArray, remain);

	//
	// 3. 병합
	//
	
	Merge(array, leftArray, mid, rightArray, remain);

	// 메모리 정리
	delete[] leftArray;
	delete[] rightArray;
}
