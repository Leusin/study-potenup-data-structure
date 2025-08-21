#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

#include "BinaryTree.h"
#include "String.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //_crtBreakAlloc = 166;

    // 트리 생성.
    //       A
    //      / \
    //     B   C
    //    / \
    //   D   E
    BinaryTree<String>* tree  = new BinaryTree<String>("A");
    tree->AddLeftChild("A", "B");    // A 왼쪽 밑에 B 추가.
    tree->AddRightChild("A", "C");    // A 오른쪽 밑에 C 추가.
    tree->AddLeftChild("B", "D");
    tree->AddRightChild("B", "E");

    // 전위 순회.
    std::cout << "전위 순회\n";
    tree->PreorderTraverse();

    // 삭제.
    std::cout << "\nE 노드 삭제\n";
    tree->DeleteNode("E");

    // 순회.
    std::cout << "\n전위 순회\n";
    tree->PreorderTraverse();

    delete tree;

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	//return 0;
}