/*pqueue.h*/

//
// Min queue that stores (key, value) pairs in ascending order by value.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
//

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <stdexcept>

using namespace std;


template<typename TKey, typename TValue>
class minqueue
{
private:
  struct NODE
  {
    TKey    Key;
    TValue  Value;
  };

  vector<NODE>  elements;

public:
  //
  // default constructor:
  //
  minqueue()
  {
    // nothing to do, vector created (and destroyed) automatically
  }

  //
  // empty:
  //
  // Returns true if empty, false if not.
  //
  bool empty()
  {
    return (elements.size() == 0);
  }

  //
  // push:
  //
  // Inserts the given (key, value) pair into the queue such that 
  // (key, value) pairs are stored in ascending order by value.
  // If the key is *already* in the queue, it's value is updated to
  // the given value and the queue reordered.  If the key is not in
  // the queue, the (key, value) pairs is added and then the queue
  // reordered.
  //
  // NOTE: if two keys have the same value, i.e. (key1, value) and
  // (key2, value), then those pairs are ordered into ascending value
  // by their key.
  //
  void pushinorder(TKey key, TValue value)
  {
    // 
    // does vector already contain key?  if so, update:
    //
    bool updated = false;

    for (int i = 0; i < elements.size(); ++i)
    {
      if (elements[i].Key == key)
      {
        elements[i].Value = value;
        updated = true;
        break;
      }
    }

    //
    // if we didn't find and update, then we have to insert:
    //
    if (!updated) 
    {
      NODE n;
      n.Key = key;
      n.Value = value;

      elements.push_back(n);
    }

    //
    // now sort into ascending order by the value (and if the values are 
    // the same, then by key):
    //
    std::sort(elements.begin(), elements.end(),
      [](NODE n1, NODE n2)
      {
        if (n1.Value < n2.Value)  // n1 should come before n2:
          return true;
        else if (n1.Value > n2.Value)  // n1 should follow n2:
          return false;
        else  // n1 and n2 are equal in value, so order by key:
        {
          return n1.Key < n2.Key;
        }
      }
    );
  }

  //
  // front:
  //
  // Returns the key at the front of the queue; does *not* pop the 
  // (key, value) pair.  Throws a logic_error exception if the queue
  // is empty.
  //
  TKey minfront()
  {
    if (elements.size() > 0)
    {
      return elements[0].Key;
    }
    else
    {
      throw logic_error("minqueue: queue empty");
    }
  }

  //
  // pop:
  //
  // Pops and discards the (key, value) pair at the front of the queue.
  // Throws a logic_error exception if the queue is empty.
  //
  void minpop()
  {
    if (elements.size() > 0)
    {
      elements.erase(elements.begin());
    }
    else
    {
      throw logic_error("minqueue: queue empty");
    }
  }

};