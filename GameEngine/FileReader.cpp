#include "FileReader.h"
#include <fstream>

FileReader::FileReader(class Game* game)
	: mGame(game)
{
	// read input from file
	// put it in data structure
	//coordOne = "(0,0)";
	//textOne = "A long hallway.";
	//coordTwo = "(0,1)";
	//textTwo = "An empty room.";

	//coordOneX = 0;
	//coordOneY = 0;
	//coordTwoX = 0;
	//coordTwoY = 1;

	mLocation = new Location(game);

	//mLocation->coordinates.first = coordOneX;
	//mLocation->coordinates.second = coordOneY;
	//mLocation->primaryText = textOne;

	//mGame->AddLocation(mLocation);
	
}

void FileReader::ReadLocationData(const std::string locationFile)
{
	std::string line;
	std::ifstream locationData;
	std::string temp;
	locationData.open(locationFile, std::ios::in);
	if (locationData.is_open()) {
		std::cout << "File has opened successfully\n";
		size_t current = 0;
		size_t next = 0;

		// hack to divide input section
		int section = 1;
		char delim = ':';
		bool start = false;
		bool end = false;

		while (std::getline(locationData, line)) {

			// add all intro text to a separate vector of strings
			while (section == 1) {
				mGame->AddIntroText(line);
				std::getline(locationData, line);
				if (!line.find("#")) {	// the '#' symbol indicates the end of the intro text
					std::getline(locationData, line);
					section = 2;
				}
			}

			if (line == "" && !locationStack.empty()) {
				mGame->AddLocation(mLocation);
				locationStack.pop();
				mLocation = new Location(mGame);
				// empty line between data
				std::getline(locationData, line);
			}

			// create new location instance
			//check if location stack is empty. If not, push location on stack to game location vector
			//pop it off the stack. Delete or clear the location. Create a new one.

			// read in location data
			if (line.size() < 1) {
				++current;
			}
			else {
				current = line.find_first_of(delim);
				temp = line.substr(0, current - 0);
				++current;
			}

			while (current < line.size()) {
				if (temp == "Coordinates") {
					if (line[current] == '*') {
						next = current + 1;
						if (line[next] == '*') {
							end = true;
							current = next;
							++current;
							//std::cout << "coordinate is end location\n";
							//current = next + 1;
							//if (isdigit(line[current])) {	// possibly 
							//	next = current + 1;
							//	if (line[next] == ',') {	// x coordinate
							//		std::cout << "End Location X: " << line[current] << "\n";
							//		mCoordX == (int)line[current];
							//		++current;
							//	}
							//	else if (line[next] == ')') {	// y coordinate
							//		std::cout << "End Location Y: " << line[current] << "\n";
							//		++current;
							//		mCoordTwoY == (int)line[current];
							//	}
							//}
							//else {	// non important character, advance
							//	++current;
							//}
						}
						else {
							start = true;
							current = next;
							++current;
							//std::cout << "coordinate is starting location\n";
							//// create a new location instance?
							//current = next;
							//if (isdigit(line[current])) {
							//	next = current + 1;
							//	if (line[next] == ',') {	// x coordinate
							//		std::cout << "Start Location X: " << line[current] << "\n";
							//		mCoordX == (int)line[current];
							//		++current;
							//	}
							//	else if (line[next] == ')') {	// y coordinate
							//		std::cout << "Start Location Y: " << line[current] << "\n";
							//		mCoordTwoY == (int)line[current];
							//		++current;
							//	}
							//}
							//else {	// non important character, advance
							//	++current;
							//}
						}
					}
					else if (isdigit(line[current])) {	// possibly 
						next = current + 1;
						if (line[next] == ',') {	// x coordinate
							std::cout << "Current X: " << line[current] << "\n";
							mCoordX = std::atoi(&line[current]);
							current = next;
							++current;
						}
						else if (line[next] == ')') {	// y coordinate
							std::cout << "Current Y: " << line[current] << "\n";
							mCoordY = std::atoi(&line[current]);
							mLocation->SetCoordinates(std::make_pair(mCoordX, mCoordY));
							locationStack.push(mLocation);
							if (start) {
								mLocation->SetStartLocation(start);
								start = false;
							}
							else if (end) {
								mLocation->SetEndLocation(end);
								end = false;
							}
							current = next;
							++current;
						}
					}
					else {	// non important character, advance
						++current;
					}
				}
				else if (temp == "Neighbor Coordinates") {
					//std::cout << "neighbor coordinates line\n";
					if (isdigit(line[current])) {	// positive numbers 
						next = current + 1;
						if (line[next] == ',') {	// x coordinate
							std::cout << "Neighbor X: " << line[current] << "\n";
							mCoordX = std::atoi(&line[current]);
							current = next;
							++current;
						}
						else if (line[next] == ')') {	// y coordinate
							std::cout << "Neighbor Y: " << line[current] << "\n";
							mCoordY = std::atoi(&line[current]);
							mLocation->AddNeighborCoordinates(std::make_pair(mCoordX, mCoordY));
							current = next;
							++current;
						}
					}
					else if (line[current] == '-') {	// negative numbers
						next = current + 1;
						if (isdigit(line[next])) {
							if (line[next + 1] == ',') {	// negative x
								std::cout << "Neighbor X: -" << line[next] << "\n";
								mCoordX = std::atoi(&line[next]);
								mCoordX *= -1;
								current = next + 1;
								++current;
							}
							if (line[next + 1] == ')') {
								std::cout << "Neighbor Y: -" << line[next] << "\n";
								mCoordY = std::atoi(&line[next]);
								mCoordY *= -1;
								mLocation->AddNeighborCoordinates(std::make_pair(mCoordX, mCoordY));
								current = next + 1;
								++current;
							}
						}
					}
					else {
						++current;
					}
				}
				else if (temp == "Location Name") {
					if (line[current] != ' ') {
						std::cout << "Current Location Name Line: " << line.substr(current, line.size()) << "\n";
						mLocation->SetLocationTitle(line.substr(current, line.size()));
						current = line.size();
					}
					else{
						++current;
					}
				}
				else if (std::stoi(temp)) {
					if (line[current] != ' ') {
						std::cout << "text: " << line.substr(current, line.size()) << "\n";
						mLocation->AddLocationText(line.substr(current, line.size()));
						current = line.size();
					}
					else {
						++current;
					}
				}
			}

			//std::cout << line << "\n";
			current = 0;
			next = 0;

		}
		// add final location
		mGame->AddLocation(mLocation);
		locationStack.pop();
		mLocation = new Location(mGame);
		locationData.close();
	}

	else {
		printf("Error: Failed to read Location Data. See FileReader::ReadLocationData function.\nTerminating Game.\n");
		exit(EXIT_FAILURE);
	}

}

//int FileReader::GetCoordOne() {
//	return coordOneX;
//}
