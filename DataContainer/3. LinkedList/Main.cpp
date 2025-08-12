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

    // 리스트 생성.
    LinkedList list;

    list.Insert(30);
    list.Insert(50);
    list.Insert(70);
    list.Insert(10);
    list.Insert(40);
    list.Insert(60);
    list.Insert(80);

    list.Print();

    std::cout << "----- 정렬 -----\n";

    list.SelectionSortGreater();

    list.Print();

    /*
    // 반복해서 입력 받기.
    char input[50] = {};

    // 입력 루프
    while (true)
    {
        std::cout << "추가할 데이터를 입력해주세요(종료는 q)\n";
        std::cin >> input;

        // q를 눌렀는지 확인.
        if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
        {
            break;
        }

        // 예외처리.
        if (!atoi(input))
        {
            std::cout << "숫자만 입력 가능합니다.\n";
            continue;
        }

        // 데이터 삽입.
        list.Insert(atoi(input));

        // 출력.
        list.Print();
    }

    // 삭제 루프
    while (true)
    {
        std::cout << "삭제할 데이터를 입력해주세요(종료는 q)\n";
        std::cin >> input;

        // q를 눌렀는지 확인.
        if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
        {
            break;
        }

        // 예외처리.
        if (!atoi(input))
        {
            std::cout << "숫자만 입력 가능합니다.\n";
            continue;
        }

        // 데이터 삭제.
        list.Delete(atoi(input));

        // 출력.
        list.Print();
    }
    */
}