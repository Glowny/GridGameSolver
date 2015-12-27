#pragma once
#include <vector>
#include <map>
#include "Node.h"
#include "Rotations.h"
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
	void CutExtraPositions();
	void CreateSymmetricalPositionVectors(int startIndex, int endIndex, int type);
	void LoadDictionary(std::string filename);
	void CutExtraDictionary(int maxLenght, int minLenght);
	void RemakeDictionary();
	void SaveRemadeDictionary();
	void LoadRemadeDictionary();
	bool CheckRareFirstLetter(int dictionaryIndex);
	void CreateAlphabetIndexMap();
	void UserInput();
	void SetOptions();
	void FindMatchingWords();
	void CreateMatch(std::string string, int vectorID, int size);
	void CheckStringWithIndexing(int positionIndex);
	bool CompareShortest(std::string* longWord, std::string* shortWord);
	void ShowResults();
	bool CheckString(std::string* string);
	std::string CreateStringFromPositionVector(std::vector<Vector2>* positionVector);
	// Map for different letter's indexes
	std::map<std::string, Vector2> indexAreaCharMap;

	std::vector<std::vector<Vector2>> positionVectorVector;
	std::vector<std::string> dictionary;
	std::vector<std::string> shortenedDictionary;
	std::vector<std::string> finalDictionary;
	char input[4][4];
	std::vector<MatchingString> matches;
	Node* root;
private:
	// User sets.
	unsigned int maxWordLenght, minWordLenght;
	bool xModeEnabled;
	bool preDone;
	Vector2 limits;
	//
	std::vector<std::string> temp√Words;
	std::vector<std::string> temp≈Words;
	std::vector<std::string> tempöWords;
	std::vector<std::string> tempwWords;
};

