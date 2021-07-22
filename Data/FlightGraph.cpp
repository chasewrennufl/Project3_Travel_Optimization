//
// Created by Chase Wrenn on 7/22/21.
//

#include <vector>
#include "FlightGraph.h"

FlightGraph::FlightGraph() {

}

FlightGraph::FlightGraph(int V) {

}

void FlightGraph::insertFlightEdge(FlightEdge &e)
{
    if (graph.find(e.originWAC) == graph.end()) {
        graph[e.originWAC] = {};
        V++;
    }
    if (graph.find(e.destWAC) == graph.end()) {
        graph[e.destWAC] = {};
        V++;

    }
    graph[e.originWAC].push_back(e);
    E++;

}

bool FlightGraph::isFlight(FlightEdge &e) {
    return false;
}

double FlightGraph::getPrice(string src, string dest) {
    return 0;
}

vector<FlightEdge> FlightGraph::getFlightsFromLoc(string src) {
    vector<FlightEdge> flights;
    return flights;
}

void FlightGraph::printGraph() {

}

string FlightGraph::getAirline(string code) {
    return std::string();
}

string FlightGraph::getDest(short AC) {
    return std::string();
}
