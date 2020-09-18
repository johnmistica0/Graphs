/*minqueue.h*/

//
// Min queue that stores (key, value) pairs using a min-heap
// implementation.  When pop is called, the key from the
// (key, value) pair with the smallest value is returned; if
// two pairs have the same value, the smaller key is returned.
// Push and pop have O(lgN) time complexity.
//
// Name: John Mistica
// UIN:660678902
// NetID: jmisti2@uic.edu
// 
// Original author: Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #07
//

#pragma once

#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>

#include <map>

using namespace std;


template<typename TKey, typename TValue>
class minqueue
{
    private:
    
    int size;
    int capacity;
    
    struct NODE
    {
        TKey    Key;
        TValue  Value;
    };
    
    NODE* heap;
    
    map<TKey, int> Map;


public:
    //
    // default constructor:
    //
    // Queue has a max capacity for efficient implementation.
    // This max capacity must be specified at queue creation.
    //
    minqueue(int capacity)
    {
        size = 0;
        this->capacity = capacity;
        heap = new NODE[capacity];
    }
    
    //
    // fill constructor:
    //
    // This allows for the efficient O(N) construction of
    // a queue with an initial set of keys, all with the same
    // initial value.  The max capacity of the queue is
    // set to the # of keys provided for initialization;
    // it is assumed the keys are in ascending order.
    //
    minqueue(vector<TKey> keys, TValue initialValue)
    {
        capacity = keys.size();
        heap = new NODE[keys.size()];
        size = keys.size();
        for(size_t i = 0; i < keys.size(); i++){
            heap[i].Key = keys.at(i);
            heap[i].Value = initialValue;
            Map.emplace(keys.at(i), i);
        }
        
    }
    
    
    //
    // destructor:
    //
    virtual ~minqueue()
    {
        delete[] heap;
        Map.clear();
    }
    
    
    //
    // empty:
    //
    // Returns true if empty, false if not.
    //
    bool empty()
    {
        return(size == 0);
    }
    
    //
    // empty:
    //
    // Deletes corresponding key and value pair in heap
    //
    void del(TKey key, TValue value){
        int p = Map[key];
        if(p == size-1){
            size--;
            return;
        }
        
        Map.erase(heap[Map[key]].Key);
        Map[heap[size-1].Key] = p;
        heap[p] = heap[size-1];
        size--;
        
        if(Map[heap[p].Key] != 0){
            siftUp(Map[heap[p].Key]);
        }
        
        if(Map[heap[p].Key] != size-1){
            siftDown(Map[heap[p].Key]);
        }
        
    }
    
    //
    // swap:
    // swaps two nodes on the heap and map
    //
    void swap(int nodeIndex, int minIndex){
        TKey tmpKey;//temp values for swapping nodes
        TValue tmpVal;//temp values for swapping nodes
        tmpKey = heap[minIndex].Key;
        tmpVal = heap[minIndex].Value;
        Map[heap[minIndex].Key] = nodeIndex;//swaps corresponding index relative to key in map
        heap[minIndex] = heap[nodeIndex];//swaps the nodes between the minIndex and nodeIndex
        Map[heap[nodeIndex].Key] = minIndex;//swaps corresponding index relative to key in map
        heap[nodeIndex].Key = tmpKey;
        heap[nodeIndex].Value = tmpVal;
    }
    
    //
    // siftDown:
    //
    //based off of algorithm from http://www.algolist.net/Data_structures/Binary_heap/Remove_minimum
    //sifts down the root of the heap and detects if elements are out of order which then swaps them.
    //
    void siftDown(int nodeIndex){
        TKey tmpKey;//temp values for swapping nodes
        TValue tmpVal;//temp values for swapping nodes
        int minIndex;//keep strack of minIndex which is the node to swap
        int leftChildIndex = 2*nodeIndex+1;
        int rightChildIndex = 2*nodeIndex+2;
        if(rightChildIndex >= size){//if current node has no right child
            if(leftChildIndex >= size){//if current node has no children sifting is over
                return;
            }
            else{//if current node  has only one left child sets as minIndex
                minIndex = leftChildIndex;
            }
        }
        else{//if current node has two children
            if(heap[leftChildIndex].Value <= heap[rightChildIndex].Value){//compares the smallest of two children
                minIndex = leftChildIndex;//if current node has only one left child sets as minIndex
            }
            else{
                minIndex = rightChildIndex;//if current node has only one right child sets as the minIndex
            }
        }
        if(heap[nodeIndex].Value == heap[nodeIndex+1].Value){//checks for if keys are in same order and orders them into ascending order
            if(heap[nodeIndex].Key > heap[nodeIndex+1].Key){
                swap(nodeIndex, nodeIndex+1);
                siftDown(minIndex);
            }
        }
        if(heap[nodeIndex].Value > heap[minIndex].Value){//checks to see if there should be a swap
            tmpKey = heap[minIndex].Key;
            tmpVal = heap[minIndex].Value;
            Map[heap[minIndex].Key] = nodeIndex;//swaps corresponding index relative to key in map
            heap[minIndex] = heap[nodeIndex];//swaps the nodes between the minIndex and nodeIndex
            Map[heap[nodeIndex].Key] = minIndex;//swaps corresponding index relative to key in map
            heap[nodeIndex].Key = tmpKey;
            heap[nodeIndex].Value = tmpVal;
            siftDown(minIndex);//recursive call that continually sifts down heap until all nodes are in valid position
        }
        
        
    }
    
    //
    //siftUp
    //
    //based off algorithm from http://www.algolist.net/Data_structures/Binary_heap/Insertion
    //sifts up heap and if heap property is broken ex. elements are in wrong order, its swaps
    //
    void siftUp(int nodeIndex){
        int parentIndex;
        TKey tmpKey;
        TValue tmpVal;
        if(nodeIndex != 0){
            parentIndex = (nodeIndex-1)/2;
            if(heap[nodeIndex].Value == heap[nodeIndex-1].Value){//checks for if keys are in same order and orders them into ascending order
                if(heap[nodeIndex].Key < heap[nodeIndex-1].Key){
                    swap(nodeIndex, nodeIndex-1);
                    siftUp(parentIndex);
                }
            }
            if(heap[parentIndex].Value > heap[nodeIndex].Value){//if heap property is broken swaps child and parent in heap
                tmpKey = heap[parentIndex].Key;
                tmpVal = heap[parentIndex].Value;
                Map[heap[parentIndex].Key] = nodeIndex;//swaps corresponding index to key in the map
                heap[parentIndex] = heap[nodeIndex];
                Map[heap[nodeIndex].Key] = parentIndex;//swaps corresponding index to key in the map
                heap[nodeIndex].Key = tmpKey;
                heap[nodeIndex].Value = tmpVal;
                siftUp(parentIndex);//recursive call to siftUp heap
            }
        }
    }
    
    //
    // push:
    //
    // Inserts the given (key, value) pair into the queue such that
    // pop always returns the pair with the minimum value.  If the
    // key is *already* in the queue, it's value is updated to the
    // given value and the queue reordered.  If the key is not in
    // the queue, the (key, value) pairs is added and the queue
    // reordered.
    //
    // NOTE: if two keys have the same value, i.e. (key1, value) and
    // (key2, value), then those pairs are ordered into ascending value
    // by their key.
    //
    void pushinorder(TKey key, TValue value)
    {
        
        if(empty()){//if heap is empty, then sets new key and value to root
            size++;
            heap[0].Key = key;
            heap[0].Value = value;
            Map.emplace(key, size-1);
            return;
        }
                
        if(Map.find(key) != Map.end()){//if key is already in queue overrides value
            heap[Map[key]].Value = value;//overrides value in already existing key
            siftUp(Map[key]);//then sifts up from the existing key to see if new value is in valid position
            siftDown(Map[key]);//first sifts down to check for any invalid positions
            return;
        }
        
        if((size == capacity) && (Map.find(key) == Map.end())){
            throw runtime_error("minqueue::pushinorder: queue is full");
            return;
        }
        
        if(Map.find(key) == Map.end()){//if key is not already in queue
            size++;
            heap[size-1].Key = key;
            heap[size-1].Value = value;
            siftUp(size-1);
            Map.emplace(key, size-1);//adds key and index to graph
            return;
        }

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
        if(empty()){
            throw logic_error("minqueue::minfront: queue empty");
        }
        return heap[0].Key;//returns the front of the queue
    }
    

    
    
    //
    // pop:
    //
    // Pops and discards the (key, value) pair at the front of the queue.
    // Throws a logic_error exception if the queue is empty.
    //
    void minpop()
    {
        if (empty())
        {
            throw logic_error("minqueue::minpop: queue empty");
        }
        else{
            del(heap[0].Key, heap[0].Value);
        } 

    }
    
};
