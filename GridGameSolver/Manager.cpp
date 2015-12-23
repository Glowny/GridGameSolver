#include "Manager.h"


Manager::Manager()
{
}


Manager::~Manager()
{
}

void Manager::Run()
{
	LoadDictionary("kotus_sanat.txt");
	CutExtraDictionary();
	CreateAlphabetIndexMap();
	CreatePositionVectorVector();
	
	UserInput();
	FindMatchingWords();
	ShowResults();
}

void Manager::CreatePositionVectorVector()
{
	Vector2 limits;
	limits.x = 3;
	limits.y = 3;
	Vector2 position;
	position.x = -1;
	position.y = -1;
	root = new Node(nullptr, 0, position, &positionVectorVector, limits); 
	
	// Create new node for each position.
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			position.x = x;
			position.y = y;
			root->CreateNewNodeOnPosition(position);
		}
	} 
}
void Manager::LoadDictionary(std::string filename)
{
	using namespace std;
	string word;

	ifstream file(filename);
	if (file.is_open())
	{
		while (getline(file, word))
		{
			dictionary.push_back(word);
		}
		file.close();
	}
	else cout << "Unable to open file: " << filename << std::endl;
	
	cout << "Read " << dictionary.size() << " words." << std::endl;

}

void Manager::CutExtraDictionary()
{
	for (unsigned int i = 0; i < dictionary.size(); i++)
	{
		// Remove words longer than 16 char. Or it has - at beginning, or letters not often used.
		if (dictionary[i].size() <= 16 && dictionary[i][0] != '-' && CheckRareFirstLetter(dictionary[i][0]))
		{
			// Change first letter to lowercase to help this
			char charToChange = dictionary[i][0];
			dictionary[i][0] = tolower(charToChange);

			shortenedDictionary.push_back(dictionary[i]);
		}
	}
	std::cout << "Smaller or equal than 16 shortened dictionary size: " << shortenedDictionary.size() << std::endl;

}
bool Manager::CheckRareFirstLetter(char letter)
{
	if (letter == 'À' || letter == 'Ã' || letter == 'Å' || letter == 'š')
		return false;
}


void Manager::CreateAlphabetIndexMap()
{
	std::string currentString = shortenedDictionary[0];
	char currentChar = currentString[0];
	int currentStartIndex = 0;
	int currentEndIndex = 0;
	for (unsigned int i = 0; i < shortenedDictionary.size(); i++)
	{
		currentString = shortenedDictionary[i];
		// If first element of string is not same current element
		if (currentString[0] != currentChar)
		{
			// Last index where this letter is first letter.
			// TODO: check if it is i-1, this might work too
			currentEndIndex = i;
			Vector2 indexes;
			indexes.x = currentStartIndex;
			indexes.y = currentEndIndex;
			// Add begin and end index to map where key is the first charachter
			indexAreaCharMap[currentChar] = indexes;
			
			// Set the new first charachter
			currentStartIndex = i;
			currentChar = currentString[0];
			// REORDER V AND W TO BE ON CORRECT POSITIONS, AND CREATE A NEW DICTIONARY
		}
	}
}

// This should be taken at the same time as the loading is done.
// (LoadDictionary, CreatePositionVectorVector)
void Manager::UserInput()
{
	input[0][0] = 'a';	input[1][0] = 'l';	input[2][0] = 'k';	input[3][0] = 'o';
	input[0][1] = 'i';	input[1][1] = 'l';	input[2][1] = 'o';	input[3][1] = 'h';
	input[0][2] = 't';	input[1][2] = 'o';	input[2][2] = 'n';	input[3][2] = 'a';
	input[0][3] = 'e';	input[1][3] = 'i';	input[2][3] = 'p';	input[3][3] = 'p';
}

void Manager::FindMatchingWords()
{
	for (unsigned int i = 0; i < positionVectorVector.size(); i++)
	{
		std::string testString;
		testString = CreateStringFromPositionVector(&positionVectorVector[i]);
		int size = CheckStringWithIndexing(&testString);
		if (size != 0)
		{
			testString.resize(size);
			std::vector<Vector2> positionVector = positionVectorVector[i];
			positionVector.resize(size);
			CreateMatch(testString, positionVector);
		}
	}
}
void Manager::CreateMatch(std::string string, std::vector<Vector2> positions)
{
	MatchingString match;
	match.string = string;
	match.locationVector = positions;
	bool push = true;
	for (unsigned int i = 0; i < matches.size(); i++)
	{	
		if (matches[i].string == match.string)
		{
			push = false;
		}	
	}
	if (push)
		matches.push_back(match);
}
int Manager::CheckStringWithIndexing(std::string* string)
{
	Vector2 beginEnd = indexAreaCharMap[string->at(0)];
	for (unsigned int i = beginEnd.x; i <= beginEnd.y; i++)
	{
		// Get current word
		std::string tempString = *string;
		// Get current checked word size.
		unsigned int currentWordSize = shortenedDictionary[i].size();
		
		// Resize the temporary word to same size as word we are comparing it to.
		tempString.resize(currentWordSize);

		if (shortenedDictionary[i] == tempString)
			return currentWordSize;
	}
	return 0;
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
	std::cout <<"Amount of possible strings:"<<positionVectorVector.size() << std::endl;
	for (unsigned int i = 0; i < matches.size(); i++)
	{
		std::cout << matches[i].string << std::endl;
	}
}