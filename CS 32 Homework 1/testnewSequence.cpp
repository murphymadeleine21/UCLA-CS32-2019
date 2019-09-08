//
//  testnewSequence.cpp
//  CS 32 Homework 1
//
//  Created by Madeleine Murphy on 4/16/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include <stdio.h>
#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence a(1000);   // a can hold at most 1000 items
    Sequence b(5);      // b can hold at most 5 items
    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType v = 5;
    
    // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(v) != -1);
    
    // Failure if we try to insert a sixth item into b
    assert(b.insert(v) == -1);
    
    // When two Sequences' contents are swapped, their capacities are
    // swapped as well:
    a.swap(b);
    assert(a.insert(v) == -1  &&  b.insert(v) != -1);

}
