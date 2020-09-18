/*main.cpp*/

//
// Program to input a graph from an input file, and immediately output to
// the console.
//
// John Mistica 660678902 jmisti2
// U. of Illinois, Chicago
// CS 251: Fall 2019
//

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <fstream>

#include "graph.h"
#include "util.h"
#include "minqueue.h"

using namespace std;


//
// outputGraph:
//
// Outputs graph g to the console.
//
void outputGraph(graph& g)
{
    vector<char> vertices = g.vertices();
    
    cout << "**Vertices: ";
    
    for (char c : vertices)
    {
        cout << c << " ";
    }
    
    cout << endl;
    
    cout << "**Edges: ";
    
    for (char v : vertices)
    {
        vector<char> neighbors = g.neighbors(v);
        
        for (char n : neighbors)
        {
            int weight = g.getweight(v, n);
            cout << "(" << v << "," << n << "," << weight << ") ";
        }
    }
    
    cout << endl;
}

void printVertices(string prefix, vector<char> visited){//prints vertices of returned vectors from BFS, DFS, and Dijkstra
    
    cout << prefix << ": ";
    for (char v : visited)
        cout << v << " ";
            
    cout << endl;
    
}

void printNeighbors(graph g, char startV){
    vector<char> neighbors = g.neighbors(startV);
    cout << "Neighbors: ";
    for(char v: neighbors){
        cout << v << " ";
    }
    cout << endl;
}

void _dijkstra(int index, char predV[], vector<char> visited, vector<char> vertices){//contains loop that prints out vector returned by dijkstra function that prints out in staggering pattern
    char c;
    stack<char> reversed;//stack data structure for reversing elements of the vertex in order they were traversed
    c = visited.at(index);
    
    while(true){
        reversed.push(c);
        if(predV[findIndex(c, vertices)] == -1){
            break;
        }
        c = predV[findIndex(c, vertices)];//traverses to next location of preceeding vertex
    }
    
    while(!reversed.empty()){
        cout << reversed.top() << " ";//prints out vector elements in reversed order that traversed in previous loop
        reversed.pop();
    }
}



int main()
{
    graph  g;
    string filename;
    char   startV;
    
    cout << "Enter filename containing graph data> ";
    cin >> filename;
    
    //
    // Let's input the graph, and then output to see what we have:
    //
    buildGraph(filename, g);
    outputGraph(g);
    
    //
    // now ask user for a starting vertex, and run BFS/DFS as well as
    // strongly-connected algorithms:
    //
    cout << endl;
    cout << "Enter a starting vertex or #> ";
    cin >> startV;
    
    while (startV != '#')
    {
        vector<char> visitedBFS;//returned vector for BFS
        vector<char> visitedDFS;//returned vector for DFS
        vector<char> visitedDJK;//returned vector for Dijkstra
        
        //
        // BFS:
        //
        if (g.isvertex(startV))
        {
            vector<char> vertices = g.vertices();//vector of all vertices on graph
            int distance[vertices.size()];//distance of each correlated vertex used for dijkstra function
            char predV[vertices.size()];//the predV of the designated vertex
            
            visitedBFS = BFS(g, startV);//returned BFS vector
            visitedDFS = DFS(g, startV);//returned DFS vector
            visitedDJK = Dijkstra(g, startV, distance, predV);//returned Dijkstra vector
            
            printNeighbors(g, startV);//prints out neighbors of starting vertex
            printVertices("BFS", visitedBFS);//prints vertices returned by BFS
            printVertices("DFS", visitedDFS);//prints vertices returned by DFS
            printVertices("Dijkstra", visitedDJK);//prints vertices returned by Dijkstra
            
            int index = 0;//keeps track of index of vertex to travel to for Dijkstra output
            
            for(char v : visitedDJK){//loop that prints out the results of the Dijkstra algorithm
                cout << " " << v << ": ";
                cout << distance[findIndex(visitedDJK.at(index), vertices)] << " via ";
                _dijkstra(index, predV, visitedDJK, vertices);//function used to print out elements in pattern traversed
                cout << endl;
                index++;//incremements count which is index
            }
            
        }
        
        else//if vertex is not in graph, prints out error statement
        {
            cout << "Not a vertex in graph, ignored..." << endl;
        }
        
        cout << endl;
        cout << "Enter a starting vertex or #> ";
        cin >> startV;
    }
    
    return 0;
}
