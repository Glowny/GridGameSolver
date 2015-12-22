#pragma once
#include <vector>
#include "Vector2.h"

//For debugging.
#include <iostream>

class Node
{
public:
	Node();
	Node(Node* parent, int generation, int positionX, int positionY, std::vector<std::vector<Vector2>>* PositionVectorVector);
	~Node();
	void Run();
	bool CheckPosition(int directionX, int directionY);
	bool CheckAllDirections();
	void CreateNewNodeOnPosition(int positionX, int positionY);
	Node* GetGeneration(int generation);
	Node* GetParent();
	void SetParent(Node* parent);
	int GetGeneration();
	void SetGeneration(int generation);
	int GetPositionX();
	int GetPositionY();
	void AddToPositionVector();
private:
	Node* parent;
	int generation;
	int positionX, positionY; 
	// If this is heavy, can we make a wrapper class that holds the information,
	// and has private positionVector. Only function addVector.
	std::vector<std::vector<Vector2>>* positionVectorVector;
};

