#pragma once

#include <string>
#include "Pair.h"
#include "LinkedList.h"

class HashTable
{
	using Entry = TPair<std::string, std::string>;

public:
	HashTable();
	~HashTable();

	int GenerateKey(const std::string& keyString);
	void Add(const std::string& key, const std::string& value);
	void Delete(const std::string& key);
	bool Find(const std::string& key, std::string& outValue);
	void Print();
	bool IsEmpty() const;

private:
	static const int buketCount = 19; // 소수(prime number)여야 한다

	// 2차 자료 구조 활용(체이닝 기법)
	LinkedList<Entry> table[buketCount] = {};
};