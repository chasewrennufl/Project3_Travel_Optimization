// Project3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include "FileManager.h"
#include "FlightEdge.h"
#include "FlightGraph.h"
#include "BellmanFordAlgo.h"
#include "DjikstrasModAlgo.h"
using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//load data
void readData(map <string, string>& airLineData, map <string, int>& locationData)
{
	//read airline data
	string filePathAirlines = "airlines.txt";
	string lineFromFile;
	ifstream myFile(filePathAirlines);
	while (getline(myFile, lineFromFile))
	{
		istringstream stream(lineFromFile);
		string ID;
		string name;
		getline(stream, ID, ',');
		getline(stream, name, ',');
		if (ID != "")
		{
			airLineData[name] = ID;
		}
	}
	myFile.close();

	//read locaiton data
	string filePathLocations = "locations.txt";
	ifstream myFile2(filePathLocations);
	while (getline(myFile2, lineFromFile))
	{
		istringstream stream(lineFromFile);
		string number;
		string name;
		int numFinal;
		getline(stream, number, ' ');
		getline(stream, name);
		if (number != "")
		{
			numFinal = stoi(number);
			locationData[name] = numFinal;
		}
	}
	myFile2.close();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//drawing functions

void loadWidgets(tgui::GuiBase& gui, vector <tgui::Button::Ptr>& startingPointButtons, vector <tgui::Button::Ptr>& destinationButtons, vector <tgui::Button::Ptr>& airlineButtons,
	vector <tgui::Button::Ptr>& quarterButtons, tgui::Button::Ptr& computeButton, map<string, string>& airlineData, map <string, int>& locationData, string* startPointPointer, set<string>* destinationsPointer,
	string* airLinePointer, string* quarterPointer)
{
	tgui::Theme::setDefault("C:/APIs/TGUI-0.9/themes/BabyBlue.txt");
	//tgui::Theme blackTheme{ "C:/APIs/TGUI-0.9/themes/Black.txt" };

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create Starting point scrollbar
	//create label
	auto startLocationLabel = tgui::Label::create();
	startLocationLabel->setText("Starting Point");
	startLocationLabel->setPosition(50, 25);
	startLocationLabel->setTextSize(18);
	gui.add(startLocationLabel);

	//create scrollbar
	auto startLocationPanel = tgui::ScrollablePanel::create();
	startLocationPanel->setPosition(50, 50);
	startLocationPanel->setSize(250, 250);
	gui.add(startLocationPanel);

	// Create locations
	auto iter1 = locationData.begin();
	int i1 = 0;
	for (iter1; iter1 != locationData.end(); iter1++)
	{
		tgui::Button::Ptr button = tgui::Button::create();
		button->setText(iter1->first);
		button->setSize(250, 25);
		button->setPosition(0, i1 * 25);
		startingPointButtons.push_back(button);
		startLocationPanel->add(button);
		i1++;
	}
	startLocationPanel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create Destinations scrollbar

	//create label
	auto destinationLabel = tgui::Label::create();
	destinationLabel->setText("Destinations");
	destinationLabel->setPosition(350, 25);
	destinationLabel->setTextSize(18);
	gui.add(destinationLabel);

	//create scrollbar
	auto destinationPanel = tgui::ScrollablePanel::create();
	destinationPanel->setPosition(350, 50);
	destinationPanel->setSize(250, 250);
	gui.add(destinationPanel);

	// Create locations
	auto iter2 = locationData.begin();
	int i2 = 0;
	for (iter2; iter2 != locationData.end(); iter2++)
	{
		tgui::Button::Ptr button = tgui::Button::create();
		button->setText(iter2->first);
		button->setSize(250, 25);
		button->setPosition(0, i2 * 25);
		destinationButtons.push_back(button);
		destinationPanel->add(button);
		i2++;
	}
	destinationPanel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create Airlines scrollbar

	//create label
	auto airinesLabel = tgui::Label::create();
	airinesLabel->setText("Airlines");
	airinesLabel->setPosition(50, 325);
	airinesLabel->setTextSize(18);
	gui.add(airinesLabel);

	//create scrollbar
	auto airinesPanel = tgui::ScrollablePanel::create();
	airinesPanel->setPosition(50, 350);
	airinesPanel->setSize(250, 250);
	gui.add(airinesPanel);

	// Create airlines
	auto iter3 = airlineData.begin();
	int i3 = 0;
	for (iter3; iter3 != airlineData.end(); iter3++)
	{
		tgui::Button::Ptr button = tgui::Button::create();
		button->setText(iter3->first);
		//cout << iter3->first << endl;
		button->setSize(250, 25);
		button->setPosition(0, i3 * 25);
		airlineButtons.push_back(button);
		airinesPanel->add(button);
		i3++;
	}
	airinesPanel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create Quarters scrollbar

	//create label
	auto quartersLabel = tgui::Label::create();
	quartersLabel->setText("Quarter");
	quartersLabel->setPosition(350, 325);
	quartersLabel->setTextSize(18);
	gui.add(quartersLabel);

	//create scrollbar
	auto quartersPanel = tgui::ScrollablePanel::create();
	quartersPanel->setPosition(350, 350);
	quartersPanel->setSize(250, 250);
	gui.add(quartersPanel);

	// Create Quarters
	for (unsigned int i = 1; i < 5; ++i)
	{
		tgui::Button::Ptr button = tgui::Button::create();
		button->setText(to_string(i));
		button->setSize(250, 25);
		button->setPosition(0, (i - 1) * 25);
		quarterButtons.push_back(button);
		quartersPanel->add(button);
	}
	quartersPanel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//create calculate button
	tgui::Button::Ptr button = tgui::Button::create();
	button->setSize(250, 50);
	button->setPosition(650, 275);
	button->setText("Compute");
	computeButton = button;
	gui.add(button);
}

void createInput(tgui::GuiBase& gui, string* startPointPointer, set<string>* destinationsPointer, string* airLinePointer, string* quarterPointer)
{
	//Create input window

	//create label
	auto inputLabel = tgui::Label::create();
	inputLabel->setText("Input");
	inputLabel->setPosition(650, 25);
	inputLabel->setTextSize(18);
	gui.add(inputLabel);

	auto listBox1 = tgui::ListBox::create();
	listBox1->setSize(250, 200);
	listBox1->setPosition(650, 50);
	listBox1->setItemHeight(25);
	listBox1->addItem("Starting Point: " + *startPointPointer);
	listBox1->addItem("Airline: " + *airLinePointer);
	listBox1->addItem("Quarter: " + *quarterPointer);
	if (destinationsPointer->begin() == destinationsPointer->end())
	{
		listBox1->addItem("Destinations: ");
	}
	else
	{
		listBox1->addItem("Destinations: " + *destinationsPointer->begin());
		auto iter = destinationsPointer->begin();
		iter++;
		for (iter; iter != destinationsPointer->end(); iter++)
		{
			listBox1->addItem("                      " + *iter);
		}
	}

	gui.add(listBox1);
}

void createOutput(tgui::GuiBase& gui, string* startPointPointer, set<string>* destinationsPointer, string* airLinePointer, string* quarterPointer, string* outputPointer)
{
	//Create input window

	//create label
	auto outputLabel = tgui::Label::create();
	outputLabel->setText("Output");
	outputLabel->setPosition(650, 325);
	outputLabel->setTextSize(18);
	gui.add(outputLabel);

	auto listBox2 = tgui::ListBox::create();
	listBox2->setSize(250, 250);
	listBox2->setPosition(650, 350);
	listBox2->setItemHeight(25);
	listBox2->addItem(*outputPointer);

	gui.add(listBox2);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//Actual computations
/*
void computeDjikstra()
{
}

void computeBellmanFord()
{
}
*/

string compute(string* startPointPointer, set<string>* destinationsPointer, string* airlinePointer, string* quarterPointer)
{
	FileManager f;
	FlightGraph flightGraph;
	short q = stoi(*quarterPointer);
	string src = *startPointPointer;
	vector<short> dest;
	map<string, bool> airlines;
	airlines[*airlinePointer] = true;
	for (auto it = destinationsPointer->begin(); it != destinationsPointer->end(); ++it)
	{
		dest.push_back(stoi(*it));
	}
	f.buildGraph("Cleaned_2018_Flights.csv", q, airlines, flightGraph);
	BellmanFordAlgo bellmanFordAlgo;
	DjikstrasModAlgo djikstra;
	vector<FlightEdge> route, route2;

	auto start = std::chrono::high_resolution_clock::now();
	route = djikstra.findShortestPaths(flightGraph, flightGraph.WAC[src], dest);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);

	auto start2 = std::chrono::high_resolution_clock::now();
	route2 = bellmanFordAlgo.calculateRoute(&flightGraph, flightGraph.WAC[src], dest);
	auto stop2 = std::chrono::high_resolution_clock::now();
	auto duration2 = chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

	string output = "Bellman Ford Algorithm Time: " + to_string(duration2.count());
	output = output + " microseconds\nDijkstra Algorithm Time: ";
	output = output + to_string(duration.count()) + " microseconds\n";
	output += flightGraph.routeText(route2);
	return output;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//button pressed functions

void startingPointPressed(tgui::GuiBase* gui, string* startPointPointer, set<string>* destinationsPointer, string* airLinePointer, string* quarterPointer, tgui::String buttonText)
{
	std::string strUtf8(buttonText);
	*startPointPointer = strUtf8;
	createInput(*gui, startPointPointer, destinationsPointer, airLinePointer, quarterPointer);
	//cout << *startPointPointer;
}

void destinationPressed(tgui::GuiBase* gui, string* startPointPointer, set<string>* destinationsPointer, string* airLinePointer, string* quarterPointer, tgui::String buttonText)
{
	std::string strUtf8(buttonText);
	set <string> tmp = *destinationsPointer;
	if (destinationsPointer->find(strUtf8) == destinationsPointer->end())
	{
		destinationsPointer->insert(strUtf8);
	}
	else
	{
		destinationsPointer->erase(strUtf8);
	}
	createInput(*gui, startPointPointer, destinationsPointer, airLinePointer, quarterPointer);
	//auto iter = destinationsPointer->begin();
	//for (iter; iter != destinationsPointer->end(); iter++)
	//{
	//    cout << *iter;
	//}
	//cout << endl;
}

void airlinePressed(tgui::GuiBase* gui, string* startPointPointer, set<string>* destinationsPointer, string* airLinePointer, string* quarterPointer, tgui::String buttonText)
{
	std::string strUtf8(buttonText);
	*airLinePointer = strUtf8;
	createInput(*gui, startPointPointer, destinationsPointer, airLinePointer, quarterPointer);
	//cout << *airLinePointer;
}

void quarterPressed(tgui::GuiBase* gui, string* startPointPointer, set<string>* destinationsPointer, string* airLinePointer, string* quarterPointer, tgui::String buttonText)
{
	std::string strUtf8(buttonText);
	*quarterPointer = strUtf8;
	createInput(*gui, startPointPointer, destinationsPointer, airLinePointer, quarterPointer);
	//cout << *quarterPointer;
}

void computePressed(tgui::GuiBase* gui, string* startPointPointer, set<string>* destinationsPointer, string* airLinePointer, string* quarterPointer, string* outputPointer)
{
	string output = compute(startPointPointer, destinationsPointer, airLinePointer, quarterPointer);
	*outputPointer = output;   //"test2 line 1 \ntest2 line 2"; //for testing, remove once you actually compute the output
	createOutput(*gui, startPointPointer, destinationsPointer, airLinePointer, quarterPointer, outputPointer); //prints output. Do this after storing the output in *outputPointer, don't change this method

	//clear all data
	*startPointPointer = "";
	destinationsPointer->clear();
	*airLinePointer = "";
	*quarterPointer = "";
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

bool runCode(tgui::GuiBase& gui, vector <tgui::Button::Ptr>& startingPointButtons, vector <tgui::Button::Ptr>& destinationButtons, vector <tgui::Button::Ptr>& airlineButtons, vector <tgui::Button::Ptr>& quarterButtons,
	tgui::Button::Ptr& computeButton, map<string, string>& airlineData, map <string, int>& locationData, string* startPointPointer, set<string>* destinationsPointer, string* airLinePointer, string* quarterPointer, string* outputPointer)
{
	try
	{
		loadWidgets(gui, startingPointButtons, destinationButtons, airlineButtons, quarterButtons, computeButton, airlineData, locationData, startPointPointer, destinationsPointer, airLinePointer, quarterPointer);
		createInput(gui, startPointPointer, destinationsPointer, airLinePointer, quarterPointer);
		createOutput(gui, startPointPointer, destinationsPointer, airLinePointer, quarterPointer, outputPointer);
		for (int i = 0; i < startingPointButtons.size(); i++)
		{
			startingPointButtons[i]->onPress(&startingPointPressed, &gui, startPointPointer, destinationsPointer, airLinePointer, quarterPointer);
		}
		for (int i = 0; i < destinationButtons.size(); i++)
		{
			destinationButtons[i]->onPress(&destinationPressed, &gui, startPointPointer, destinationsPointer, airLinePointer, quarterPointer);
		}
		for (int i = 0; i < airlineButtons.size(); i++)
		{
			airlineButtons[i]->onPress(&airlinePressed, &gui, startPointPointer, destinationsPointer, airLinePointer, quarterPointer);
		}
		for (int i = 0; i < quarterButtons.size(); i++)
		{
			quarterButtons[i]->onPress(&quarterPressed, &gui, startPointPointer, destinationsPointer, airLinePointer, quarterPointer);
		}
		computeButton->onPress(&computePressed, &gui, startPointPointer, destinationsPointer, airLinePointer, quarterPointer, outputPointer);
		//cout << startingPoints.size();
		return true;
	}
	catch (const tgui::Exception& e)
	{
		std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
		return false;
	}
}

int main()
{
	vector <tgui::Button::Ptr> startingPointButtons;
	vector <tgui::Button::Ptr> destinationButtons;
	vector <tgui::Button::Ptr> airlineButtons;
	vector <tgui::Button::Ptr> quarterButtons;
	tgui::Button::Ptr computeButton;

	map <string, string> airlineData;
	map <string, int> locationData;

	string startPoint;
	string* startPointPointer = &startPoint;

	string airLine;
	string* airLinePointer = &airLine;

	set<string> destinations;
	set<string>* destinationsPointer = &destinations;

	string quarter;
	string* quarterPointer = &quarter;
	int quarterFinal;

	string output = "test line 1 \ntest line 2";
	string* outputPointer = &output;

	bool redrawInputOutput;
	bool* redrawInputOutputPointer = &redrawInputOutput;

	sf::RenderWindow window(sf::VideoMode(1000, 650), "TGUI window");

	//read data
	readData(airlineData, locationData);

	tgui::Gui gui(window);

	if (!runCode(gui, startingPointButtons, destinationButtons, airlineButtons, quarterButtons, computeButton, airlineData, locationData, startPointPointer, destinationsPointer, airLinePointer, quarterPointer, outputPointer))
		return EXIT_FAILURE;

	//while (window.isOpen())
	//{
	//    cout << "hi";
	//}

	gui.mainLoop();
	//cout << "hi";
	//cout << startPoint;
	return EXIT_SUCCESS;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file