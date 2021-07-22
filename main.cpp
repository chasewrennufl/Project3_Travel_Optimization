#include <iostream>
#include "Data/FileManager.h"

using namespace std;

int main() {
	FileManager f;
	f.buildGraph("Cleaned_2018_Flights.csv");
}