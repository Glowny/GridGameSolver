#include "Node.h"


Node::Node()
{
}


Node::~Node()
{
}

Node::Node(Node* parent, int generation, Vector2 position, std::vector<std::vector<Vector2>>* positionVectorVector, Vector2 limits)
{
	this->parent = parent;
	this->generation = generation;
	this->position = position;
	this->positionVectorVector = positionVectorVector;
	this->limits = limits;
}

void Node::Run()
{
	// Check if we have reached the last point of search (Last child)
	if (CheckAllDirections() == true)
	{
		// Create the vector of coordinates by going throught all parents.
		CreatePositionVector(this);
	}
}
bool Node::CheckPosition(Vector2 positionToCheck)
{
	if (CheckParents(positionToCheck) && CheckLimits(positionToCheck))
		return true;
	else
		return false;
}
bool Node::CheckLimits(Vector2 positionToCheck)
{
	// Return false if any value is over the limits.
	if (positionToCheck.x < 0 || positionToCheck.x > limits.x
		|| positionToCheck.y < 0 || positionToCheck.y > limits.y)
		return false;
	else return true;
}
bool Node::CheckParents(Vector2 positionToCheck)
{

	// TODO: It is more likely that generations closer to node (higher value)
	// are neighbours to this node, so this should be reversed to boost performance.
	// Should start from generation-1 and go to zero last.
	for (int i = 1; i < generation; i++)
	{
		// Get the generation node we are checking at the moment.
		Node* node = GetGeneration(i);
		// If any of the positions are same as the position being checked,
		//	return false,
		if (node->GetPosition().x == positionToCheck.x &&
			node->GetPosition().y == positionToCheck.y)
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
	Vector2 positionToCheck;

	// Check all four directions
	// TODO: Make this better looking
	positionToCheck.x = position.x - 1; positionToCheck.y = position.y;
	if (CheckPosition(positionToCheck))
	{
		//std::cout << "Creating node on position: X:" << positionToCheck.x << " Y:" << positionToCheck.y << std::endl;
		CreateNewNodeOnPosition(positionToCheck);
		lastNode = false;
	}

	positionToCheck.x = position.x + 1; positionToCheck.y = position.y;
	if (CheckPosition(positionToCheck))
	{
		//std::cout << "Creating node on position: X:" << positionToCheck.x << " Y:" << positionToCheck.y << std::endl;
		CreateNewNodeOnPosition(positionToCheck);
		lastNode = false;
	}

	positionToCheck.x = position.x; positionToCheck.y = position.y-1;
	if (CheckPosition(positionToCheck))
	{
		//std::cout << "Creating node on position: X:" << positionToCheck.x << " Y:" << positionToCheck.y << std::endl;
		CreateNewNodeOnPosition(positionToCheck);
		lastNode = false;
	}

	positionToCheck.x = position.x; positionToCheck.y = position.y + 1;
	if (CheckPosition(positionToCheck))
	{
		//std::cout << "Creating node on position: X:" << positionToCheck.x << " Y:" << positionToCheck.y << std::endl;
		CreateNewNodeOnPosition(positionToCheck);
		lastNode = false;
	}
	
	return lastNode;
}
void Node::CreateNewNodeOnPosition(Vector2 newPosition)
{
	// Gather information for new node
	
	int newNodeGeneration = generation + 1;

	// Create new node, set parent as this node.
	Node* node = new Node(this, newNodeGeneration, newPosition, positionVectorVector, limits);

	// Set the new node to start searching for new node locations.
	node->Run();
	// When node comes back from the search, it has done it's job and it can be deleted to free the space.
	delete node;
}

Vector2 Node::GetPosition()
{
	return position;
}

void Node::AddToPositionVector()
{
	std::vector<Vector2> temporaryPositions;

	// DOES NOT GET HERE 22.12
	for (int i = generation; i > 0; i--)
	{
		// Make sure generation is not 1.
		Node* node = GetGeneration(i);
		temporaryPositions.push_back(node->GetPosition());
	}
	positionVectorVector->push_back(temporaryPositions);

}

void Node::CreatePositionVector(Node* lastNode)
{
	// Remember to start from generation 1
	std::vector<Vector2> tempPositionVector;
	for (int i = 1; i < lastNode->GetGeneration(); i++)
	{
		Node* parent = lastNode->GetGeneration(i);
		tempPositionVector.push_back(parent->GetPosition());
	}
	positionVectorVector->push_back(tempPositionVector);
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
			<< "This node coordinates X:" << this->GetPosition().x << "Y: " << this->GetPosition().y << std::endl;
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