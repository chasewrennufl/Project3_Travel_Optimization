//
// Created by Chase Wrenn on 7/27/21.
//

#include "DjikstrasModAlgo.h"

short getIndex(vector<short>& v, short K) //source - https://www.geeksforgeeks.org/how-to-find-index-of-a-given-element-in-a-vector-in-cpp/
{
	auto it = find(v.begin(), v.end(), K);

	// If element was found
	if (it != v.end())
	{

		// calculating the index
		// of K
		short index = it - v.begin();
		return index;
	}
	else {
		// If the element is not
		// present in the vector
		return -1;
	}
}

bool alreadyChecked(vector<short>& destsChecked, short x)
{
	for (auto it = destsChecked.begin(); it != destsChecked.end(); ++it)
	{
		if (*it == x)
			return true;
	}
	return false;
}

vector<FlightEdge> getPath(FlightGraph& graph, short origin, short dest, map<short, short>& p, map<short, double>& d)
{
	short cur = dest;
	vector<FlightEdge> path;
	while (cur != origin) {
		short last = p[cur];
		FlightEdge edge;
		edge.price = d[cur] - d[last];
		edge.destWAC = cur;
		edge.originWAC = last;
		edge.airlineCode = graph.getAirlineFromData(edge.originWAC, edge.destWAC, edge.price);
		path.push_back(edge);
		cur = last;
	}
	return path;
}

//Will return a vector of all pairs, with the indices matching the indicies of dests. First is distance, second is path
map<short, pair<double, vector<FlightEdge>>> djikstraRun(FlightGraph& graph, short origin, vector<short> dests)
{
	short s = origin;
	vector<short> ss = { origin };
	vector<short> vs;
	map<short, short> p; //first is wac, second is previous
	map<short, double> d; //first is wac, second is price/distance
	map<short, pair<double, vector<FlightEdge>>> returnMap;
	for (auto it = graph.graph.begin(); it != graph.graph.end(); ++it)
	{
		if (it->first != s)
		{
			vs.push_back(it->first);
		}
	}
	for (short v : vs)
	{
		p[v] = s;
		if (graph.isFlight(s, v))
			d[v] = graph.getWeight(s, v);
		else
			d[v] = DBL_MAX;
		//cout << d[v] << endl;

	}
	while (!vs.empty())
	{
		int smallestShort = 0;
		double smallestDouble = DBL_MAX;
		for (int i = 0; i < vs.size(); i++)
		{
			if (d[vs.at(i)] < smallestDouble)
				//cout << d[vs.at(i)];
				smallestShort = i;
		}
		short u = vs.at(smallestShort);
		ss.push_back(vs.at(smallestShort));
		vs.erase(vs.begin() + smallestShort);
		for (int i = 0; i < graph.graph.at(ss.at(ss.size() - 1)).size(); i++)
		{
			if (d[u] + graph.graph.at(ss.at(ss.size() - 1)).at(i).price < d[graph.graph.at(ss.at(ss.size() - 1)).at(i).destWAC])
			{
				d[graph.graph.at(ss.at(ss.size() - 1)).at(i).destWAC] = d[u] + graph.graph.at(ss.at(ss.size() - 1)).at(i).price;
				p[graph.graph.at(ss.at(ss.size() - 1)).at(i).destWAC] = u;
			}
		}
	}
	for (int i = 0; i < dests.size(); i++) //Here would be the error checking to make sure if dests in graph
	{
		returnMap[dests.at(i)] = make_pair(d[dests.at(i)], getPath(graph, origin, dests.at(i), p, d));
	}

	return returnMap;
}

vector<FlightEdge> DjikstrasModAlgo::findShortestPaths(FlightGraph& graph, short origin, vector<short> dests)
{
	vector<short> destsChecked;
	destsChecked.push_back(origin);
	map<short, pair<double, vector<FlightEdge>>> tempDists;
	vector<FlightEdge> returnVector;
	while (!dests.empty())
	{
		tempDists = djikstraRun(graph, destsChecked.at(destsChecked.size() - 1), dests);;
		short lowestIndex = 0;
		double lowestDist = DBL_MAX;
		//for (int i = 0; i < tempDists.size(); i++)
		for (auto it = tempDists.begin(); it != tempDists.end(); ++it)
		{
			if (it->second.first < lowestDist)
				lowestIndex = it->first;
		}
		destsChecked.push_back(lowestIndex);
		int x = getIndex(dests, lowestIndex);
		dests.erase(dests.begin() + x);
		for (int i = 0; i < tempDists[lowestIndex].second.size(); i++)
		{
			returnVector.push_back(tempDists[lowestIndex].second.at(i));
		}
	}
	//run once more for way back
	tempDists = djikstraRun(graph, destsChecked.at(destsChecked.size() - 1), { origin });
	for (int i = 0; i < tempDists[origin].second.size(); i++)
	{
		returnVector.push_back(tempDists[origin].second.at(i));
	}
	return returnVector;
}
