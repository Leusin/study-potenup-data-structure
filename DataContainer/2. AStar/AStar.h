#pragma once

#include <vector>

#include "SafeDelete.h"

class AStar
{
	struct Direction
	{
		// 위치
		int x = 0;
		int y = 0;
		
		// 이동 비용
		float cost = 0.0f;
	};

public: // RAII

	AStar();
	~AStar();

public: // MESSAGE

	std::vector<class Node*> FindPath(class Node* start, class Node* goal, std::vector<std::vector<int>>& grid);

private: // METHOD

	// 탐색을 마친 후 경로를 조립해 반환하는 함수
	// 목표 노드에서 부모 노드를 참조해 시작 노드까지 역추적 하면서 경로 구함
	std::vector<Node*> ConstructPath(class Node* goalNode);
	
	// 탐색하려는 노드가 목표 노드인지 검사
	bool IsDestination(const Node* node);

	// 범위가 유효한지 확인
	bool IsInRange(int x, int y, const std::vector<std::vector<int>>& grid);

	// 이미 방문했는지 확인
	bool HasVisited(int x, int y, float gCost);

	float CalculateHuristic(class Node* current, class Node* goal);

private: // DATA

	// 열린 리스트: 방문할 노드 목록
	std::vector<class Node*> openList;

	// 닫힌 리스트: 방문된 노드 목록
	std::vector<class Node*> closedList;
	
	// 시작
	class Node* startNode;

	// 목표
	class Node* goalNode;
};