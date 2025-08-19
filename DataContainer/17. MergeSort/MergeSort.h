#pragma once

/// <summary>
/// 분할된 배열을 다시 합치는 병합 함수
/// </summary>
/// <param name="array">합쳐질 배열</param>
/// <param name="leftArray">분할 될 왼쪽 배열</param>
/// <param name="leftArratLength">왼쪽 배열의 크기</param>
/// <param name="rightArray">분할될 오른쪽 배열</param>
/// <param name="rightArratLength">오른쪽 배열 크기</param>
void Merge(int* array, int* leftArray, int leftArratLength, int* rightArray, int rightArratLength);

/// <summary>
/// 병합 정렬 함수.
/// </summary>
/// <param name="array">정렬할 대상</param>
/// <param name="length">배열 크기</param>
void MergeSort(int* array, int length);
