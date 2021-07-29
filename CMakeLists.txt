cmake_minimum_required(VERSION 3.17)
project(Project3_Travel_Optimization)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project3_Travel_Optimization main.cpp Data/FileManager.cpp Data/FileManager.h Data/FlightGraph.cpp Data/FlightGraph.h Data/FlightEdge.cpp Data/FlightEdge.h Function/DjikstrasModAlgo.cpp Function/DjikstrasModAlgo.h Function/FloydWarshallAlgo.cpp Function/FloydWarshallAlgo.h)