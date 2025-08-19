#include "QuickSort.h"

int Partition(int* array, int left, int right)
{
    // 임의로 정한 피봇
    int pivot = array[left];

    int low = left + 1;
    int hight = right;

    while (low <= hight)
    {
        // 왼쪽 -> 오른쪽
        while (low <= right && array[low] <= pivot)
        {
            ++low;
        }

        // 왼쪽 <- 오른쪽
        while (hight > left && array[hight] >= pivot)
        {
            --hight;
        }

        // 종료 조건 확인: low와 high가 교차하면 분할이 완료됨
        if (low > hight)
        {
            break;
        }

        // 피봇보다 큰 low 와 피봇보다 작은 hight 반환
        Swap(array[low], array[hight]);
    }

    // 피벗과 왼쪽 데이터의 마지막 요소 교환
    Swap(array[left], array[hight]);

    //
    return hight;
}

void QuicSort(int* array, int start, int end)
{
    // 예외처리.
    if (start >= end)
    {
        return;
    }

    // 피벗을 기준으로 배열 분할
    int pivot = Partition(array, start, end);

    // 왼쪽 정렬
    QuicSort(array, start, pivot - 1);

    // 오른쪽 정렬
    QuicSort(array, pivot + 1, end);
}
