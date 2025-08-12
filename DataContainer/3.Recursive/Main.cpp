#include <iostream>

// 이진 탐색
// 정렬이 선행되어야 한다.
int BinarySearch(int arr[], int target, int low, int high)
{
	//종료 조건(예외/만족)
	if (low > high)
	{
		return -1;
	}

	// 입력 변경
	int mid = (low + high) / 2;
	if (arr[mid] == target)
	{
		return mid;
	}
	else if (arr[mid] < target)
	{
		return BinarySearch(arr, target, mid + 1, high);
	}
	else // if (arr[mid] >= target)
	{
		return BinarySearch(arr, target, low, mid - 1);
	}
}

int main()
{
	int array[] = { 2, 5, 8, 12, 16, 23, 38, 56, 72, 91 };
	int length = sizeof(array) / sizeof(int)/*sizeof(array[0])*/;
	int target = 56;

	int result = BinarySearch(array, target, 0, length - 1);
	if (result < 0)
	{
		std::cout << "검색 실패\n";
	}
	else
	{
		std::cout << target << "는 " << result << "번 인덱스\n";
	}

	std::cin.get();

	return 0;
}