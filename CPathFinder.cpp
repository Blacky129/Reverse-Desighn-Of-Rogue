#include "CPathFinder.h"
#include <algorithm>

Node::Node(CPosition From, CPosition To, int ValueToNode)
{
	_From = From;
	_To = To;
	_ValueToNode = ValueToNode;
	_ValueToSourse = sqrt((To.X - From.X) ^ 2 + (To.Y - From.Y) ^ 2);
}

void Stack::addNode(Node* Node)
{
	if (Node->_ValueToNode >= _Stack.size())
		initNewVector();

	_Stack.at(Node->_ValueToNode)->push_back(Node);
}

void Stack::initNewVector()
{
	_Stack.push_back(new std::vector < Node*>);
}

void Stack::clearStack()
{
	for (std::vector<Node*>* NodeVector : _Stack)
	{
		for (Node* CurrentNode : *NodeVector)
		{
			delete CurrentNode;
		}

		delete NodeVector;
	}

	_Stack.clear();
}

CPathFinder::CPathFinder(CMap* Map)
{
	_Map = Map;
}

void CPathFinder::changeMap(CMap* NewMap)
{
	_Map = NewMap;
	_Open = {};
	_Closed = {};
}

void CPathFinder::clearOpenAndClosed()
{
	for (Node* Node : _Open)
		delete Node;

	for (Node* Node : _Closed)
		delete Node;
}

CPosition CPathFinder::getVectorToGoal(CPosition From, CPosition Goal)
{
	clearOpenAndClosed();

	_PathStack.clearStack();

	_Open.push_back(new Node{ CPosition{-1, -1}, From, 0 });

	while (_Open.size() != 0)
	{
		Node* NewNode = findNewNodeToExtend();

		if (NewNode->_To == Goal)
			break;

		extendNode(NewNode);

		improoveOpen();
	}

	return createVectorToGoal(Goal);
}

CPosition CPathFinder::createVectorToGoal(CPosition Goal)
{
	Node* CurrentNode = nullptr;

	for (int FIndex = _PathStack._Stack.size() - 1; FIndex >= 0; FIndex--)
	{
		for (Node* Node : *(_PathStack._Stack[FIndex]))
		{
			if (Node->_To == Goal)
			{
				CurrentNode = Node;
				break;
			}
		}
		if (CurrentNode != nullptr)
			break;
	}

	while (CurrentNode->_ValueToNode > 1)
	{
		for (Node* Node : *(_PathStack._Stack[CurrentNode->_ValueToNode - 1]))
		{
			if (Node->_To == CurrentNode->_From)
			{
				CurrentNode = Node;
				break;
			}
		}
	}

	return CurrentNode->_To - CurrentNode->_From;
}

Node* CPathFinder::findNewNodeToExtend()
{
	Node* NodeToExtend = _Open.at(0);

	for (Node* CurrentNode : _Open)
	{
		if (CurrentNode->_ValueToNode + CurrentNode->_ValueToSourse < NodeToExtend->_ValueToNode + NodeToExtend->_ValueToSourse)
			NodeToExtend = CurrentNode;
	}

	return NodeToExtend;
}

void CPathFinder::extendNode(Node* CurrentNode)
{
	std::vector<CPosition> ExtendedPostions = {
		CurrentNode->_To + CPosition{ -1, -1 }, CurrentNode->_To + CPosition{ +0, -1 }, CurrentNode->_To + CPosition{ +1, -1 },
	    CurrentNode->_To + CPosition{ -1, +0 },			                                CurrentNode->_To + CPosition{ +1, +0 },
	    CurrentNode->_To + CPosition{ -1, +1 }, CurrentNode->_To + CPosition{ +0, +1 }, CurrentNode->_To + CPosition{ +1, +1 } 
	};

	for (CPosition NextPosition : ExtendedPostions)
	{
		if (isCellPathable(NextPosition) == false)
			continue;

		if (isPositionInClosed(NextPosition) == true)
			continue;
		
		_PathStack.addNode(new Node{ CurrentNode->_To, NextPosition, CurrentNode->_ValueToNode + 1 });
	}
}

bool CPathFinder::isCellPathable(CPosition Position)
{
	if (Position.X < 0 || Position.Y < 0 || Position.X > _Map->getSizeOfMap().X || Position.Y > _Map->getSizeOfMap().Y)
		return false;

	if (_Map->getTypeOfIteration(Position) != TypeIteration::Move)
		return false;

	return true;
}

bool CPathFinder::isPositionInClosed(CPosition Position)
{
	for (Node* Node : _Closed)
	{
		if (Node->_To == Position)
			return true;
	}
	return false;
}

void CPathFinder::improoveOpen()
{
	std::vector<Node*> ImproovedOpen = {};
	for (Node* CurrentNode : _Open)
	{
		for (Node* NodeForCheck : ImproovedOpen)
		{
			if (!(CurrentNode->_To == NodeForCheck->_To))
				continue;

			if (CurrentNode->_ValueToNode > NodeForCheck->_ValueToNode)
			{
				std::vector<Node*>::iterator Position = std::find(_Open.begin(), _Open.end(), CurrentNode);
				_Open.erase(Position);
				continue;
			}
			else
			{
				std::vector<Node*>::iterator Position = std::find(_Open.begin(), _Open.end(), NodeForCheck);
				_Open.erase(Position);
				Position = std::find(ImproovedOpen.begin(), ImproovedOpen.end(), NodeForCheck);
				ImproovedOpen.erase(Position);
			}


			ImproovedOpen.push_back(CurrentNode);
		}

	}
}