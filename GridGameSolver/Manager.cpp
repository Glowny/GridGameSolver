#include "Manager.h"


Manager::Manager()
{
	
}


Manager::~Manager()
{
}

void Manager::Run()
{
	SetOptions();

	if (preDone)
	{
		LoadRemadeDictionary();
	}
	else
	{
		LoadDictionary("kotus_sanat.txt");
		CutExtraDictionary(maxWordLenght, minWordLenght);
		RemakeDictionary();
	}
	CreateAlphabetIndexMap();

	CreatePositionVectorVector();
	CutExtraPositions();

	UserInput();

	FindMatchingWords();
	ShowResults();
}

void Manager::CreatePositionVectorVector()
{
	std::cout << "Solving all possible combinations on " << limits.x << "x" << limits.y << " grid" << std::endl;
	Vector2 position;
	position.x = -1;
	position.y = -1;
	Vector2 nodeLimits(limits.x - 1, limits.y - 1);

	Node::limits = nodeLimits;
	Node::positionVectorVector = &positionVectorVector;
	root = new Node(nullptr, 0, position);

	// Create new node for each position.

	int endIndexForSource[3];
	position.x = 0;
	position.y = 0;
	std::cout << "Creating new source node on position: " << position.x << ", " << position.y << "." << std::endl;
	root->CreateNewNodeOnPosition(position);
	// Note! This is not the end, but end + 1!
	endIndexForSource[0] = positionVectorVector.size();

	position.x = 1;
	position.y = 0;
	std::cout << "Creating new source node on position: " << position.x << ", " << position.y << "." << std::endl;
	root->CreateNewNodeOnPosition(position);
	endIndexForSource[1] = positionVectorVector.size();

	
	position.x = 1;
	position.y = 1;
	std::cout << "Creating new source node on position: " << position.x << ", " << position.y << "." << std::endl;
	root->CreateNewNodeOnPosition(position);
	endIndexForSource[2] = positionVectorVector.size();

	// Create rest of NodeVectors.
	std::cout << "Duplicating found nodevectors.. " << std::endl;
	CreateSymmetricalPositionVectors(0, endIndexForSource[0], 4);
	std::cout << "Duplicating found nodevectors 1/3 done.. " << std::endl;
	CreateSymmetricalPositionVectors(endIndexForSource[0], endIndexForSource[1], 8);
	std::cout << "Duplicating found nodevectors 2/3 done.. " << std::endl;
	CreateSymmetricalPositionVectors(endIndexForSource[1], endIndexForSource[2], 4);

	std::cout << "Node creation done, possible solutions: " << positionVectorVector.size() << std::endl;
}
void Manager::CutExtraPositions()
{
	std::cout << "Removing combinations shorter than " << minWordLenght <<" current size:"<<positionVectorVector.size()<< std::endl;
	std::vector<std::vector<Vector2>> tempVector;

	// TODO: Recreate later to use iterators and delete, makes this more fast.

	for (unsigned int i = 0; i < positionVectorVector.size(); i++)
	{
		if (positionVectorVector[i].size() >= minWordLenght)
		{
			tempVector.push_back(positionVectorVector[i]);
		}
	}
	positionVectorVector = tempVector;

	std::cout << "Combination-vector size after cutting too short words" << positionVectorVector.size();
}
void Manager::CreateSymmetricalPositionVectors(int startIndex, int endIndex, int type)
{
	// Type = how many similiar start positions there are. Note! Source is counted on this.
	
	// Three copies.
	

	
	for (int i = startIndex; i < endIndex; i++)
	{
		std::vector<Vector2> mirrorCopy[3];
		for (int j = 0; j < positionVectorVector[i].size(); j++)
		{
			mirrorCopy[0].push_back(Rotate::RotateOnAxis(positionVectorVector[i][j], Rotate::Y));
			mirrorCopy[1].push_back(Rotate::RotateOnAxis(positionVectorVector[i][j], Rotate::X));
			mirrorCopy[2].push_back(Rotate::RotateOnAxis(positionVectorVector[i][j], Rotate::XY));
		}
		for (int i = 0; i < 3; i++)
		positionVectorVector.push_back(mirrorCopy[i]);
	}
	
		
	if (type = 8)
	{
		
		for (int i = startIndex; i < endIndex; i++)
		{
			std::vector<Vector2> axisSwapCopy[4];
			for (int j = 0; j < positionVectorVector[i].size(); j++)
			{
				axisSwapCopy[0].push_back(Rotate::SwapAxis(positionVectorVector[i][j]));
				axisSwapCopy[1].push_back(Rotate::SwapAxis(Rotate::RotateOnAxis(positionVectorVector[i][j], Rotate::Y)));
				axisSwapCopy[2].push_back(Rotate::SwapAxis(Rotate::RotateOnAxis(positionVectorVector[i][j], Rotate::X)));
				axisSwapCopy[3].push_back(Rotate::SwapAxis(Rotate::RotateOnAxis(positionVectorVector[i][j], Rotate::XY)));
			}
			for (int i = 0; i < 4; i++)
				positionVectorVector.push_back(axisSwapCopy[i]);
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

void Manager::CutExtraDictionary(int maxLenght, int minLenght)
{
	for (unsigned int i = 0; i < dictionary.size(); i++)
	{
		// Remove words longer than 16 char. Or it has - at beginning, or letters not often used.
		if (dictionary[i].size() >= minLenght && dictionary[i].size() <= maxLenght && dictionary[i][0] != '-' && CheckRareFirstLetter(i))
		{
			// Change first letter to lowercase to help this
			char charToChange = dictionary[i][0];
			dictionary[i][0] = tolower(charToChange);

			shortenedDictionary.push_back(dictionary[i]);
		}
	}
	std::cout << "Smaller or equal than "<< limits.x*limits.y << " shortened dictionary size: " << shortenedDictionary.size() << std::endl;

}
void Manager::RemakeDictionary()
{

	char firstChar = shortenedDictionary[0][0];
	for (unsigned int i = 0; i < shortenedDictionary.size(); i++)
	{
		if (firstChar == 'a')
		{
			if (shortenedDictionary[i][0] == 'b')
			{
				for (unsigned int i = 0; i < tempÃWords.size(); i++)
				{
					finalDictionary.push_back(tempÃWords[i]);
				}
				for (unsigned int i = 0; i < tempÅWords.size(); i++)
				{
					finalDictionary.push_back(tempÅWords[i]);
				}
			}
		}
		else if (firstChar == 's')
		{
			if (shortenedDictionary[i][0] == 't')
			{
				for (unsigned int i = 0; i < tempšWords.size(); i++)
				{
					finalDictionary.push_back(tempšWords[i]);
				}
			}
		}

		else if (firstChar == 'v')
		{
			if (shortenedDictionary[i][0] == 'x')
			{
				for (unsigned int i = 0; i < tempwWords.size(); i++)
				{
					finalDictionary.push_back(tempwWords[i]);
				}
			}
		}
		finalDictionary.push_back(shortenedDictionary[i]);
		firstChar = shortenedDictionary[i][0];
	}
	SaveRemadeDictionary();
}

bool Manager::CheckRareFirstLetter(int dictionaryIndex)
{
	// This has to be done because these letters are mixed in dictionary with normal letters, for example
	
	//Ã la
	//ala
	//Ã la carte

	// This causes pointers to first and last letter index to go wrong.

	char letter = dictionary[dictionaryIndex][0];
	if (letter == 'Ã' || letter == 'Å' || letter == 'š' || letter == 'w')
	{
		if (dictionary[dictionaryIndex][0] == 'Ã')
			tempÃWords.push_back(dictionary[dictionaryIndex]);
		else if (dictionary[dictionaryIndex][0] == 'Å')
			tempÅWords.push_back(dictionary[dictionaryIndex]);
		else if (dictionary[dictionaryIndex][0] == 'š')
			tempšWords.push_back(dictionary[dictionaryIndex]);
		else if (dictionary[dictionaryIndex][0] == 'w')
			tempwWords.push_back(dictionary[dictionaryIndex]);
		return false;
	}
		
	return true;
}
void Manager::SaveRemadeDictionary()
{
	std::ofstream output_file("dictionary.data");
	std::ostream_iterator<std::string> output_iterator(output_file, "\n");
	std::copy(finalDictionary.begin(), finalDictionary.end(), output_iterator);
	std::cout << "Remade dictionary done" << std::endl;
}
void Manager::LoadRemadeDictionary()
{
	std::cout << "Loading premade dictionary.." << std::endl;
	std::string line;
	std::ifstream myfile("dictionary.data");
	std::vector<std::string> myLines;
	while (std::getline(myfile, line))
	{
		finalDictionary.push_back(line);
	}
	std::cout << "Premade dictionary loaded, size:" << finalDictionary.size() << std::endl;
}

void Manager::CreateAlphabetIndexMap()
{
	
	std::cout << "Creating dictionary indexes for final dictionary.." << std::endl;
	std::string currentString = finalDictionary[0];
	std::string currentChar;
	currentChar[0] = currentString[0];
	currentChar[1] = currentString[1];

	int currentStartIndex = 0;
	int currentEndIndex = 0;
	for (unsigned int i = 0; i < finalDictionary.size(); i++)
	{
		currentString = finalDictionary[i];
		// If first element of string is not same current element

		if (currentString[1] != currentChar[1] || currentString[0] != currentChar[0])
		{	
			// Last index where this letter is first letter.
			// TODO: check if it is i-1, this might work too
			currentEndIndex = i;
			Vector2 indexes;
			indexes.x = currentStartIndex;
			indexes.y = currentEndIndex;
			// Add begin and end index to map where key is the first charachter
			currentChar[0] = currentString[0];
			currentChar[1] = currentString[1];
			indexAreaCharMap[currentChar] = indexes;

			// Set the new first charachter
			currentStartIndex = i;
		}
	}
	

}

// This should be taken at the same time as the loading is done.
// (LoadDictionary, CreatePositionVectorVector)
void Manager::SetOptions()
{
	std::cout << "Skip settings? (0 = skip)" << std::endl;
	bool skip = 0;
	std::cin >> skip;

	if (skip != 0)
	{
		std::cout << "Read premade dictionary? (0/1)" << std::endl;
		std::cin >> preDone;
		std::cout << "Give grid size on x direction (default 4)" << std::endl;
		//std::cin >> limits.x;
		std::cout << "Give grid size on y direction (default 4)" << std::endl;
		//std::cin >> limits.y;
		std::cout << "Give minimun word lenght" << std::endl;
		std::cin >> minWordLenght;
		std::cout << "Enable x-mode?(0 or 1)" << std::endl;
		std::cin >> xModeEnabled;

		limits.x = 4; limits.y = 4;
	}
	else
	{
		preDone = false;
		limits.x = 4; limits.y = 4;
		Rotate::limits = limits;
		minWordLenght = 1;
		xModeEnabled = true;
	}
	maxWordLenght = limits.x * limits.y;

}
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
		input[0][0] = 'r';	input[1][0] = 'e';	input[2][0] = 'r';	input[3][0] = 'n';
		input[0][1] = 't';	input[1][1] = 't';	input[2][1] = 'i';	input[3][1] = 'a';
		input[0][2] = 'a';	input[1][2] = 's';	input[2][2] = 'p';	input[3][2] = 'i';
		input[0][3] = 'w';	input[1][3] = 'e';	input[2][3] = '-';	input[3][3] = 'n';
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
	std::cout << "Beginning to find matching words..." << std::endl;
	for (unsigned int i = 0; i < positionVectorVector.size(); i++)
	{
		 CheckStringWithIndexing(i);
	}
	std::cout << "Words found: " << matches.size();
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
	{
		matches.push_back(match);
		std::cout << "Found match: " << match.string << std::endl << ". Positions: || X: ";
		for (unsigned int i = 0; i < match.locationVector.size(); i++)
		{
			std::cout << match.locationVector[i].x << ", Y: " << match.locationVector[i].y << " || X: ";
		}
		std::cout<<std::endl;
	}
		
}
void Manager::CheckStringWithIndexing(int positionIndex)
{
	std::string testString;
	testString = CreateStringFromPositionVector(&positionVectorVector[positionIndex]);
	std::string tempChar;
	tempChar[0] = testString[0]; tempChar[1] = testString[1];
	Vector2 beginEnd = indexAreaCharMap[tempChar];

	for (int i = beginEnd.x; i <= beginEnd.y; i++)
	{
		// Get current checked word size.
		unsigned int currentWordSize = finalDictionary[i].size();
		
		// Resize the temporary word to same size as word we are comparing it to.
		if (CompareShortest(&testString, &finalDictionary[i]))
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
	for (unsigned int i = 0; i < shortWord->size(); i++)
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
	std::cin >> preDone;
}