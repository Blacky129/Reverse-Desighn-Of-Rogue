#include "CPathFinder.h"
#include <algorithm>

Node::Node(CPosition From, CPosition To, int ValueToNode, CPosition Goal)
{
	_From = From;
	_To = To;
	_ValueToNode = ValueToNode;
	_ValueToSourse = sqrt(pow(Goal.X - To.X, 2) + pow(Goal.Y - To.Y, 2));
}

void Stack::addNode(Node* Node)
{
	while (Node->_ValueToNode >= (_Stack.size()))
	{
		initNewVector();
	}

	_Stack.at(Node->_ValueToNode)->push_back(Node);
}

void Stack::deleteNode(Node* Node)
{
	for (int Index = 0; Index < _Stack.size(); Index++)
	{
		for (int Index2 = 0; Index2 < _Stack.at(Index)->size(); Index2++)
		{
			if (_Stack.at(Index)->at(Index2) == Node)
			{
				_Stack.at(Index)->erase(_Stack.at(Index)->begin() + Index2);
				delete Node;
				return;
			}
		}
	}
}

void Stack::initNewVector()
{
	_Stack.push_back(new std::vector < Node*>);
}

void Stack::clearStack()
{
	_Stack.clear();
}

CPathFinder::CPathFinder()
{
	_Map = nullptr;
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
	for (Node* CurrentNode : _Open)
		delete CurrentNode;

	_Open = {};

	for (Node* CurrentNode : _Closed)
		delete CurrentNode;
	
	_Closed = {};
}

CPosition CPathFinder::getVectorToGoal(CPosition From, CPosition Goal)
{
	clearOpenAndClosed();

	_PathStack.clearStack();

	_Open.push_back(new Node{ CPosition{-1, -1}, From, 0 , Goal});

	while (_Open.size() != 0)
	{
		Node* NewNode = findNewNodeToExtend();

		if (NewNode->_To == Goal)
		{
			std::vector<Node*>::iterator Position = std::find(_Open.begin(), _Open.end(), NewNode);
			_Open.erase(Position);
			_Closed.push_back(NewNode);
			break;
		}

		extendNode(NewNode, Goal);
	}

	for (Node* __Node : _Closed)
		_PathStack.addNode(__Node);

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

void CPathFinder::extendNode(Node* CurrentNode, CPosition Goal)
{
	std::vector<CPosition> ExtendedPostions = {
		CurrentNode->_To + CPosition{ -1, -1 }, CurrentNode->_To + CPosition{ +0, -1 }, CurrentNode->_To + CPosition{ +1, -1 },
	    CurrentNode->_To + CPosition{ -1, +0 },			                                CurrentNode->_To + CPosition{ +1, +0 },
	    CurrentNode->_To + CPosition{ -1, +1 }, CurrentNode->_To + CPosition{ +0, +1 }, CurrentNode->_To + CPosition{ +1, +1 } 
	};

	for (CPosition NextPosition : ExtendedPostions)
	{
		if (isCellPathable(NextPosition, CurrentNode->_To) == false)
			continue;

		if (isPositionInClosed(NextPosition) == true)
			continue;
		
		Node* NewNode = new Node{ CurrentNode->_To, NextPosition, CurrentNode->_ValueToNode + 1, Goal };
		
		improoveOpen(NewNode);
	}

	std::vector<Node*>::iterator Position = std::find(_Open.begin(), _Open.end(), CurrentNode);
	_Closed.push_back(CurrentNode);
	_Open.erase(Position);
}

bool CPathFinder::isCellPathable(CPosition Source, CPosition To)
{
	if (Source.X < 0 || Source.Y < 0 || Source.X > _Map->getSizeOfMap().X || Source.Y > _Map->getSizeOfMap().Y)
		return false;

	if (_Map->getTypeOfIteration(Source) != TypeIteration::Move)
		return false;

	if (CPosition{ Source - To }.getVectorLength() > 1)
		return _Map->isCanGoByDiagonal(Source, To);

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

void CPathFinder::improoveOpen(Node* NewNode)
{


	for (Node* CurrentNode : _Open)
	{
		if (!(CurrentNode->_To == NewNode->_To))
			continue;
			
		if (CurrentNode->_ValueToNode < NewNode->_ValueToNode)
		{
			delete NewNode;
			return;
		}

		std::vector<Node*>::iterator Position = std::find(_Open.begin(), _Open.end(), CurrentNode);
		_Open.erase(Position);
		delete CurrentNode;
	}


	_Open.push_back(NewNode);
}