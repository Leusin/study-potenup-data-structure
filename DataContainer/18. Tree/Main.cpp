#include <iostream>

#include "String.h"
#include "Tree.h"

int main()
{
	String test("test");
	String addtest = test + String("Added");

	std::cout << addtest << "\n";

	Tree<String> tree("A");
	tree.AddChild("A", "B");
	tree.AddChild("A", "C");
	tree.AddChild("C", "D");
	tree.AddChild("C", "E");
	tree.AddChild("B", "F");
	tree.AddChild("B", "G");

	return 0;
}