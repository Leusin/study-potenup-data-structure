#include "HashTable.h"

#include <iostream>

HashTable::HashTable()
	: table{}
{
}

HashTable::~HashTable()
{
}

/// <summary>
/// 해시를 생성하는 함수
/// </summary>
int HashTable::GenerateKey(const std::string& keyString)
{
	int key = 0;
	for (size_t i = 0; i < keyString.length(); ++i)
	{
		key = key * 31 + keyString[i];
	}

	//return key < 0 ? -key : key;
	return std::abs(key);
}

void HashTable::Add(const std::string& key, const std::string& value)
{
	// 키생성
	int keyValue = GenerateKey(key);

	// 버킷 인덱스로 변환
	int buketIndex = keyValue % buketCount;

	// 저장할 연결 리스트 참조
	LinkedList<Entry>& list = table[buketIndex];

	// 키가 같은 것을 허용할 것인지?
	for (int i = 0; i < list.Count(); ++i)
	{
		// 같은 키를 허용하지 않음
		if (list[i]->data.key == key)
		{
			std::cout << "이미 동일한 키를 가진 데이터가 있습니다\n";
			return;
		}
	}

	list.PushBack(Entry(key, value));
}

void HashTable::Delete(const std::string& key)
{
	// 삭제는 2단계

	// 1. 찾기.
	int KeyValue = GenerateKey(key);
	int buketIndex = KeyValue % buketCount;
	LinkedList<Entry>& list = table[buketIndex];

	// 2. 삭제.
	for (size_t i = 0; i < list.Count(); ++i)
	{
		if (list[i]->data.key == key)
		{
			list.Delete(list[i]->data);
			std::cout << "항목을 삭제했습니다.\n";
			return;
		}
	}

	std::cout << "항목을 찾을 수 없습니다.\n";
}

bool HashTable::Find(const std::string& key, std::string& outValue)
{
	// 1. 찾기.
	int KeyValue = GenerateKey(key);
	int buketIndex = KeyValue % buketCount;
	LinkedList<Entry>& list = table[buketIndex];

	if (list.IsEmpty())
	{
		std::cout << "해당 키로 항목을 찾을 수 없습니다.\n";
		return false;
	}

	for (size_t i = 0; i < list.Count(); ++i)
	{
		if (list[i]->data.key == key)
		{
			outValue = list[i]->data.value;

			return true;
		}
	}

	std::cout << "해당 키로 항목을 찾을 수 없습니다.\n";
	return false;
}

void HashTable::Print()
{
	for (int i = 0; i < buketCount; ++i)
	{
		LinkedList<Entry>& list = table[i];

		if (list.IsEmpty())
		{
			continue;
		}

		for (size_t j = 0; j < list.Count(); ++j)
		{
			std::cout
				<< "키: " << list[j]->data.key
				<< " 값: " << list[j]->data.value
				<< "\n";
		}
	}
}

bool HashTable::IsEmpty() const
{
	size_t totalCount = 0;

	for (int i = 0; i < buketCount; ++i)
	{
		const LinkedList<Entry>& list = table[i];

		if (list.IsEmpty())
		{
			continue;
		}

		totalCount += list.Count();
		//return true;
	}

	return totalCount == 0;
}