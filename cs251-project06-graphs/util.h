/*util.h*/

#pragma once

#include <iostream>
#include <string>

#include "graph.h"

using namespace std;

void buildGraph(string filename, graph& g);
vector<char> Dijkstra(graph& g, char startV, int distance[], char predV[]);
int findIndex(char target, vector<char> vertices);
vector<char> DFS(graph& g, char startV);
vector<char> BFS(graph& g, char startV);