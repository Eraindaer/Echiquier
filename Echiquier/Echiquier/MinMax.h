#pragma once
#include <vector>
#include <iostream>
#define HIGHNUMBER 1000000000

struct Node {
	int               value = 0;
	bool              hasChildren = false;
	std::vector<Node> children;
};

class NodeTree
{
public:
	NodeTree();
	~NodeTree();

	void Init(Node& currentNode, int depth, int childPerNodes);
	void Print(Node currentNode);
	void ClearTree(Node currentNode);

	int  MinMax(Node& currentNode, int depth, int alpha, int beta, bool maximizingPlayer);
};

