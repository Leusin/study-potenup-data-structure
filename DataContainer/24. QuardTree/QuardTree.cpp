#include "QuardTree.h"
#include "SafeDelete.h"
#include "Bounds.h"
#include "Node.h"

int QuardTree::maxDepth = 5;

QuardTree::QuardTree(const Bounds& bounds)
	: root(new Node(bounds))
{
}

QuardTree::~QuardTree()
{
	SafeDelete(root);
}

void QuardTree::Insert(Node* node)
{
	root->Insert(node);
}

std::vector<Node*> QuardTree::Query(Node* queryNode)
{
	// 겹침 가능성이 있는 영역 확인
	std::vector<Node*> possibleNode;
	root->Query(queryNode->GetBounds(), possibleNode);

	// 가능성이 있는 노드에서 실제로 겹치는지 노드 검사
	std::vector<Node*> intersects;

	// 겹침 가능성 있는 영역 순회
	for (Node* node : possibleNode)
	{
		// 각 영역이 가지는 노드 순회
		for (Node* point : node->GetPointers())
		{
			// 겹침 검사
			if (point->GetBounds().Intersects(queryNode->GetBounds()))
			{
				intersects.emplace_back(point);
				continue;
			}
		}
	}

	// 최종 목록 반환.
	// 노트: 함수에서 출력용 배열을 참조로 받으면 최적화 가능

	return intersects;
}