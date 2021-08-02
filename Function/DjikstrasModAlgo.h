//
// Created by Chase Wrenn on 7/27/21.
//

#ifndef PROJECT3_TRAVEL_OPTIMIZATION_DJIKSTRASMODALGO_H
#define PROJECT3_TRAVEL_OPTIMIZATION_DJIKSTRASMODALGO_H
#include <vector>
//#include "FlightGraph.h" - need to rearrange paths
#include "../Data/FlightGraph.h" //- need to rearrange paths


class DjikstrasModAlgo {

public:

	//DjikstrasModAlgo();

	//void findShortestPaths(FlightGraph& graph, )
	vector<FlightEdge> findShortestPaths(FlightGraph& graph, short origin, vector<short> dests);
};


#endif //PROJECT3_TRAVEL_OPTIMIZATION_DJIKSTRASMODALGO_H
