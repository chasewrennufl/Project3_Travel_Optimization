//
// Created by Chase Wrenn on 7/22/21.
//

#ifndef PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTGRAPH_H
#define PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTGRAPH_H

#include <string>
#include "FlightEdge.h"
#include <map>

using namespace std;

class FlightGraph
{
private:

    map<short, vector<FlightEdge>> graph;
    int V;
    int E;

public:

    FlightGraph();
    FlightGraph(int V);

    void insertFlightEdge(FlightEdge& e);
    bool isFlight(FlightEdge& e);
    double getPrice(string src, string dest);
    vector<FlightEdge> getFlightsFromLoc(string src);
    void printGraph();

    string getAirline(string code);
    string getDest(short AC);

};

#endif //PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTGRAPH_H
