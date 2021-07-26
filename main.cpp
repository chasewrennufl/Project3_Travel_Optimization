#include <iostream>
#include "Data/FileManager.h"

using namespace std;

int main() {
	FileManager f;
	FlightGraph* flightGraph;
	//flightGraph = f.buildGraph("Cleaned_2018_Flights.csv");
	flightGraph = f.buildGraph("Test Flight Data.csv");
    cout << "For testing" << endl;
}