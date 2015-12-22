#include "Node.h"


Node::Node()
{
}


Node::~Node()
{
}

Node::Node(Node* parent, int generation, int positionX, int posiitonY, std::vector<std::vector<Vector2>>* positionVectorVector)
{
	this->parent = parent;
	this->generation = generation;
	this->positionX = positionX;
	this->positionY = positionY;
	this->positionVectorVector = positionVectorVector;
}

void Node::Run()
{
	// Check if we have reached the last point of search (Last child)
	if (CheckAllDirections() == true)
	{
		// Create the vector of coordinates by going throught all parents.
	}
}
bool Node::CheckPosition(int directionX, int directionY)
{
	int xPositionToCheck = directionX;
	int yPositionToCheck = directionY;

	// TODO: It is more likely that generations closer to node (higher value)
	// are neighbours to this node, so this should be reversed to boost performance.
	// Should start from generation-1 and go to zero last.
	for (int i = 1; i < generation; i++)
	{
		// Get the generation node we are checking at the moment.
		Node* node = GetGeneration(i);
		// If any of the positions are same as the position being checked,
		//	return false,
		if (node->GetPositionX() == xPositionToCheck &&
			node->GetPositionY() == yPositionToCheck)
		{
			return false;
		}
	}
	// If no blocking nodes are found, return true.
	return true;
}
bool Node::CheckAllDirections()
{
	bool lastNode = true;
	int xCheck, yCheck;

	// Check all four directions
	xCheck = positionX - 1; yCheck = positionY;
	if (CheckPosition(xCheck, yCheck))
	{
		CreateNewNodeOnPosition(xCheck, yCheck);
		lastNode = false;
	}

	xCheck = positionX + 1; yCheck = positionY;
	if (CheckPosition(xCheck, yCheck))
	{
		CreateNewNodeOnPosition(xCheck, yCheck);
		lastNode = false;
	}

	xCheck = positionX; yCheck = positionY - 1;
	if (CheckPosition(xCheck, yCheck))
	{
		CreateNewNodeOnPosition(xCheck, yCheck);
		lastNode = false;
	}

	xCheck = positionX; yCheck = positionY + 1;
	if (CheckPosition(xCheck, yCheck))
	{
		CreateNewNodeOnPosition(xCheck, yCheck);
		lastNode = false;
	}

	return lastNode;
}
void Node::CreateNewNodeOnPosition(int positionX, int positionY)
{
	// Gather information for new node

	int newNodePositionX = positionX + positionX;
	int newNodePositionY = positionY + positionY;
	int newNodeGeneration = generation + 1;

	// Create new node, set parent as this node.
	Node* node = new Node(this, newNodeGeneration, newNodePositionX, newNodePositionY, positionVectorVector);

	// Set the new node to start searching for new node locations.
	node->Run();
	// When node comes back from the search, it has done it's job and it can be deleted to free the space.
	delete node;
}

int Node::GetPositionX()
{
	return positionX;
}
int Node::GetPositionY()
{
	return positionY;
}

void Node::AddToPositionVector()
{
	std::vector<Vector2> temporaryPositions;

	// DOES NOT GET HERE 22.12
	for (int i = generation; i > 0; i--)
	{
		// Make sure generation is not 1.
		Node* node = GetGeneration(i);
		Vector2 position;
		position.x = node->GetPositionX();
		position.y = node->GetPositionY();
		temporaryPositions.push_back(position);
	}
	positionVectorVector->push_back(temporaryPositions);

}

Node* Node::GetParent()
{
	return parent;
}

// When calling this, make sure the generation exists.
Node* Node::GetGeneration(int generation)
{
	// If this node is generation we are searching for, return it.
	if (this->generation == generation)
	{
		return this;
	}
	// Else call parent to search for generation, and return it.
	else
	{
		// Make sure this uses parameter 'generation'
		if (this->parent == nullptr)
			std::cout << "DO NOT SEARCH FOR GENERATION 0, IT IS ROOT." << std::endl
			<< "Searched generation: " << generation << "This node generation: " << this->generation << std::endl
			<< "This node coordinates X:" << this->GetPositionX() << "Y: " << this->GetPositionY() << std::endl;
		return parent->GetGeneration(generation);
	}
}
void Node::SetParent(Node* parent)
{
	this->parent = parent;
}
int Node::GetGeneration()
{
	return generation;
}
void Node::SetGeneration(int generation)
{
	this->generation = generation;
}