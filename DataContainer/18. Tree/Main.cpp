#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

#include "String.h"
#include "Tree.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Tree<String> tree("A");
	tree.AddChild("A", "B");
	tree.AddChild("A", "C");
	tree.AddChild("C", "D");
	tree.AddChild("C", "E");
	tree.AddChild("B", "F");
	tree.AddChild("B", "G");

	tree.PreorderTraverse();

	tree.Remove("C");
	tree.PreorderTraverse();

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}