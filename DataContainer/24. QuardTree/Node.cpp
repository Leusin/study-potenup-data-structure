#include "Node.h"

Node::Node(const Bounds& bounds, int depth)
	:bounds{ bounds }, depth{ depth }
{
}

Node::~Node()
{
	Clear();
}

void Node::Insert(Node* node)
{
}

void Node::Query(const Bounds& queryBounds, std::vector<Node*>& possibleNodes)
{
}

void Clear()
{

}