//
//  hash.cpp
//  Project 4
//
//  Created by Madeleine Murphy on 6/1/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include "hash.h"
#include <functional>

HashTable::HashTable()
{
    list<Node> lf;
    for (int i = 0; i < NUMBUCKETS; i++)        //make a vector of size 12800, each slot holds an empty list
        Buckets.push_back(lf);
}

void HashTable::search(const string& seq, bool& found, vector<int>& result)
{
    int bucketNum = hashFunc(seq);          //use hash function to compute bucket number
    list<Node> current = Buckets[bucketNum];    //look at that bucket
    if (current.empty()) //if there's no list at that bucket
        return;
    else
    {
        for (auto i = current.begin(); i != current.end(); i++) //look through entire list for sequence
        {
            if (i->data == seq)
            {
                found = true;
                result = i->offset;
                return;       //return the vector of positions
            }
        }
    }
    return;
}



void HashTable::add(const string& seq, int pos)
{

    bool found = false;
    vector<int> addV;
    search(seq, found, addV);
    if (found == true)      //if it already exists, only add the position it exists at
    {
        unsigned int bucketNum = hashFunc(seq);      //use hash function to compute bucket number
        list<Node> current = Buckets[bucketNum];    //look at the list in that bucket
        for (auto i = current.begin(); i != current.end(); i++) //look through entire list for sequence
        {
            if (i->data == seq)
            {
                i->offset.push_back(pos);           //push that position
            }
        }
        Buckets[bucketNum] = current;
        return;
    }
    unsigned int bucketNum = hashFunc(seq);      //use hash function to compute bucket number
    list<Node> current = Buckets[bucketNum];    //look at the list in that bucket
    Node newNode;                               //make a new node
    newNode.data = seq;                         //set that Node's information to the appropriate values
    newNode.offset.push_back(pos);              //add position to position vector
    current.push_back(newNode);                 //add the node to the list
    Buckets[bucketNum] = current;               //update bucket to contain list
}

unsigned int HashTable::hashFunc(const string& hashMe)
{
    hash<string> strhash;           //hash function that uses <functional>
    unsigned int hashValue = strhash(hashMe);       //compute hash functions's number
    unsigned int bucketNum = hashValue % NUMBUCKETS;        //convert to our own number
    return bucketNum;
}


//Not necessary ??
//HashTable::~HashTable()
//{
//    for (int i = 0; i < NUMBUCKETS; i++)
//        Buckets[i].clear();             //clear every list in each bucket
//}

