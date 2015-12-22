#include "Manager.h"


Manager::Manager()
{
}


Manager::~Manager()
{
}

void Manager::Run()
{
	CreatePositionVectorVector();
	LoadDictionary("sanakirjatesti.txt");
	
	UserInput();
	FindMatchingWords();
	ShowResults();
}

void Manager::CreatePositionVectorVector()
{
	root = new Node(nullptr, 0, -1, -1, &positionVectorVector); 
	
	// Create new node for each position.
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			root->CreateNewNodeOnPosition(x, y);
		}
	} 
}
void Manager::LoadDictionary(std::string filename)
{
	using namespace std;
	string word;

	ifstream infile;
	infile.open(filename);
	while (infile.eof())
	{
		getline(infile, word);
		dictionary.push_back(word);
	}
	infile.close();

}
// This should be taken at the same time as the loading is done.
// (LoadDictionary, CreatePositionVectorVector)
void Manager::UserInput()
{
	input[0][0] = 'a';
	input[1][0] = 'b';
	input[2][0] = 'c';
	input[3][0] = 'd';
	input[0][1] = 'e';
	input[1][1] = 'f';
	input[2][1] = 'g';
	input[3][1] = 'h';
	input[0][2] = 'i';
	input[1][2] = 'j';
	input[2][2] = 'k';
	input[3][2] = 'l';
	input[0][3] = 'm';
	input[1][3] = 'n';
	input[2][3] = 'o';
	input[3][3] = 'p';
}

void Manager::FindMatchingWords()
{
	for (unsigned int i = 0; i < positionVectorVector.size(); i++)
	{
		std::string testString;
		testString = CreateStringFromPositionVector(&positionVectorVector[i]);
		if (CheckString(&testString))
		{
			MatchingString match;
			match.string = testString;
			match.locationVector = positionVectorVector[i];
			matches.push_back(match);
		}
	}
}
bool Manager::CheckString(std::string* string)
{
	for (unsigned int i = 0; i < dictionary.size(); i++)
	{
		if (dictionary[i] == *string)
			return true;
	}
	return false;
}

std::string Manager::CreateStringFromPositionVector(std::vector<Vector2>* positionVector)
{
	std::string tempString;
	for (unsigned int i = 0; i < positionVector->size(); i++)
		tempString.push_back(input[positionVector->at(i).x][positionVector->at(i).y]);
	return tempString;
}

void Manager::ShowResults()
{
	std::cout << "Results: " << std::endl;
	for (unsigned int i = 0; i < matches.size(); i++)
	{
		std::cout << matches[i].string << std::endl;
	}
}