#pragma once

#include <iostream>

class Node
{
	friend std::ostream& operator<< (std::ostream & os, const Node & node);
	friend class LinkedList;

private:
	Node();
	Node(int data);

private:
	// 데이터 필드
	int data = 0;

	// 링크 필드
	Node* next = nullptr;
};