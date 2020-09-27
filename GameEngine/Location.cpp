#include "Location.h"

Location::Location(class Game* game)
	: mGame(game)
	, mCoordinates(std::make_pair(0,0))
	, mPrimaryText("")
	, mSecondaryText("")
	, mHasVisited(false)
	, previousCoordinates(NULL, NULL)
	, mIsStartLocation(false)
	, mIsEndLocation(false)
	, mNumVisits(0)

{
	mLocationText;
}

Location::~Location()
{
	mGame->RemoveLocation(this);
}

void Location::SetCoordinates(std::pair<int, int> pair)
{
	mCoordinates.first = pair.first;
	mCoordinates.second = pair.second;
}

void Location::SetPreviousCoordinates(std::pair<int, int> pair)
{
	pair.first = previousCoordinates.first;
	pair.second = previousCoordinates.second;
}

void Location::SetLocationTitle(std::string locationTitle)
{
	mLocationTitle = locationTitle;
}

void Location::SetHasVisited(bool value)
{
	mHasVisited = value;
}

//void Location::SetPrimary(std::string primary)
//{
//	mPrimaryText = primary;
//}
//
//void Location::SetSecondary(std::string secondary)
//{
//	mSecondaryText = secondary;
//}

void Location::AddNeighborCoordinates(std::pair<int, int> coordinates)
{
	mNeighborCoordinates.emplace_back(coordinates);
}

void Location::AddNeighbors(Location * location)
{
	this->neighbors.push_back(location);
}

void Location::SetStartLocation(bool start)
{
	mIsStartLocation = start;
}

void Location::SetEndLocation(bool end)
{
	mIsEndLocation = end;
}

void Location::AddLocationText(std::string text)
{
	mLocationText.push_back(text);
}

void Location::SetNumVisits(int v)
{
	mNumVisits = v;
}

std::pair<int, int> Location::GetCoordinates() const
{
	return mCoordinates;
}

bool Location::GetHasVisited() const
{
	return mHasVisited;
}

std::pair<int, int> Location::GetPreviousCoordinates() const
{
	return previousCoordinates;
}

std::string Location::GetPrimary() const
{
	return mPrimaryText;
}

std::string Location::GetSecondary() const
{
	return mSecondaryText;
}

std::vector<std::pair<int, int>> Location::GetNeighborCoordinates() const
{
	return mNeighborCoordinates;
}

std::vector<std::pair<int, int>> Location::GetConnectedNeighborCoordinates()
{
	std::vector<std::pair<int, int>> temp;

	for (auto m : neighbors) {
		temp.push_back(m->GetCoordinates());
	}
	return temp;
}

// test
std::vector<Location*> Location::getNeighbors() const
{
	return neighbors;
}

std::vector<std::string> Location::GetLocationText()
{
	return mLocationText;
}

std::string Location::GetLocationTitle()
{
	return mLocationTitle;
}

bool Location::GetIsStartLocation()
{
	return mIsStartLocation;
}

bool Location::GetIsEndLocation()
{
	return mIsEndLocation;
}

int Location::GetNumVisits()
{
	return mNumVisits;
}
