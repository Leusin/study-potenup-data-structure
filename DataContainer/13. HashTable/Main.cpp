#include <iostream>
#include "HashTable.h"

int main()
{
	HashTable ht;

	ht.Add("믱ㅇ", "12312312");
	ht.Add("ㄴㅇㄹㄴㄹ", "ㄴㅇㄹㄴ");
	ht.Add("ㅇㄴㄹ", "ㄹㅇㄴ");

	ht.Print();

	ht.Add("ㅇㄴㄹ", "ㄹㅇㄴ");
	
	std::string find;
	ht.Find("믱ㅇ", find);
	std::cout << "찾았다: " << find << "\n";

	ht.Delete("ㄴㅇㄹㄴㄹ");
	ht.Delete("ㄴㅇㄹㄴㄹ");
	ht.Find("ㄴㅇㄹㄴㄹ", find);

	ht.Print();
}