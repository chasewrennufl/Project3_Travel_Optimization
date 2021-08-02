#include <iostream>
#include <sstream>
#include "Data/FileManager.h"
#include "Function/BellmanFordAlgo.h"
#include "Function/DjikstrasModAlgo.h"
#include <chrono>

using namespace std;

int main() {
	FileManager f;
    FlightGraph flightGraph;
	bool incomplete = true;
	short q;
	string src;
	vector<short> dest;
	map<string, bool> airlines;
    cout << "Welcome to Travel Optimization BETA!" << endl;
	while (incomplete) {
        cout << "Please enter the quarter of the year "
            "you would like to take your trip:" << endl;
        cin >> q;
        if (q < 0 || q > 4) {
            cout << "Error! Quarter must be between 1 and 4!" << endl;
            q = 0;
        }
        else
            incomplete = false;
    }
    cout << "Please enter the source of the trip:" << endl;
    cin >> src;
    cout << "Enter Airline codes of airlines you would like to use,"
        " separated by a comma. (Ex: WN,DL):" << endl;
    cout << "WN Southwest Airlines Co.\n"
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
    string str;
    cin >> str;
    stringstream ss(str);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        airlines.insert(make_pair(substr, true));
    }
    cout << "Enter Area Codes of locations you would like to go to, "
            "separated by a comma. (Ex: 2,13):" << endl;
    cout << "1 Alaska\n"
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
    string str2;
    cin >> str2;
    stringstream ss2(str2);
    while (ss2.good()) {
        string substr;
        getline(ss2, substr, ',');
        dest.push_back(stoi(substr));
    }
	f.buildGraph("Cleaned_2018_Flights.csv", q, airlines, flightGraph);
	//f.buildGraph("Test Flight Data.csv", q, airlines, flightGraph);
    BellmanFordAlgo bellmanFordAlgo;
    DjikstrasModAlgo djikstra;
    vector<FlightEdge> route, route2;
    //route = bellmanFordAlgo.calculateRoute(&flightGraph, flightGraph.WAC[src], dest);

    auto start2 = std::chrono::high_resolution_clock::now();
    route2 = bellmanFordAlgo.calculateRoute(&flightGraph, flightGraph.WAC[src], dest);
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

    auto start = std::chrono::high_resolution_clock::now();
    route = djikstra.calculateRoute(&flightGraph, flightGraph.WAC[src], dest);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);

    cout << "Bellman Ford Output:" << endl;
    string out = flightGraph.routeText(route2);
    cout << out << endl;
    cout << "Bellman Ford Algorithm Time: " << duration2.count() << " microseconds" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "Djikstra Output:" << endl;
    string out2 = flightGraph.routeText(route);
    cout << out2 << endl;
    cout << "Dijkstra Algorithm Time: " << duration.count() << " microseconds" << endl;//
   /* for (int i = 0; i < route.size(); i++) {
        FlightEdge e = route.at(i);
        cout << flightGraph.getLocFromAC(e.originWAC) << "--->" <<
            flightGraph.getLocFromAC(e.destWAC) << "; Price: $" << e.price << "; Airline: " <<
            flightGraph.getAirlineFromCode(e.airlineCode) << endl;
    } */

    //when clicked
}