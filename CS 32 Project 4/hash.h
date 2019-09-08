//
//  hash.hpp
//  Project 4
//
//  Created by Madeleine Murphy on 6/1/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#ifndef hash_h
#define hash_h

#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

const unsigned int NUMBUCKETS = 12800;

class HashTable
{
public:
    HashTable();
//    ~HashTable();
    void search(const string& seq, bool& found, vector<int>& result);
    void add(const string& seq, int pos);
private:
    struct Node
    {
        string data;
        vector<int> offset;
    };
    vector<list<Node>> Buckets;
    unsigned int hashFunc(const string& hashMe);
   // Node* searchList(const list<Node>& findMe);
};


#endif /* hash_h */
