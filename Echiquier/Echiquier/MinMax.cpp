#include "MinMax.h"

NodeTree::NodeTree() {
}
NodeTree::~NodeTree() {
}

void NodeTree::Init(Node& currentNode, int depth, int childPerNodes) {
	if (depth >= 1)
		currentNode.hasChildren = true;
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
		currentNode.value = rand() % 100 + 1; //Valeur pour l'exemple, ce ne sera pas cette valeur évidemment
	}
}

void NodeTree::Print(Node currentNode) {
	if (currentNode.hasChildren) {
		std::cout << "Value of the current Node : " << currentNode.value << "\nChilds :\n";
		for (Node& child : currentNode.children) {
			Print(child);
		}
	}
	else {
		std::cout << "Value of the Node : " << currentNode.value << "\n";
	}
}

void NodeTree::ClearTree(Node currentNode) {
	if (currentNode.hasChildren) {
		for (Node& child : currentNode.children) {
			ClearTree(child);
		}
		currentNode.children.clear();
	}
}

int NodeTree::MinMax(Node& currentNode, int depth, int alpha, int beta, bool maximizingPlayer) {
	if (depth == 0)
		return currentNode.value;
	if (maximizingPlayer) {
		currentNode.value = -HIGHNUMBER;
		for (Node& node : currentNode.children) {
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
		for (Node& node : currentNode.children) {
			int eval = MinMax(node, depth - 1, alpha, beta, true);
			currentNode.value = std::max(currentNode.value, eval);
			beta = std::min(beta, eval);
			if (beta <= alpha)
				break;
		}
		return currentNode.value;
	}
}