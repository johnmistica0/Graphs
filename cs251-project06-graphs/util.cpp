/*util.cpp*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <fstream>
#include <limits>

#include "graph.h"
#include "util.h"
#include "minqueue.h"

using namespace std;

const int infinity = numeric_limits<int>::max();

//
// buildGraph:
//
// Inputs the graph vertices and edges from the given file, building
// the graph g.  File format:
//   vertex vertex vertex ... #
//   src dest weight ... #
//
void buildGraph(string filename, graph& g)
{
  ifstream file(filename);
  char vertex;
  char vertexA;
  char vertexB;
  string weight;

  if (!file.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << filename << "'." << endl;
    cout << endl;
    return;
  }

  //
  // Input vertices as single uppercase letters:  A B C ... #
  //

  //
  // TODO: use >> operator, since we are not inputting
  // strings that might contain blanks:
  //
   file >> vertex;
    
   while (vertex != '#')
   {
      g.addvertex(vertex);
      file >> vertex;
   }
  

  //
  // Now input edges:  Src Dest Weight ... #
  //
  
  file >> vertexA;
  file >> vertexB;
  file >> weight;

  //
  // TODO: use >> operator, since we are not inputting
  // strings that might contain blanks:
  //
  
  while(vertexA != '#'){
     g.addedge(vertexA,vertexB,stoi(weight));
     file >> vertexA;
     file >> vertexB;
     file >> weight;
  }
  
}
                                       

//
// BFS:
//
// Performs a breadth-first search from the given starting vertex.
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> BFS(graph& g, char startV)
{
  vector<char>  visited;
  queue<char>   frontierQueue;
  set<char>     discoveredSet;
  char currentV;
  vector<char>  neighbors;

  //
  // TODO:
  //
  frontierQueue.push(startV);
  discoveredSet.insert(startV);
  
  while (!frontierQueue.empty()){
      currentV = frontierQueue.front();
      frontierQueue.pop();
      visited.push_back(currentV);
      neighbors = g.neighbors(currentV);
      for(unsigned i = 0; i < neighbors.size(); i++){
         if(discoveredSet.find(neighbors.at(i)) == discoveredSet.end()){
            frontierQueue.push(neighbors.at(i));
            discoveredSet.insert(neighbors.at(i));
         }
      }
  }
  return visited;
}

//
// DFS:
//
// Performs a depth-first search from the given starting vertex.
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> DFS(graph& g, char startV)
{
  vector<char>  visited;
  stack<char>   frontierStack;
  set<char>     visitedSet;
  char currentV;
  vector<char> neighbors;

  frontierStack.push(startV);

  
  //
  // TODO: main loop of DFS algorithm
  //
  
  while(!frontierStack.empty()){
     currentV = frontierStack.top();
     frontierStack.pop();
     if(visitedSet.find(currentV) == visitedSet.end()){
        visited.push_back(currentV);
        visitedSet.insert(currentV);
        neighbors = g.neighbors(currentV);
        for(size_t i = 0; i < neighbors.size(); i++){
           frontierStack.push(neighbors.at(i));
        }
     }
  }
  

  return visited;
}


int findIndex(char target, vector<char> vertices){//returns the index of the designated element in the vector
    for(unsigned i = 0; i < vertices.size(); i++){
        if(vertices.at(i) == target){
            return i;
        }
    }
    return -1;
}

// Dijkstra:
// 
// Performs a search that finds shortest distances from each vertex in the graph.
// Returns the vertices in the order they were visited.
// 

vector<char> Dijkstra(graph& g, char startV, int distance[], char predV[]){
    vector<char> vertices = g.vertices();
    vector<char> neighbors;
    vector<char> visited;
    minqueue<char, int> unvisitedQueue(vertices, infinity);
    char currentV;
    int edgeWeight;
    int altDistance;
    
    
    for(unsigned i = 0; i < vertices.size(); i++){
        distance[i] = infinity;
        predV[i] = -1;
        //unvisitedQueue.pushinorder(vertices.at(i), infinity);
    }

    //startV has a distance of 0 from itself
    distance[findIndex(startV, vertices)] = 0;
    unvisitedQueue.pushinorder(startV, 0);
    
    while(!unvisitedQueue.empty()){
        //Visit vertex with minimum distance from startV
        currentV = unvisitedQueue.minfront();
        unvisitedQueue.minpop();
        neighbors = g.neighbors(currentV);
                
        if(distance[findIndex(currentV, vertices)] == infinity){
            break;
        }
        visited.push_back(currentV);
        
        for(unsigned i = 0; i < neighbors.size(); i++){
            char adjV = neighbors.at(i);
            edgeWeight = g.getweight(currentV, adjV);
            altDistance = distance[findIndex(currentV, vertices)] + edgeWeight;
            
            // If shorter path from startV to adjV is found,
            // update adjV's distance and predecessor
            if(altDistance < distance[findIndex(adjV, vertices)]){
                distance[findIndex(adjV, vertices)] = altDistance;
                predV[findIndex(adjV, vertices)] = currentV;
                unvisitedQueue.pushinorder(adjV, altDistance);
            }
        }
    }
    return visited;
}