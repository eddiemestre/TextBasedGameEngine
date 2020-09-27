//#include "CoordinateGraph.h"
//
//CoordinateGraph::CoordinateGraph(int v)
//{
//	this->mVertices = v;
//	adj = new std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>[mVertices];
//}
//
//void CoordinateGraph::addEdge(std::pair<int, int> v1, std::pair<int, int> v2)
//{
//	adj->push_back(std::make_pair(v1, v2));
//}
//
////void CoordinateGraph::DFSUtil(std::vector<std::pair<int, int>> locationVec)
////{
////	for (int i = 0; i < locationVec.size(); ++i) {
////		if (visitedMap.find({ locationVec[i].first, locationVec[i].second }) == visitedMap.end()) {
////			visitedMap[{ locationVec[i].first, locationVec[i].second }] = true;
////
////			// either check out how to bucket and link and handle collisions or create a vector of pair vector pairs
////			std::vector<std::pair<int, int>>::iterator j;
////			//for (j = locatio)
////		}
////	}
////}
//
//// test
//void CoordinateGraph::DFSUtil(std::vector<Location*> locationVec) {
//
//	for (int i = 0; i < locationVec.size(); ++i) {
//		//std::pair<int, int> temp(locationVec[i]->GetCoordinates().first, locationVec[i]->GetCoordinates().second);
//		if (visitedMap.find({ locationVec[i]->GetCoordinates().first, locationVec[i]->GetCoordinates().second }) == visitedMap.end()) {
//			visitedMap[{ locationVec[i]->GetCoordinates().first, locationVec[i]->GetCoordinates().second }] = true;
//
//			// recur for all vertices adjacent to this vertex
//			//std::vector<Location*>::iterator j;
//			//for (j = locationVec[i]->getNeighbors().begin(); j != locationVec[i]->getNeighbors().end();  ++j) {
//			for (int j = 0; j < locationVec[i]->getNeighbors().size(); ++ j) {
//				Location* temp = locationVec[i]->getNeighbors()[j];
//				if (visitedMap.find({ temp->GetCoordinates().first, temp->GetCoordinates().second }) == visitedMap.end()) {
//					DFSUtil(locationVec[i]->GetNeighborCoordinates());
//				}
//			}
//
//		}
//
//
//	}
//
//
//	//// look into pointers and memory allocation
//	//for (int i = 0; i < locationVector.size(); ++i) {
//	//	std::pair<int, int> temp(locationVector[i]->GetCoordinates().first, locationVector[i]->GetCoordinates().second);
//	//	if (visitedMap.find(temp) == visitedMap.end()) {
//	//		visitedMap[temp] = false;
//	//	}
//	//}
//
//	//loop through adjacency list
//	for (int i = 0; i < adj->size(); ++i) {
//		//if (mVisited->find())
//	}
//}
//
//void CoordinateGraph::DFSUtility(Location * loc)
//{
//	visitedMap[{ loc->GetCoordinates().first, loc->GetCoordinates().second }] = true;
//	std::cout << loc->GetCoordinates().first << "," << loc->GetCoordinates().second << "\n";
//
//	//std::vector<Location*>::iterator i;
//	for (int i = 0; i < loc->getNeighbors().size(); ++i) {
//		if (!visitedMap[{loc->getNeighbors()[i]->GetCoordinates().first, loc->getNeighbors()[i]->GetCoordinates().second}]) {
//			DFSUtility(loc->getNeighbors()[i]);
//		}
//	}
//
//
//}
//	
