#pragma once
#include <vector>
#include <map>
#include "Vector2.h"
#include "Node.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
struct MatchingString
{
	std::string string;
	std::vector<Vector2> locationVector;
};

class Manager// TODO: SEARCH ONLY FOR FIRST LETTERS
{
public:
	Manager();
	~Manager();
	void Run();
	void CreatePositionVectorVector();
	void LoadDictionary(std::string filename);
	void CutExtraDictionary();
	bool CheckRareFirstLetter(char letter);
	void CreateAlphabetIndexMap();
	void UserInput();
	void FindMatchingWords();
	void CreateMatch(std::string string, int vectorID, int size);
	void CheckStringWithIndexing(int positionIndex);
	bool CompareShortest(std::string* longWord, std::string* shortWord);
	void ShowResults();
	bool CheckString(std::string* string);
	std::string CreateStringFromPositionVector(std::vector<Vector2>* positionVector);
	// Map for different letter's indexes
	std::map<char, Vector2> indexAreaCharMap;

	std::vector<std::vector<Vector2>> positionVectorVector;
	std::vector<std::string> dictionary;
	std::vector<std::string> shortenedDictionary;
	char input[4][4];
	std::vector<MatchingString> matches;
	Node* root;
};

