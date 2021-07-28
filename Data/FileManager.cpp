//
// Created by Chase Wrenn on 7/22/21.
//

#include <vector>
#include <sstream>
#include "FileManager.h"

FlightGraph* FileManager::buildGraph(string fileName, short q,  map<string, bool> airlines) {
    FlightGraph* fgraph = new FlightGraph();
    fstream fin;

    fin.open(fileName, ios::in);

    if(!fin.is_open()) throw std::runtime_error("Could not open file");

    short quarter, srcWAC, destWAC;
    string airlineCode;
    double price;

    vector<string> row;
    string line, temp, data;
    cout << "Loading Flight Data..." << endl;
    fin >> temp;
    while (fin >> line)
    {
        row.clear();
        stringstream s(line);

        while (getline(s, data, ','))
        {
            row.push_back(data);
        }

        FlightEdge e;
        e.quarter = stoi(row[4]);
        e.originWAC = stoi(row[6]);
        e.destWAC = stoi(row[8]);
        e.airlineCode = row[12];
        e.price = stod(row[13]);
        if (e.quarter == q && airlines.find(e.airlineCode) != airlines.end()) {
            fgraph->insertFlightEdge(e);
        }
    }
    cout << "Flight Data loaded successfully!" << endl;
    return fgraph;
}
