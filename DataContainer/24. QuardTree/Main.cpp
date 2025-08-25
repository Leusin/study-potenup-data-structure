#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>


#include <vector>
#include "QuardTree.h"
#include "Node.h"

struct Wow
{
	int a, b, c;
};

class Wowa
{
public:
	int a, b, c;
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	QuardTree tree(Bounds(0.0f, 0.0f, 100.0f, 100.0f));

	tree.Insert(new Node(Bounds{ 40.0f, 40.0f, 20.f, 20.f }));
	tree.Insert(new Node(Bounds{ 20.0f, 20.0f, 2.f, 2.f }));

	Node testBound(Bounds{ 50, 50, 5, 5 });
	std::vector<Node*> intersects = tree.Query(&testBound);

	Wow what1{ 1,2,3 };
	Wowa what2{ 1,2,3 };

	std::cout << "Wow what " << what1.a << " " << what1.b<< " " << what1.c << "\n";
	std::cout << "Wowa what " << what2.a << " " << what2.b<< " " << what2.c << "\n";

	if (intersects.size() == 0)
	{
		std::cout << "없음" << "\n";
	}
	else
	{
		std::cout << "있음" << "\n";
	}

	return 0;
}