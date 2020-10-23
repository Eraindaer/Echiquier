#include <iostream>
#include <algorithm>
#include <vector>
#define HIGHNUMBER 10000000

struct Node {
	int               value = 0;
	int               depth = 0;
	bool              hasChildren = false;
	std::vector<Node> children;
};

class NodeTree {
public:
	NodeTree() {
	}
	~NodeTree() {

	}

	void Init(Node &currentNode, int depth, int childPerNodes) {
		if (depth >= 1) {
			currentNode.hasChildren = true;
		}
		if (currentNode.hasChildren) {
			for (int i = 0; i < childPerNodes; i++) {
				Node n;
				currentNode.children.push_back(n);
			}
			currentNode.value = 0;
			for (Node& child : currentNode.children) {
				Init(child, depth - 1, childPerNodes);
			}
		}
		else {
			//std::cout << "Node initialized \n";
			currentNode.value = rand() % 100 + 1;
		}
	}

	void Print(Node currentNode) {
		if (currentNode.hasChildren) {
			std::cout << "Value of the current Node : " << currentNode.value << "\n Childs : \n";
			for (Node& child : currentNode.children) {
				Print(child);
			}
		}
		else {
			std::cout << "Value of the node : ";
			std::cout << currentNode.value << "\n";
		}
	}
};

int MinMax(Node &currentNode, int depth, int alpha, int beta, bool maximizingPLayer) {
	if (depth == 0)
		return currentNode.value;
	if (maximizingPLayer) {
		currentNode.value = -HIGHNUMBER;
		for (auto& node : currentNode.children) {
			int eval = MinMax(node, depth - 1, alpha, beta, false);
			currentNode.value = std::max(currentNode.value, eval);
			alpha = std::max(alpha, eval);
			if (beta <= alpha)
				break;
		}
		return currentNode.value;
	}
	else {
		currentNode.value = HIGHNUMBER;
		for (auto& node : currentNode.children) {
			int eval = MinMax(node, depth - 1, alpha, beta, true);
			currentNode.value = std::min(currentNode.value, eval);
			beta = std::min(beta, eval);
			if (beta <= alpha)
				break;
		}
		return currentNode.value;
	}
}

int main() {
	NodeTree nt;
	Node mainNode;

	int depth = 5;
	int nodesPerNode = 15;

	nt.Init(mainNode, depth, nodesPerNode);
	//nt.Print(mainNode);

	std::cout << "Result of MinMax :" << MinMax(mainNode, depth, -HIGHNUMBER, HIGHNUMBER, true) << "\n";

	return 0;
}