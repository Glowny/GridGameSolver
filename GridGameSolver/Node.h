#pragma once
#include <vector>
#include "Vector2.h"

//For debugging.
#include <iostream>

class Node
{
public:
	Node();
	Node(Node* parent, int generation, Vector2 position, std::vector<std::vector<Vector2>>* PositionVectorVector, Vector2 limits);
	~Node();
	void Run();
	bool CheckPosition(Vector2 positionToCheck);
	bool CheckAllDirections();
	void CreateNewNodeOnPosition(Vector2 position);
	Node* GetGeneration(int generation);
	Node* GetParent();
	void SetParent(Node* parent);
	int GetGeneration();
	void SetGeneration(int generation);
	Vector2 GetPosition();
	void AddToPositionVector();
	void CreatePositionVector(Node* lastNode);
private:
	bool CheckLimits(Vector2 positionToCheck);
	bool CheckParents(Vector2 positionToCheck);
	Node* parent;
	int generation;
	Vector2 position;
	Vector2 limits;
	// If this is heavy, can we make a wrapper class that holds the information,
	// and has private positionVector. Only function addVector.
	std::vector<std::vector<Vector2>>* positionVectorVector;
};

