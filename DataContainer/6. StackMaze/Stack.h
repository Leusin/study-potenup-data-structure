#pragma once

#include <iostream>
#include <Windows.h>

#define TEST 0

// 경험치 스택 최대 저장 수
#if TEST
const int stackCount = 1;
#else 
const int stackCount = 100;
#endif

/// <summary>
/// 경험치 이력을 관리하는 스택 클래스
/// </summary>
template<typename T>
class Stack
{
public:
	Stack()
		:count(0)
	{
		memset(data, 0, sizeof(float) * stackCount);
	}

	~Stack() = default;

	// 정리 함수
	void Clear()
	{
		memset(data, 0, sizeof(float) * stackCount);
		count = 0;
	}

	// 스택이 비어있는지 확인
	bool IsEmpty() const
	{
		return count == 0;
	}

	// 스택이 가득 찼는지 확인
	bool IsFull() const
	{
		return count == stackCount;
	}

	// 스택에 데이터 추가
	bool Push(T exp)
	{
		if (IsFull())
		{
			MessageBoxA(nullptr, "스택이 가득 차 추가 불가", "Stack Push Error", MB_OK);

			std::cout << "스택이 가득차 추가 불가\n";

			return false;
		}

		data[count] = exp;
		++count;

		return true;
	}

	// 스택에 데이터 추출
	T Pop()
	{
		if (IsEmpty())
		{
			MessageBoxA(nullptr, "스택이 비어 추출 불가", "Stack Push Error", MB_OK);

			std::cout << "스택이 비어 추출 불가\n";

			return data[0];
		}

		--count;
		return data[count];
	}

	// 스택에 저장된 데이터 수 반환 함수
	int Count() const
	{
		return count;
	}

private:

	T data[stackCount] = { }; // 데이터 저장 공간

	int count = 0; // 저장된 자료 수
};