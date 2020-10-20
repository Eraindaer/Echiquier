#include <iostream>
#include <algorithm>
#include <vector>

class NodeTree {
public:
	NodeTree() {
		value = rand() % 10 - 5;
	}
	~NodeTree() {

	}

public:
	int value;
	std::vector<NodeTree> childNodes;
};

int MinMax(NodeTree currentNode, int depth, bool maximizingPLayer) {
	if (depth == 0)
		return currentNode.value;
	if (maximizingPLayer) {
		currentNode.value = -INFINITY;
		for (auto& node : currentNode.childNodes) {
			currentNode.value = std::max(currentNode.value, MinMax(node, depth - 1, false));
		}
		return currentNode.value;
	}
	else {
		currentNode.value = INFINITY;
		for (auto& node : currentNode.childNodes) {
			currentNode.value = std::min(currentNode.value, MinMax(node, depth - 1, true));
		}
		return currentNode.value;
	}
}

int main() {
	
}