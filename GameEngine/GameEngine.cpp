//
// GameEngine.cpp
//
// Created by Eddie Mestre on 9/12/2020
// Copyright © 2020 Eddie Mestre. All rights reserved.
//

#include "GameEngine.h"
//#include <conio.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>



// Constructor
Game::Game()
	// initialize constants
{
	// initialize member variables
	currentNode = std::pair<int, int>(0, 0);
	previousNode = std::pair<int, int>(0, 0);
	mCompass = true;
	mValidInput = false;
	mNorthStraight = false;
	mSouthPrevious = false;
	mWestLeft = false;
	mEastRight = false;
}

// Initialize
// Returns true if game successfully intializes and false otherwise
bool Game::Initialize()
{
	// graphics, render, window, video, music load

	// call LoadData
	LoadData();

	return true;
}

// Shutdown
void Game::Shutdown()
{
	// call UnloadData
	UnloadData();
}

// RunLoop
void Game::RunLoop()
{
	// run loop
	while (runLoop) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput() {
	
	// eventual control inputs

}

void Game::UpdateGame() {
	// update time
	// update new screen
	
	// Clear direction vector
	mDirectionVector.clear();
	mValidInput = false;
	mNorthStraight = false;
	mSouthPrevious = false;
	mWestLeft = false;
	mEastRight = false;

}

void Game::GenerateOutput() {
	//// render stuff to screen or draw things

	std::pair<int, int> temp;
	bool undecided = true;
	std::string direction;

	while (undecided) {
		for (int i = 0; i < locationVector.size(); ++i) {

			if (!undecided) {
				break;
			}

			// find currentNode
			//
			// ******display text based on number of room visits. The last string in the vector is the 
			// ******default string and should you hit it, it should stay at the index for the default string
			if (locationVector[i]->GetCoordinates() == currentNode) {

				// print room name
				std::cout << locationVector[i]->GetLocationTitle() << "\n";

				// for primary and secondary... may want to revisit this...
				//if (locationVector[i]->GetPrimary() != "" && locationVector[i]->GetHasVisited() == false) {
				//	std::cout << locationVector[i]->GetPrimary() << '\n';
				//}
				//std::cout << locationVector[i]->GetSecondary() << '\n';
				//locationVector[i]->SetHasVisited(true);

				int tempNumVisits = locationVector[i]->GetNumVisits();

				// default text
				if (tempNumVisits == locationVector[i]->GetLocationText().size() - 1) {
					std::cout << locationVector[i]->GetLocationText()[locationVector[i]->GetNumVisits()] << "\n";
				}
				else {	// increase tempNumVisits and set after text is displayed
					std::cout << locationVector[i]->GetLocationText()[locationVector[i]->GetNumVisits()] << "\n";
					++tempNumVisits;
					locationVector[i]->SetNumVisits(tempNumVisits);
				}

				// reset
				tempNumVisits = 0;

				// check if player is at final room and give option to reset if they are
				if (locationVector[i]->GetIsEndLocation()) {
					// compute score

					std::cout << "Would you like to play again?\n";
					std::getline(std::cin, direction);
					
					std::for_each(direction.begin(), direction.end(), [](char &c) {
						c = ::tolower(c);
					});

					if (direction == "n" || direction == "no") {
						printf("Thanks for playing!\n");
						exit(EXIT_SUCCESS);
					}
					else {
						// reset game data

					}
				}

				// display options
				DisplayMath(locationVector[i]->GetNeighborCoordinates());

				// order options
				DirectionSort(mDirectionVector);

				for (int j = 0; j < mDirectionVector.size(); ++j) {
					std::cout << '>' << mDirectionVector[j].first << '\n';
				}

				//*****
				//*****
				//***** Switch reliance from the direction Vector to the location vector or change up how it gets the info
				//***** Right now you can have locations with neighbors that don't exist.

				if (mCompass) {
					while (!mValidInput) {
						std::getline(std::cin, direction);

						// convert string to lowercase
						std::for_each(direction.begin(), direction.end(), [](char &c) {
							c = ::tolower(c);
						});

						if (direction == "n" || direction == "north" || direction == "go north" || 
							direction == "walk north" || direction == "head north") {	// Go to Previous Node
							if (mNorthStraight) {
								for (int k = 0; k < mDirectionVector.size(); ++k) {
									if (mDirectionVector[k].first == "North") {
										temp = mDirectionVector[k].second;
										previousNode = currentNode;
										currentNode = temp;
										break;
									}
								}
								undecided = false;
								mValidInput = true;
							}
							else {
								std::cout << "Despite your desire, no path leads that way.\n";
							}
						}
						else if (direction == "s" || direction == "south" || direction == "go south" ||
							direction == "walk south" || direction == "head south") {	// Go to Right Node
							if (mSouthPrevious) {
								for (int k = 0; k < mDirectionVector.size(); ++k) {
									if (mDirectionVector[k].first == "South") {
										temp = mDirectionVector[k].second;
										previousNode = currentNode;
										currentNode = temp;
										break;
									}
								}
								undecided = false;
								mValidInput = true;
							}
							else {
								std::cout << "Despite your desire, no path leads that way.\n";
							}
						}
						else if (direction == "e" || direction == "east" || direction == "go east" ||
							direction == "walk east" || direction == "head east") {	// Go to Left Node
							if (mEastRight) {
								for (int k = 0; k < mDirectionVector.size(); ++k) {
									if (mDirectionVector[k].first == "East") {
										temp = mDirectionVector[k].second;
										previousNode = currentNode;
										currentNode = temp;
										break;
									}
								}
								undecided = false;
								mValidInput = true;

							}
							else {
								std::cout << "Despite your desire, no path leads that way.\n";
							}
						}
						else if (direction == "w" || direction == "west" || direction == "go west" ||
							direction == "walk west" || direction == "head west") {
							if (mWestLeft) {
								for (int k = 0; k < mDirectionVector.size(); ++k) {	// Go to Straight Node
									if (mDirectionVector[k].first == "West") {
										temp = mDirectionVector[k].second;
										previousNode = currentNode;
										currentNode = temp;
										break;
									}
								}
								undecided = false;
								mValidInput = true;
							}
							else {
								std::cout << "Despite your desire, no path leads that way.\n";
							}
						}
						else {
							std::cout << direction << " is not a recognizable direction.\n";
						}
					}
				}
				else {
					while (!mValidInput) {
						std::getline(std::cin, direction);

						// convert string to lowercase
						std::for_each(direction.begin(), direction.end(), [](char &c) {
							c = ::tolower(c);
						});

						if (direction == "p" || direction == "P" || direction == "previous" || direction == "Previous") {	// Go to Previous Node
							if (mSouthPrevious) {
								temp = previousNode;
								previousNode = currentNode;
								currentNode = temp;
								undecided = false;
								mValidInput = true;
							}
							else {
								std::cout << "Despite your desire, no path leads that way.\n";
							}
						}
						else if (direction == "r" || direction == "R" || direction == "right" || direction == "Right") {	// Go to Right Node
							if (mEastRight) {
								for (int k = 0; k < mDirectionVector.size(); ++k) {
									if (mDirectionVector[k].first == "Right") {
										temp = mDirectionVector[k].second;
										previousNode = currentNode;
										currentNode = temp;
										break;
									}
								}
								undecided = false;
								mValidInput = true;
							}
							else {
								std::cout << "Despite your desire, no path leads that way.\n";
							}
						}
						else if (direction == "l" || direction == "L" || direction == "left" || direction == "Left") {	// Go to Left Node
							if (mWestLeft) {
								for (int k = 0; k < mDirectionVector.size(); ++k) {
									if (mDirectionVector[k].first == "Left") {
										temp = mDirectionVector[k].second;
										previousNode = currentNode;
										currentNode = temp;
										break;
									}
								}
								undecided = false;
								mValidInput = true;
							}
							else {
								std::cout << "Despite your desire, no path leads that way.\n";
							}
						}
						else if (direction == "s" || direction == "S" || direction == "straight" || direction == "Straight") {
							if (mNorthStraight) {
								for (int k = 0; k < mDirectionVector.size(); ++k) {	// Go to Straight Node
									if (mDirectionVector[k].first == "Straight") {
										temp = mDirectionVector[k].second;
										previousNode = currentNode;
										currentNode = temp;
										break;
									}
								}
								undecided = false;
								mValidInput = true;
							}
							else {
								std::cout << "Despite your desire, no path leads that way.\n";
							}
						}
						else {
							std::cout << direction << " is not a recognizable direction.\n";
						}
					}
				}
			}
		}
	}








	//for (int i = 0; i < locationVector.size(); ++i) {
	//	std::cout << i << ": " << locationVector[i]->coordinates.first << "," << locationVector[i]->coordinates.second << "\n";
	//	if (locationVector[i]->GetPrimary() != "") {
	//		std::cout << locationVector[i]->GetPrimary() << "\n";
	//	}
	//	std::cout << locationVector[i]->GetSecondary() << '\n';
	//	for (int j = 0; j < locationVector[i]->neighborCoordinates.size(); ++j) {
	//		std::cout << "(" << locationVector[i]->neighborCoordinates[j].first << "," << locationVector[i]->neighborCoordinates[j].second << ")";
	//	}
 //		std::cout << '\n' << '\n';
	//}
}

void Game::LoadData() {
	// load any data
	// read any files
	mFileReader = new FileReader(this);
	
	// read in Location Data
	mFileReader->ReadLocationData(constants::LOCATION_DATA_FILE);
	
	// print intro text
	for (auto p : mIntroText) {
		std::cout << p << "\n";
	}

	//// pass in what is needed (locationVector, visitMap)???
	//// move utility tool to file reader????

	//Location* location1 = new Location(this);
	//Location* location2 = new Location(this);
	//Location* location3 = new Location(this);
	//Location* location4 = new Location(this);
	//Location* location5 = new Location(this);
	//Location* location6 = new Location(this);
	//
	//location1->SetCoordinates(std::pair<int, int>(2, 1));
	////*location1->SetPrimary("You awaken from a bad dream.");
	//location1->SetSecondary("You are in a small room. (2,1) ");*/
	//location1->AddNeighborCoordinates(std::pair<int, int>(1, 1));

	//location2->SetCoordinates(std::pair<int, int>(0, 1));
	////location2->SetSecondary("A large hallway. (0,1) ");
	////location2->AddNeighborCoordinates(std::pair<int, int>(0, 0));
	//location2->AddNeighborCoordinates(std::pair<int, int>(1, 1));
	////location2->AddNeighborCoordinates(std::pair<int, int>(0, 2));

	//location3->SetCoordinates(std::pair<int, int>(1, 1));
	////location3->SetSecondary("A dead end. (1,1) ");
	//location3->AddNeighborCoordinates(std::pair<int, int>(0, 1));
	//location3->AddNeighborCoordinates(std::pair<int, int>(2, 1));
	//location3->AddNeighborCoordinates(std::pair<int, int>(1, 0));
	//location3->AddNeighborCoordinates(std::pair<int, int>(1, 2));

	//location4->SetCoordinates(std::pair<int, int>(1, 0));
	////location4->SetSecondary("A small hallway. (1,0) ");
	//location4->AddNeighborCoordinates(std::pair<int, int>(1, 1));
	////location4->AddNeighborCoordinates(std::pair<int, int>(0, 3));

	//location5->SetCoordinates(std::pair<int, int>(1, 2));
	////location5->SetSecondary("There is a gate ahead. (1,2) ");
	//location5->AddNeighborCoordinates(std::pair<int, int>(1, 1));

	//location6->SetCoordinates(std::pair<int, int>(4, 5));

	//location1->AddNeighbors(location3);

	//location2->AddNeighbors(location3);

	//location3->AddNeighbors(location2);
	//location3->AddNeighbors(location1);
	//location3->AddNeighbors(location4);
	//location3->AddNeighbors(location5);

	//location4->AddNeighbors(location3);

	//location5->AddNeighbors(location3);

	//this->AddLocation(location1);
	//this->AddLocation(location2);
	//this->AddLocation(location3);
	//this->AddLocation(location4);
	//this->AddLocation(location5);
	//this->AddLocation(location6);

	// location connection test
	//std::cout << "testing connection starting at " << location5->GetCoordinates().first << "," << location5->GetCoordinates().second << "\n";
	
	// DFS test
	//std::cout << "testing connection starting at " << location5->GetCoordinates().first << "," << location5->GetCoordinates().second << "\n";
	//****************
	//****************
	//****************loop through locations to get start and end locations. If there are multiple start
	// or end locations (or none at all) throw error. There should be exactly one each. if not, do DFSUtility 
	// and check visitedMap (done below)

	// add neighbor locations to each location's neighbor location vector
	LocationConnector(locationVector);

	// check if neighborCoordinates are all accounted for in locationVector. If not, throw game terminating error


	// Set start and end locations
	SetStartIndex(locationVector);
	SetEndIndex(locationVector);


	// DFS test
	std::cout << "testing connection starting at (" << locationVector[mStartIndex]->GetCoordinates().first 
		<< "," << locationVector[mStartIndex]->GetCoordinates().second << ") ...\n\n";


	// recursion to check location connection
	DFSUtility(locationVector[mStartIndex]);

	std::vector<std::pair<int, int>> extraNeighborCoordinates;
	std::vector<std::pair<int, int>> copyNeighbor;
	// we know all locations in locationVector were created with real location coordinates. We know all locations in the getNeighbors()
	// vector are also real. Need to compare the coordinate pairs of the NeighCoordinates function to each location in the getNeighbors()
	// vector for each location. If there are extra mNeighborCoordinates then we should alert the dev but not break the game. 
	for (int i = 0; i < locationVector.size(); ++i) {
		copyNeighbor = locationVector[i]->GetConnectedNeighborCoordinates();
		for (int j = 0; j < locationVector[i]->GetNeighborCoordinates().size(); ++j) {
			if (std::find(copyNeighbor.begin(),
				copyNeighbor.end(), locationVector[i]->GetNeighborCoordinates()[j])
				!= copyNeighbor.end()) {
			}
			else {
				std::cout << "Error: Location (" << locationVector[i]->GetCoordinates().first << "," << locationVector[i]->GetCoordinates().second
					<< ") has unlinked Neighbor Coordinate ==> (" << locationVector[i]->GetNeighborCoordinates()[j].first << ","
					<< locationVector[i]->GetNeighborCoordinates()[j].second << ")\n";
				extraNeighborCoordinates.push_back({ locationVector[i]->GetNeighborCoordinates()[j].first, locationVector[i]->GetNeighborCoordinates()[j].second });
			}
		}
	}
	
	//	results
	if (visitedMap[{locationVector[mEndIndex]->GetCoordinates().first, locationVector[mEndIndex]->GetCoordinates().second}]) {
		std::cout << "\n\n*****graph is connected*****\n\n";
		currentNode = std::make_pair(locationVector[mStartIndex]->GetCoordinates().first, locationVector[mStartIndex]->GetCoordinates().second);
	}
	else {
		char c;
		bool quit = false;
		while (!quit) {
			printf("Error: Graph is not connected\n\nShow visited locations? (y\\n)\n");
			std::cin >> c;
			c = ::tolower(c);
			if (c == 'y') {
				// print map results
				std::cout << "visitedMap resutlts: \n";
				for (auto m : visitedMap) {
					std::cout << "(" << (m.first).first << "," << (m.first).second
						<< ") ==> " << m.second << "\n";
				}
				std::cout << "List of all locations:\n";
				for (auto p : locationVector) {
					std::cout << "(" << p->GetCoordinates().first << ","
						<< p->GetCoordinates().second << ")\n";
				}
				quit = false;
			}
			else {
				printf("Game terminated. Failure to connect locations. See GameEngine.cpp Game::LoadData()\n");
				//quit = true;
				exit (EXIT_FAILURE);
			}
		}
	}

	// check to see if there are unused locations
	if (!extraNeighborCoordinates.empty()) {
		printf("Error: Unused Neighbor Locations in file. See above. Check location data file and remove unused Neighbor Coordinates.\n\n");
		exit(EXIT_FAILURE);
	}

}

void Game::UnloadData() {
	// delete or close data
}

void Game::AddLocation(Location* location) {
	locationVector.push_back(location);
}

void Game::RemoveLocation(Location* location) {
	if (std::find(locationVector.begin(), locationVector.end(), location) != locationVector.end()) {
		locationVector.erase(std::find(locationVector.begin(), locationVector.end(), location));
	}
}

std::vector<std::pair<std::string, std::pair<int, int>>> Game::DisplayMath(std::vector<std::pair<int, int>> const &locations)
{
	// create new copy vector
	std::vector<std::pair<int, int>> copy;

	for (int i = 0; i < locations.size(); ++i) {
		copy.push_back(locations[i]);
	}
	while (!copy.empty()) {


		if (mCompass) {	// compass directions
			if (!copy.empty() && currentNode.first - copy[0].first == -1) {	// North
				mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("North", (copy[0])));
				copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
			}
			if (!copy.empty() && currentNode.first - copy[0].first == 1) {	// South
				mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("South", (copy[0])));
				copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
			}
			if (!copy.empty() && currentNode.second - copy[0].second == -1) {	// South
				mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("East", (copy[0])));
				copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
			}
			if (!copy.empty() && currentNode.second - copy[0].second == 1) {	// South
				mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("West", (copy[0])));
				copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
			}
		}
		else {
			if (currentNode.first - previousNode.first == 0) {	// moved straight or possibly previous (horizontally on grid)
				//printf("Moved horizontally.");
				if (currentNode.second - previousNode.second == 1) {	// moved straight (Horizontal Right on grid)
					// is previous in here yet?
					if (std::find(mDirectionVector.begin(), mDirectionVector.end(), std::pair<std::string, std::pair<int, int>>("Previous", previousNode)) != mDirectionVector.end()) {
						// it is in here so skip
					}
					else {
						mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Previous", (previousNode)));
						copy.erase(std::find(copy.begin(), copy.end(), previousNode));
					}
					if (!copy.empty() && currentNode.first - copy[0].first == -1) {	// Left (up on grid)
						mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Left", (copy[0])));
						copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
					}
					else if (!copy.empty() && currentNode.first - copy[0].first == 1) {	// Right (down on grid)
						mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Right", (copy[0])));
						copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
					}
					else if (!copy.empty()) {	// Straight (left on grid)
						mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Straight", (copy[0])));
						copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
					}
				}
				else {	// moved straight (Horizontal Left on grid)
					if (std::find(mDirectionVector.begin(), mDirectionVector.end(), std::pair<std::string, std::pair<int, int>>("Previous", previousNode)) != mDirectionVector.end()) {
						// it is in here so skip
					}
					else {
						mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Previous", (previousNode)));
						copy.erase(std::find(copy.begin(), copy.end(), previousNode));
					}
					if (!copy.empty() && currentNode.first - copy[0].first == -1) {	// Right (up on grid)
						mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Right", (copy[0])));
						copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
					}
					else if (!copy.empty() && currentNode.first - copy[0].first == 1) {	// Left (down on grid)
						mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Left", (copy[0])));
						copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
					}
					else if (!copy.empty()) {	// Straight (left on grid)
						mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Straight", (copy[0])));
						copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
					}
				}
			}
			else if (currentNode.first - previousNode.first == -1) {	// moved down vertically on grid view
				//printf("Moved down vertically.\n");
				if (std::find(copy.begin(), copy.end(), previousNode) != copy.end()) {
					mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Previous", (previousNode)));
					copy.erase(std::find(copy.begin(), copy.end(), previousNode));
				}
				if (!copy.empty() && currentNode.first - copy[0].first == 1) {			// Straight (down on grid)
					mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Straight", (copy[0])));
					copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
				}
				if (!copy.empty() && currentNode.second - copy[0].second == -1) {		// Left (right on grid)
					mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Left", (copy[0])));
					copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
				}
				if (!copy.empty() && currentNode.second - copy[0].second == 1) {			// Right (left on grid)
					mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Right", (copy[0])));
					copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
				}


				//std::cout << "copy" << '\n';
				//for (int i = 0; i < copy.size(); ++i) {
				//	std::cout << copy[i].first << ',' << copy[i].second << '\n';
				//}



			}
			else {	// moved up vertically +1
				//printf("Moved up vertically.");
				if (std::find(copy.begin(), copy.end(), previousNode) != copy.end()) {
					mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Previous", (previousNode)));
					copy.erase(std::find(copy.begin(), copy.end(), previousNode));
				}
				if (!copy.empty() && currentNode.first - copy[0].first == -1) {			// Straight (up on grid)
					mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Straight", (copy[0])));
					copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
				}
				if (!copy.empty() && currentNode.second - copy[0].second == 1) {		// Left (right on grid)
					mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Left", (copy[0])));
					copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
				}
				if (!copy.empty() && currentNode.second - copy[0].second == -1) {			// Right (left on grid)
					mDirectionVector.push_back(std::pair<std::string, std::pair<int, int>>("Right", (copy[0])));
					copy.erase(std::find(copy.begin(), copy.end(), copy[0]));
				}
			}
		}
	}

	return mDirectionVector;

}

void Game::DirectionSort(std::vector<std::pair<std::string, std::pair<int, int>>> &locations)
{
	// temp variables
	std::pair<std::string, std::pair<int, int>> tempNoSt;
	std::pair<std::string, std::pair<int, int>> tempSoPr;
	std::pair<std::string, std::pair<int, int>> tempEaRi;
	std::pair<std::string, std::pair<int, int>> tempWeLe;

	if (mCompass) {

		while (!locations.empty()) {
			if (locations[0].first == "North") {
				tempNoSt = std::pair<std::string, std::pair<int, int>>(locations[0].first, locations[0].second);
				locations.erase(std::find(locations.begin(), locations.end(), locations[0]));
				mNorthStraight = true;
			}
			if (!locations.empty() && locations[0].first == "South") {
				tempSoPr = std::pair<std::string, std::pair<int, int>>(locations[0].first, locations[0].second);
				locations.erase(std::find(locations.begin(), locations.end(), locations[0]));
				mSouthPrevious = true;
			}
			if (!locations.empty() && locations[0].first == "East") {
				tempEaRi = std::pair<std::string, std::pair<int, int>>(locations[0].first, locations[0].second);
				locations.erase(std::find(locations.begin(), locations.end(), locations[0]));
				mEastRight = true;
			}
			if (!locations.empty() && locations[0].first == "West") {
				tempWeLe = std::pair<std::string, std::pair<int, int>>(locations[0].first, locations[0].second);
				locations.erase(std::find(locations.begin(), locations.end(), locations[0]));
				mWestLeft = true;
			}
		}

		if (locations.empty()) {
			if (tempNoSt.first == "North") {
				mDirectionVector.push_back(tempNoSt);

			}
			if (tempSoPr.first == "South") {
				mDirectionVector.push_back(tempSoPr);

			}
			if (tempEaRi.first == "East") {
				mDirectionVector.push_back(tempEaRi);
			}
			if (tempWeLe.first == "West") {
				mDirectionVector.push_back(tempWeLe);
			}
		}
		else {
			printf("Location vector wasn't empty. See GameEngine.cpp DirectionSort function.");
			exit (EXIT_FAILURE);
		}
	}
	else {
		while (!locations.empty()) {
			if (locations[0].first == "Straight") {
				tempNoSt = std::pair<std::string, std::pair<int, int>>(locations[0].first, locations[0].second);
				locations.erase(std::find(locations.begin(), locations.end(), locations[0]));
				mNorthStraight = true;
			}
			if (!locations.empty() && locations[0].first == "Left") {
				tempWeLe = std::pair<std::string, std::pair<int, int>>(locations[0].first, locations[0].second);
				locations.erase(std::find(locations.begin(), locations.end(), locations[0]));
				mWestLeft = true;
			}
			if (!locations.empty() && locations[0].first == "Right") {
				tempEaRi = std::pair<std::string, std::pair<int, int>>(locations[0].first, locations[0].second);
				locations.erase(std::find(locations.begin(), locations.end(), locations[0]));
				mEastRight = true;
			}
			if (!locations.empty() && locations[0].first == "Previous") {
				tempSoPr = std::pair<std::string, std::pair<int, int>>(locations[0].first, locations[0].second);
				locations.erase(std::find(locations.begin(), locations.end(), locations[0]));
				mSouthPrevious = true;
			}
		}

		if (locations.empty()) {
			if (tempNoSt.first == "Straight") {
				mDirectionVector.push_back(tempNoSt);

			}
			if (tempWeLe.first == "Left") {
				mDirectionVector.push_back(tempWeLe);

			}
			if (tempEaRi.first == "Right") {
				mDirectionVector.push_back(tempEaRi);
			}
			if (tempSoPr.first == "Previous") {
				mDirectionVector.push_back(tempSoPr);
			}
		}
		else {
			printf("Error: Location vector wasn't empty. See GameEngine.cpp DirectionSort function.");
			exit (EXIT_FAILURE);
		}
	}
}

void Game::DFSUtility(const Location * loc)
{
	// set current location to true in Map
	visitedMap[{ loc->GetCoordinates().first, loc->GetCoordinates().second }] = true;
	
	// print for debugging
	//std::cout << loc->GetCoordinates().first << "," << loc->GetCoordinates().second << "\n";

	// loop through location's neighbor vector and perform recursive DFSUtility
	for (int i = 0; i < loc->getNeighbors().size(); ++i) {
		if (!visitedMap[{loc->getNeighbors()[i]->GetCoordinates().first, loc->getNeighbors()[i]->GetCoordinates().second}]) {
			DFSUtility(loc->getNeighbors()[i]);
		}
	}
}

void Game::AddIntroText(std::string &introtext)
{
	mIntroText.push_back(introtext);
}

void Game::LocationConnector(std::vector<Location*> locations)
{
	for (int i = 0; i < locations.size(); ++i) {
		for (int j = 0; j < locations[i]->GetNeighborCoordinates().size(); ++j) {
			for (int k = 0; k < locations.size(); ++k) {
				if (locations[i]->GetNeighborCoordinates()[j] == locations[k]->GetCoordinates()) {
					locations[i]->AddNeighbors(locations[k]);
				}
			}
		}
	}
}

void Game::SetStartIndex(const std::vector<Location*>& locations)
{
	for (int i = 0; i < locations.size(); ++i) {
		if (locations[i]->GetIsStartLocation()) {
			mStartIndex = i;
			break;
		}
	}
}

void Game::SetEndIndex(const std::vector<Location*>& locations)
{
	for (int i = 0; i < locations.size(); ++i) {
		if (locations[i]->GetIsEndLocation()) {
			mEndIndex = i;
			break;
		}
	}
}


