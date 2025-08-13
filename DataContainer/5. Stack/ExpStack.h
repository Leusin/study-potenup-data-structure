#pragma once

#include <iostream>

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
class ExpStack
{
public:
	ExpStack();
	~ExpStack() = default;

	// 정리 함수
	void Clear();

	// 스택이 비어있는지 확인
	bool IsEmpty() const;
	
	// 스택이 가득 찼는지 확인
	bool IsFull() const;
	
	// 스택에 데이터 추가
	bool Push(float exp);
	
	// 스택에 데이터 추출
	float  Pop();

	// 스택에 저장된 데이터 수 반환 함수
	int Count() const;

private:

	float data[stackCount] = { }; // 데이터 저장 공간
	
	int count = 0; // 저장된 자료 수
};