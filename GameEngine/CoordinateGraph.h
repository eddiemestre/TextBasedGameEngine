#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include "Location.h"


//struct hash_pair {
//	template <class T1, class T2>
//	size_t operator()(const std::pair<T1, T2>& p) const {
//		auto hash1 = std::hash<T1>{}(p.first);
//		auto hash2 = std::hash<T2>{}(p.second);
//		return hash1 ^ hash2;
//	}
//};
//
//class Location;
//
//class CoordinateGraph {
//public:
//	CoordinateGraph(int v);
//	void addEdge(std::pair<int, int> v1, std::pair<int, int> v2);
//	void DFSUtil(std::vector<Location*> locationVec);
//	void DFSUtil(std::vector<std::pair<int,int>> locationVec);
//	void DFSUtility(Location* loc);
//
//	void DSF(int v);
//
//private:
//	int mVertices;	// number of rooms in game world
//	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> *adj;	// adjacency list of all nodes
//	std::unordered_map<std::pair<int, int>, bool, hash_pair> visitedMap;	// keep track of nodes that have been visted
//	//std::unordered_map<std::pair<int, int>, bool, hash_pair> visitedMap;
//
//};
