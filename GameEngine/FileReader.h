#pragma once

#include "GameEngine.h"
#include "Location.h"
#include <string>
#include <iostream>
#include <stack>

class Location;

class FileReader
{
public:
	FileReader(class Game* game);
	void ReadLocationData(const std::string locationFile);
	//int GetCoordTwo();
	//std::string GetTextOne();
	//std::string GetTextTwo();

private:
	std::string coordOne;
	std::string coordTwo;
	std::string textOne;
	std::string textTwo;

	int mCoordX;
	int mCoordY;
	int mCoordTwoX;
	int mCoordTwoY;

	std::stack<Location*> locationStack;

protected:
	class Game* mGame;
	class Location* mLocation;

};
