#include "AStar.h"

#include <cmath>
#include "Node.h"

AStar::AStar()
	: startNode{ nullptr }, goalNode{ nullptr }
{
}

AStar::~AStar()
{
	// 메모리 해제

	for (Node* node : openList)
	{
		SafeDelete(node);
	}

	openList.clear();

	for (Node* node : closedList)
	{
		SafeDelete(node);
	}

	closedList.clear();
}

std::vector<Node*> AStar::FindPath(Node* start, Node* goal, std::vector<std::vector<int>>& grid)
{
	startNode = start;
	goalNode = goal;

	// 상화좌우, 대각선 방향 및 비용
	std::vector<Direction> directions =
	{
		// 하상우좌 (화면 좌표계 기준)
		{0, 1, 1.0f}, {0, -1, 1.0f}, {1, 0, 1.0f}, {-1, 0, 1.0f},
		// 대각선
		{1, 1, 1.414f}, {1, -1, 1.414f}, {1, -1, 1.414f}, {-1, -1, 1.414f}
	};

	// 1. 초기화
	openList.emplace_back(startNode);

	while (!openList.empty())
	{
		//2. fCost 가 가장 낮은 노드 선택

		// 가장 비용이 작은 노드 (선형으로) 탐색
		Node* lowestNode = openList[0];
		for (Node* node : openList)
		{
			if (node->fCost < lowestNode->fCost)
			{
				lowestNode = node;
			}
		}

		// fCost 가장 작은 노드를 현재 노드로 설정
		Node* currentNode = lowestNode;

		// 3. 목표 확인
		if (IsDestination(currentNode))
		{
			// 목표 노드인 경우, 지금까지 경로 반환
			return ConstructPath(currentNode);
		}

		// 4. 닫힌 리스트로 이동
		for (size_t i = 0; i < openList.size(); ++i)
		{
			if (*openList[i] == *currentNode)
			{
				// i 번째 노드 제거
				openList.erase(openList.begin() + i);
				break;
			}
		}

		// 5. 이웃 노드 탐색
		bool isNodeInList = false;
		for(Node* node: closedList)
		{
			if (*node == *currentNode)
			{
				isNodeInList = true;
				break;
			}
		}

		// 방문했으면 아래 단계 건너뜀
		if (isNodeInList)
		{
			continue;
		}

		closedList.emplace_back(startNode);

		// 이웃 노드 방문
		for (const Direction& direction : directions)
		{
			// 다음에 이동할 위치 설정
			int newX = currentNode->position.x + direction.x;
			int newY = currentNode->position.y + direction.y;

			// 그리드 밖인지 확인
			if (!IsInRange(newX, newY, grid))
			{
				continue;
			}

			// (옵션) 장애물인지 확인
			// 여기선 값이 1일 경우 장애물
			if (grid[newY][newX] == 1)
			{
				continue;
			}

			// 이미 방문했는지 확인
			float gCost = currentNode->gCost + direction.cost;
			if (HasVisited(newX, newY, gCost))
			{
				continue;
			}

			// 방문을 위한 노드 생성
			Node* neighbor = new Node(newX, newY, currentNode);
			neighbor->gCost = currentNode->gCost + direction.cost;

			// 휴리스틱 비용 계산
			neighbor->hCost = CalculateHeuristic(currentNode, goal);
			neighbor->fCost = neighbor->gCost + neighbor->hCost;
		}
	}

	return std::vector<Node*>();
}

std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
	std::vector<Node*> path;
	Node* current = goalNode;

	while (current != nullptr)
	{
		path.emplace_back(current);
		current = current->parent;
	}

	std::reverse(path.begin(), path.end());
	return path;
}

bool AStar::IsDestination(const Node* node)
{
	return *node == *goalNode;
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
	if (x < 0 || y < 0 || x >= (int)grid[0].size() || y >= (int)grid.size())
	{
		return false;
	}

	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	// 열린 리스트 또는 닫힌 리스트에 해당 노드가 있으면 방문 한 것으로 판단
	for (size_t i = 0; i < openList.size(); ++i)
	{
		Node* node = openList[i];
		if (node->position.x == x && node->position.y == y)
		{
			// 위치가 같고 비용이 더 큰 경우
			if (node->gCost < gCost)
			{
				return true;
			}
			else if (node->gCost > gCost)
			{
				openList.erase(openList.begin() + i);
				SafeDelete(node);
			}
		}
	}

	for (size_t i = 0; i < closedList.size(); ++i)
	{
		Node* node = closedList[i];
		if (node->position.x == x && node->position.y == y)
		{
			if (node->gCost < gCost)
			{
				return true;
			}
			else if (node->gCost > gCost)
			{
				closedList.erase(closedList.begin() + i);
				SafeDelete(node);
			}
		}
	}

	return false;
}

float AStar::CalculateHeuristic(Node* current, Node* goal)
{
	// 단순 거리 계산을 통해 휴리스틱 비용 활용
	Position diff = *current - *goal;
	return (float)std::sqrt(diff.x * diff.x + diff.y * diff.y);
}
