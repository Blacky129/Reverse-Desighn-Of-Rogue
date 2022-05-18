#pragma once

#include "Map/CMap.h"
#include <vector>

struct Node
{
	CPosition _From;
	CPosition _To;
	int _ValueToNode;
	float _ValueToSourse;

	Node(CPosition From, CPosition To, int ValueToNode, CPosition Goal);
};

struct Stack
{
	std::vector<std::vector<Node*>*> _Stack = {};

	void initNewVector();

	void addNode(Node* Node);

	void deleteNode(Node* Node);

	void clearStack();
};

class CPathFinder
{
private:
	CMap* _Map;

	Stack _PathStack;

	std::vector<Node*> _Open;

	std::vector<Node*> _Closed;
public:
	CPathFinder();
	CPathFinder(CMap* Map);

	void changeMap(CMap* NewMap);

	CPosition getVectorToGoal(CPosition From, CPosition Goal);

private:
	Node* findNewNodeToExtend();

	void extendNode(Node* Node, CPosition Goal);

	bool isCellPathable(CPosition Source, CPosition To);

	bool isPositionInClosed(CPosition Position);

	void clearOpenAndClosed();

	void improoveOpen(Node* NewNode);

	CPosition createVectorToGoal(CPosition Goal);
};
