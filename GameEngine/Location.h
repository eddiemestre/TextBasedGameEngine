#pragma once

#include "GameEngine.h"
#include <string>
#include <iostream>
#include <utility>
#include <vector>

class Location
{
public:
	Location(class Game* game);
	~Location();

	void SetCoordinates(std::pair<int, int> pair);
	void SetPreviousCoordinates(std::pair<int, int> pair);
	void SetLocationTitle(std::string locationTitle);
	void SetHasVisited(bool value);
	//void SetPrimary(std::string primary);
	//void SetSecondary(std::string secondary);
	void AddNeighborCoordinates(std::pair<int, int> coordinates);
	void AddNeighbors(Location* location);
	void SetStartLocation(bool start);
	void SetEndLocation(bool end);
	void AddLocationText(std::string text);
	void SetNumVisits(int v);

	std::pair<int, int> GetCoordinates() const;
	bool GetHasVisited() const;
	std::pair<int, int> GetPreviousCoordinates() const;
	std::string GetPrimary() const;
	std::string GetSecondary() const;
	std::vector<std::pair<int, int>> GetNeighborCoordinates() const;
	std::vector<std::pair<int, int>> GetConnectedNeighborCoordinates();
	std::vector<Location*> getNeighbors() const;	// test
	std::vector<std::string> GetLocationText();
	std::string GetLocationTitle();
	bool GetIsStartLocation();
	bool GetIsEndLocation();
	int GetNumVisits();


	class Game* GetGame() { return mGame; }

protected:
	class Game* mGame;


private: 
	std::pair<int, int> mCoordinates;
	std::string mLocationTitle;
	std::string mPrimaryText;
	std::string mSecondaryText;
	bool mHasVisited;
	std::pair<int, int> previousCoordinates;
	std::vector<std::pair<int, int>> mNeighborCoordinates;
	std::vector<Location*> neighbors;	// test
	bool mIsStartLocation;
	bool mIsEndLocation;
	std::vector<std::string> mLocationText;
	int mNumVisits;

};
