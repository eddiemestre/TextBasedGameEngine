#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "FileReader.h"
#include "Location.h"
#include <vector>
#include <unordered_map>
#include <map>

namespace constants {
	// location data
	const std::string LOCATION_DATA_FILE = "../Assets/location_data.txt";
	// action data TBD
}

// hash function
struct hash_pair {
	template <class T1, class T2>
	size_t operator()(const std::pair<T1, T2>& p) const {
		auto hash1 = std::hash<T1>{}(p.first);
		auto hash2 = std::hash<T2>{}(p.second);
		return hash1 ^ hash2;

	}
};

class Location;
class FileReader;

class Game {
public:
	Game();
	bool Initialize();
	void Shutdown();
	void RunLoop();
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void AddLocation(Location* location);
	void RemoveLocation(Location* location);
	std::vector<std::pair<std::string, std::pair<int, int>>> DisplayMath(std::vector<std::pair<int, int>> const &locations);
	void DirectionSort(std::vector<std::pair<std::string, std::pair<int, int>>> &locations);
	void DFSUtility(const Location* loc);
	void AddIntroText(std::string &introtext);
	void LocationConnector(std::vector<Location*> locations);
	void SetStartIndex(const std::vector<Location*>& locations);
	void SetEndIndex(const std::vector<Location*>& locations);


private:
	// Eventual window and renderer


	// condition for running loop
	bool runLoop = true;
	void LoadData();
	void UnloadData();
	class std::vector<Location*> locationVector;
	class Location* mLocation;
	class FileReader* mFileReader;

	std::pair<int, int> currentNode;
	std::pair<int, int> previousNode;
	std::vector<std::pair<std::string, std::pair<int, int>>> mDirectionVector;
	std::vector<std::pair<std::string, std::pair<int, int>>> mSortedDirectionVector;
	std::unordered_map<std::pair<int, int>, bool, hash_pair> visitedMap;

	int mStartIndex;
	int mEndIndex;

	std::vector<std::string> mIntroText;

	// Compass or POV directions
	bool mCompass;
	
	// bool to check valid input
	bool mValidInput;
	bool mNorthStraight;
	bool mSouthPrevious;
	bool mWestLeft;
	bool mEastRight;

	// map
	//std::unordered_map <std::pair<int, int>, std::vector<std::pair<int, int>>> mLookupMap;


};
