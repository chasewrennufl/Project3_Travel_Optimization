//
// Created by Chase Wrenn on 7/22/21.
//

#ifndef PROJECT3_TRAVEL_OPTIMIZATION_FILEMANAGER_H
#define PROJECT3_TRAVEL_OPTIMIZATION_FILEMANAGER_H

#include "fstream"
#include "FlightGraph.h"

class FileManager
{
private:

public:

    FlightGraph* buildGraph(string fileName, short q, map<string, bool> airlines);

};

#endif //PROJECT3_TRAVEL_OPTIMIZATION_FILEMANAGER_H
