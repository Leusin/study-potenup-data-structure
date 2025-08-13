#include "PreCompiledHeader.h"

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

	FILE* stream;
	if (fopen_s(&stream, "InputTest.txt", "rb") != 0)
	{
		std::cout << "Failed to open map file\n";

		return 0;
	}

	//파일 크기 구하기
	fseek(stream, 0, SEEK_END);
	size_t count = ftell(stream);
	rewind(stream);

	// 버퍼 초기화
	char* buffer = new char[count + 1];
	memset(buffer, 0, sizeof(char) * (count + 1));
	int numread = fread(buffer, sizeof(char), count, stream);

	// 디버그 출력
	printf("Number of items read = %d\n", numread);
	printf("Contents of buffer = %s\n", buffer);

	char* context = nullptr;
	char* data = strtok_s(buffer, " ", &context);
	while (data)
	{
		if (atoi(data))
		{
			ll.PushBack(atoi(data));
		}

		data = strtok_s(nullptr, " ", &context);
	}

	delete[] buffer;
	fclose(stream);

	ll.Print();

	// 삭제 테스트.
	char input[50] = {};
	while (true)
	{
		std::cout << "삭제할 데이터를 입력해주세요(종료는 q)\n";
		std::cin >> input;

		// 입력 값이 q/Q 인지 확인.
		if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
		{
			break;
		}

		// 예외처리(숫자만 입력 하도록 검증).
		if (!atoi(input))
		{
			std::cout << "숫자만 입력 가능합니다.\n";
			continue;
		}

		// 삭제.
		ll.Delete(atoi(input));

		// 출력.
		ll.Print();
	}
}