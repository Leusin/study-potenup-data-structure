#include <iostream>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#include "LinkedList.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
int main()
{
	LinkedList<int> ll;

	char input[50] = {};

	while (true)
	{
		std::cout << "추가할 데이터를 입력해주세요\n";
		std::cin >> input;

		if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
		{
			break;
		}

		// 숫자 입력만 하도록 검증
		if (!atoi(input))
		{
			std::cout << " 숫자만 입력 가능\n";
			continue;
		}

		ll.PushBack(atoi(input));
		ll.Print();
	}
}