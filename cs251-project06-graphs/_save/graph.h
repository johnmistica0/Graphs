/*graph.h*/

//
// Simple graph class where vertices are single uppercase letters, 
// 'A'..'Z', and an adjacency matrix is used for the representation.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
//

#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class graph
{
private:
  int  Matrix[26][26];  // adjacency matrix
  bool Vertices[26];    // true if a vertex, false if not

public:
  // default constructor:
  graph()
  {
    //
    // initialize the adjacency matrix, and the vertices:
    //
    for (int i = 0; i < 26; ++i)
    {
      Vertices[i] = false;

      for (int j = 0; j < 26; ++j)
        Matrix[i][j] = -1;
    }
  }

  //
  // numvertices:
  //
  int numvertices()
  {
    int count = 0;

    for (int i = 0; i < 26; ++i)
    {
      if (Vertices[i])
        count++;
    }

    return count;
  }

  //
  // isvertex:
  //
  bool isvertex(char v)
  {
    if (v < 'A' || v > 'Z')
      return false;

    int i = v - 'A';

    return Vertices[i];
  }

  //
  // addvertex:
  //
  bool addvertex(char v)
  {
    if (v < 'A' || v > 'Z')
      return false;

    int i = v - 'A';

    Vertices[i] = true;
    return true;
  }

  //
  // addedge:
  //
  bool addedge(char from, char to, int weight)
  {
    if (!isvertex(from) || !isvertex(to))
      return false;

    int i = from - 'A';
    int j = to - 'A';

    Matrix[i][j] = weight;
    return true;
  }

  //
  // getweight:
  //
  int getweight(char from, char to)
  {
    if (!isvertex(from) || !isvertex(to))
      return -1;

    int i = from - 'A';
    int j = to - 'A';

    return Matrix[i][j];
  }

  //
  // vertices:
  //
  vector<char> vertices()
  {
    vector<char>  V;

    for (int i = 0; i < 26; ++i)
    {
      if (Vertices[i])
        V.push_back('A' + i);
    }

    return V;
  }

  //
  // neighbors:
  //
  vector<char> neighbors(char v)
  {
    vector<char>  V;

    if (!isvertex(v))
      return V;

    int i = v - 'A';

    //
    // loop along row, if there's an edge in the column then that
    // vertex is a neighbor:
    //
    for (int j = 0; j < 26; ++j)
    {
      if (Matrix[i][j] >= 0)
        V.push_back(j + 'A');
    }

    return V;
  }

  //
  // output:
  //
  // Outputs graph to the console, typically for debugging purposes.
  //
  void output()
  {
    vector<char> V = vertices();

    cout << "**Vertices: ";

    for (char c : V)
    {
      cout << c << " ";
    }

    cout << endl;

    cout << "**Edges: ";

    for (char v : V)
    {
      vector<char> adjacent = neighbors(v);

      for (char n : adjacent)
      {
        int weight = getweight(v, n);
        cout << "(" << v << "," << n << "," << weight << ") ";
      }
    }

    cout << endl;
  }

};
