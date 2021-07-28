//
// Created by Chase Wrenn on 7/22/21.
//

#include <vector>
#include <sstream>
#include "FlightGraph.h"

FlightGraph::FlightGraph() {

    string string1 = "1 Alaska\n"
                     "2 Hawaii\n"
                     "3 Puerto Rico\n"
                     "4 U.S. Virgin Islands\n"
                     "5 U.S. Pacific Trust Territories and Possessions\n"
                     "11 Connecticut\n"
                     "12 Maine\n"
                     "13 Massachusetts\n"
                     "14 New Hampshire\n"
                     "15 Rhode Island\n"
                     "16 Vermont\n"
                     "21 New Jersey\n"
                     "22 New York\n"
                     "23 Pennsylvania\n"
                     "31 Delaware\n"
                     "32 District of Columbia\n"
                     "33 Florida\n"
                     "34 Georgia\n"
                     "35 Maryland\n"
                     "36 North Carolina\n"
                     "37 South Carolina\n"
                     "38 Virginia\n"
                     "39 West Virginia\n"
                     "41 Illinois\n"
                     "42 Indiana\n"
                     "43 Michigan\n"
                     "44 Ohio\n"
                     "45 Wisconsin\n"
                     "51 Alabama\n"
                     "52 Kentucky\n"
                     "53 Mississippi\n"
                     "54 Tennessee\n"
                     "61 Iowa\n"
                     "62 Kansas\n"
                     "63 Minnesota\n"
                     "64 Missouri\n"
                     "65 Nebraska\n"
                     "66 North Dakota\n"
                     "67 South Dakota\n"
                     "71 Arkansas\n"
                     "72 Louisiana\n"
                     "73 Oklahoma\n"
                     "74 Texas\n"
                     "81 Arizona\n"
                     "82 Colorado\n"
                     "83 Idaho\n"
                     "84 Montana\n"
                     "85 Nevada\n"
                     "86 New Mexico\n"
                     "87 Utah\n"
                     "88 Wyoming\n"
                     "91 California\n"
                     "92 Oregon\n"
                     "93 Washington";

    std::istringstream f(string1);
    std::string line;
    while (std::getline(f, line)) {
        int index = line.find(' ');
        short AC = stoi(line.substr(0,index));
        string loc = line.substr(index+1, line.size());
        WAC.insert(make_pair(loc, AC));
    }

    string string2 = "WN Southwest Airlines Co.\n"
                     "DL Delta Air Lines Inc.\n"
                     "AA American Airlines Inc.\n"
                     "UA United Air Lines Inc.\n"
                     "B6 JetBlue Airways\n"
                     "AS Alaska Airlines Inc.\n"
                     "NK Spirit Air Lines\n"
                     "G4 Allegiant Air\n"
                     "F9 Frontier Airlines Inc.\n"
                     "HA Hawaiian Airlines Inc.\n"
                     "SY Sun Country Airlines d/b/a MN Airlines\n"
                     "VX Virgin America";

    std::istringstream g(string2);
    std::string line2;
    while (std::getline(g, line2)) {
        int index = line2.find(' ');
        string code = line2.substr(0,index);
        string name = line2.substr(index+1, line2.size());
        airlines.insert(make_pair(code, name));
    }
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

}

string FlightGraph::getLocFromAC(short AC) {
    string res = "";
    for (auto itr = WAC.begin(); itr != WAC.end() && res == ""; itr++)
    {
        if (itr->second == AC)
        {
            res = itr->first;
        }
    }
    return res;
}

short FlightGraph::getACfromLoc(string loc) {
    return WAC.find(loc)->second;
}
