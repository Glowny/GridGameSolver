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
	std::cout << "Node creation done" << std::endl;
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
	return true;
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
	std::cout << "Give me a 16-letter word to fill 4x4 grid. For example: " << std::endl;
	std::cout << "abcdefghijklmnop will be used on grid this way:" << std::endl;

	std::cout << " _ _ _ _" << std::endl;
	std::cout << "|a|b|c|d|" << std::endl;
	std::cout << " _ _ _ _" << std::endl;
	std::cout << "|e|f|g|h|" << std::endl;
	std::cout << " _ _ _ _" << std::endl;
	std::cout << "|i|j|k|l|" << std::endl;
	std::cout << " _ _ _ _" << std::endl;
	std::cout << "|m|n|o|p|" << std::endl;
	std::cout << " _ _ _ _" << std::endl;

	std::cout << "Extra input will be cut. Give zero(0) to use default input" << std::endl;

	std::string inputString;
	std::cin >> inputString;

	if (inputString[0] == '0' || inputString.size() < 16)
	{
		input[0][0] = 's';	input[1][0] = 'a';	input[2][0] = 'n';	input[3][0] = 'i';
		input[0][1] = 't';	input[1][1] = 'a';	input[2][1] = 'a';	input[3][1] = 'a';
		input[0][2] = 'b';	input[1][2] = 't';	input[2][2] = 's';	input[3][2] = 'i';
		input[0][3] = 't';	input[1][3] = 'o';	input[2][3] = 'e';	input[3][3] = 'n';
	}
	else
	{
		int inputIndex = 0;
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				input[x][y] = inputString[inputIndex];
				inputIndex++;
			}
		}
	}

}

void Manager::FindMatchingWords()
{
	for (unsigned int i = 0; i < positionVectorVector.size(); i++)
	{
		 CheckStringWithIndexing(i);
	}
}
void Manager::CreateMatch(std::string string, int vectorID, int size)
{
	MatchingString match;

	match.string = string;
	match.string.resize(size);
	match.locationVector = positionVectorVector[vectorID];
	match.locationVector.resize(size);

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
void Manager::CheckStringWithIndexing(int positionIndex)
{
	std::string testString;
	testString = CreateStringFromPositionVector(&positionVectorVector[positionIndex]);

	Vector2 beginEnd = indexAreaCharMap[testString[0]];

	for (int i = beginEnd.x; i <= beginEnd.y; i++)
	{
		// Get current checked word size.
		unsigned int currentWordSize = shortenedDictionary[i].size();
		
		// Resize the temporary word to same size as word we are comparing it to.
		if (CompareShortest(&testString, &shortenedDictionary[i]))
		{
			CreateMatch(testString, positionIndex, currentWordSize);
		}
	}
}
bool Manager::CompareShortest(std::string* longWord, std::string* shortWord)
{
	// If longword is shorter than shortword do not compare.
	if (longWord->size() < shortWord->size())
		return false;
	// Go throught every shortWord letter, and if any of them differs, return false.
	for (int i = 0; i < shortWord->size(); i++)
	{
		{
			if (longWord->at(i) != shortWord->at(i))
			return false;
		}
	}
	return true;
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