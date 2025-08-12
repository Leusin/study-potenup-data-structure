#include <iostream>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#include "LinkedList.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	LinkedList ll;

	ll.Delete(10);

	ll.Insert(10);
	ll.Insert(50);
	ll.Insert(30);
	ll.Insert(20);

	ll.Print();

	ll.Delete(10);

	ll.Print();

	ll.Delete(100);

	std::cin.get();

	return 0;
}