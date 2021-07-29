//
// Created by Chase Wrenn on 7/22/21.
//

#ifndef PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTGRAPH_H
#define PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTGRAPH_H

#include <string>
#include "FlightEdge.h"
#include <map>
#include <vector>

using namespace std;

class FlightGraph
{
private:

    map<short, vector<FlightEdge>> graph;
    int V;
    int E;


public:

    FlightGraph();

    void insertFlightEdge(FlightEdge& e);
    bool isFlight(FlightEdge& e);
    double getPrice(string src, string dest);
    vector<FlightEdge> getFlightsFromLoc(string src);
    void printGraph();

    string getAirline(string code);
    string getLocFromAC(short AC);
    short getACfromLoc(string loc);

    map<string, short> WAC;
    map<string, string> airlines;

};

#endif //PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTGRAPH_H
