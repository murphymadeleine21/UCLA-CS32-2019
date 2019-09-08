//
//  testScoreList.cpp.cpp
//  CS 32 Homework 1
//
//  Created by Madeleine Murphy on 4/16/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "ScoreList.h"
#include "Sequence.h"
#include <cassert>
using namespace std;

int main()
{
    ScoreList s;
    s.add(100);
    s.add(101);
    assert(s.add(101) == false);
    assert(s.add(1000) == false);
    assert(s.add(-10) == false);
    assert(s.add(-1) == false);
    //assert(s.add(0) == true);
    //assert(s.add(1) == true);
    s.add(98);
    s.add(99);
    s.add(1);
    s.add(10);
    assert(s.remove(10) == true);
    assert(s.remove(98) == true);
    s.add(98);
    s.add(10);
    s.add(52);
    s.remove(1);
    s.add(9);
    assert(s.minimum() == 9);
    assert(s.maximum() == 100);
    
    ScoreList x;
    assert(x.maximum() == NO_SCORE);
    assert(x.minimum() == NO_SCORE);
    s.add(400);
    assert(x.maximum() == NO_SCORE);
    assert(x.minimum() == NO_SCORE);
    assert(x.size() == 0);
    assert(s.size() == 6);
    
    ScoreList p;
    p.add(1);
    p.add(2);
    p.add(3);
    p.add(4);
    p.add(5);
    p.add(6);
    p.add(7);
    p.add(8);
    p.add(9);
    p.add(10);
    p.add(-1);
    p.add(-2);
    p.add(300);
    p.add(-40);
    p.add(500000000);
    p.add(-50000);
    p.add(890);
    
    
    assert(p.size() == 10);
    assert(p.maximum() == 10);
    assert(p.minimum() == 1);
    
    p.remove(43);
    assert(p.size() == 10);
    assert(p.maximum() == 10);
    assert(p.minimum() == 1);
    
    p.remove(10);
    assert(p.size() == 9);
    assert(p.maximum() == 9);
    assert(p.minimum() == 1);
    cout << "All tests succeeded" << endl;
}

