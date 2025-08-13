#include <iostream>
#include "Stack.h"
#include "Vector2.h"

// 큰
const size_t MAZE_SIZE = 20;

// map[y][x]
// s : 시작
// g : 목표
// 1 : 이동 가능
// 0 : 이동 불가
char map[MAZE_SIZE][MAZE_SIZE] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1'},
	{'s', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', 'g'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

bool IsValidLocation(int y, int x)
{
	if (y >= MAZE_SIZE || x >= MAZE_SIZE)
	{
		return false;
	}

	if (y < 0 || x < 0)
	{
		return false;
	}

	return map[y][x] == '0' || map[y][x] == 'g';
}

// 화면 지우기
void ClearScreen()
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO info = { };
	info.dwSize = 1;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &info);

	SetConsoleCursorPosition(handle, { 0,0 });
	for (int y = 0; y < MAZE_SIZE; ++y)
	{
		for (int x = 0; x < MAZE_SIZE; ++x)
		{
			std::cout << " ";
		}
		std::cout << "\n";
	}
	SetConsoleCursorPosition(handle, { 0,0 });
}

// 위치 출력 함수
void PrintLocation(int playerX, int playerY, unsigned long delay)
{
	Sleep(delay); // 밀리 세콘드(1/1000초) 단위로 CPU 재우기

	ClearScreen(); // 화면 지우기

	// 맵과 플레이어 그리기
	for (int y = 0; y < MAZE_SIZE; ++y)
	{
		for (int x = 0; x < MAZE_SIZE; ++x)
		{
			if (x == playerX && y == playerY)
			{
				std::cout << "P ";
				continue;
			}

			std::cout << map[y][x] << " ";
		}
		std::cout << "\n";
	}
}

int main()
{
	// 시작 위치
	int startY = 0; // row
	int startX = 0; // col

	for (int y = 0; y < MAZE_SIZE; ++y)
	{
		for (int x = 0; x < MAZE_SIZE; ++x)
		{
			std::cout << map[y][x] << " ";

			//  시작 위치인지 확인
			if (map[y][x] == 's')
			{
				startX = x;
				startY = y;
			}
		}
		std::cout << "\n";
	}

	Stack<Vector2> locationStack;
	locationStack.Push(Vector2{ startX, startY });

	// 미로 탐색
	while (!locationStack.IsEmpty())
	{
		Vector2 current = locationStack.Pop();

		// 맵과 플레이어 위치 
		PrintLocation(current.x, current.y, 500);

		// 도착 확인
		if (map[current.y][current.x] == 'g')
		{
			std::cout << "\n 미로  탐색 성공\n";

			std::cin.get();
			return 0;
		}

		// 탐색 표시
		map[current.y][current.x] = '.';

		// 인접한 위치 탐색
		// 입력 순서: 상/하/좌/우
		// 탐색 순서: 우/좌/하/상
		if (IsValidLocation(current.y - 1, current.x))
		{
			locationStack.Push(Vector2{ current.x, current.y - 1 });
		}
		if (IsValidLocation(current.y + 1, current.x))
		{
			locationStack.Push(Vector2{ current.x, current.y + 1 });
		}
		if (IsValidLocation(current.y, current.x - 1))
		{
			locationStack.Push(Vector2{ current.x - 1, current.y });
		}
		if (IsValidLocation(current.y, current.x + 1))
		{
			locationStack.Push(Vector2{ current.x + 1, current.y });
		}
	}

	// 탐색 실패
	std::cout << "\n미로 탐색 실패\n";
	std::cin.get();

	return 0;
}