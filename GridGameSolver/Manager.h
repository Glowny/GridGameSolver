#pragma once
#include <vector>
#include "Vector2.h"
#include "Node.h"
#include <string>
#include <iostream>
#include <fstream>
struct MatchingString
{
	std::string string;
	std::vector<Vector2> locationVector;
};

class Manager
{
public:
	Manager();
	~Manager();
	void Run();
	void CreatePositionVectorVector();
	void LoadDictionary(std::string filename);
	void UserInput();
	void FindMatchingWords();
	void ShowResults();
	bool CheckString(std::string* string);
	std::string CreateStringFromPositionVector(std::vector<Vector2>* positionVector);
	

	std::vector<std::vector<Vector2>> positionVectorVector;
	std::vector<std::string> dictionary;
	char input[4][4];
	std::vector<MatchingString> matches;
	Node* root;
};

