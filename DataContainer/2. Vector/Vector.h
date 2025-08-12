#pragma once

#include <iostream>
/// <summary>
/// 동적으로 (실행 중 ) 크기가 변하는 배열
/// </summary>
template<typename T>
class Vector
{
public:
	Vector() : size(0), capacity(2)
	{
		// 내부 공간 할당
		data = new T[capacity];
	};

	~Vector()
	{
		if (data)
		{
			delete[] data;
		}
	}

	// 데이터 추가 함수
	void PushBack(const T& value)
	{
		if (size == capacity)
		{
			ReAllocate(capacity * 2);

		}

		data[size] = value;// 마지막 요소 다음 위치에 새 값 저장
		++size; // 저장된 요소의 크기 증가 처리
	}

	// [심화] 데이터 추가 함수 (RValue Reference version) ***
	void PushBack(T&& value)
	{
		if (size == capacity)
		{
			ReAllocate(capacity * 2);

		}

		data[size] = std::move(value); // Move Semantic (중요) ***
		++size; // 저장된 요소의 크기 증가 처리
	}

	
	// 접근 및 설정을 위한 인덱스 연산자 오버로딩
	T& operator[](int index)
	{
		// Out of Index/Range 예외 처리
		if (index < 0 || index >= size) 
		{
			__debugbreak();
		}

		return data[index];
	}

	// 접근 및 설정을 위한 인덱스 연산자 오버로딩 (const 버전)
	T& operator[](int index) const
	{
		// Out of Index/Range 예외 처리
		if (index < 0 || index >= size)
		{
			__debugbreak();
		}

		return data[index];
	}

	T& At(int index)
	{
		// Out of Index/Range 예외 처리
		if (index < 0 || index >= size)
		{
			__debugbreak();
		}

		return data[index];
	}

	void Set(int index, const T& value)
	{
		// Out of Index/Range 예외 처리
		if (index < 0 || index >= size)
		{
			__debugbreak();
		}

		data[index] = value;
	}

	T* begin()
	{
		return data;
	}

	T* end()
	{
		return data + size;
	}

private:
	void ReAllocate(int newCapacity)
	{
		// 1. 새 공간 할당
		T* newBlock = new T[newCapacity];
		memset(newBlock, 0, sizeof(T) * newCapacity);

		// 2. 기존 값 복사
		memcpy(newBlock, data, sizeof(T) * capacity); // for 루프보다 빠르다 // 혹은 move 를 사용해도 된다. 
		/*for (int i = 0; i < capacity; ++i)
		{
		newBlock[i] = data[i];
		}*/

		// 3. 다 쓴 메모리 공간 해제 및 업데이트
		delete[] data;
		data = newBlock;
		capacity = newCapacity;
	}

private:
	// 컨테이너
	T* data = nullptr;

	// 배열에 실제로 저장될 요소 수
	int size = 0;

	// 미리 확보해둔 저장 공간 크기
	int capacity = 0;
};