//
//  testSequence.cpp
//  CS 32 Homework 1
//
//  Created by Madeleine Murphy on 4/16/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include <stdio.h>
#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    assert(s.insert(42) == 0);
    assert(s.size() == 1  &&  s.find(42) == 0);
    
    
    Sequence p;
    p.insert(0, 1);
    p.insert(1, 2);
    p.insert(2, 3);
    p.insert(3, 2);
    p.insert(4, 5);
    assert(p.remove(2) == 2);
    assert(p.size() == 3);
    string x;
    /*assert(p.get(0, x)  &&  x == "a");      //tests for std:string
    assert(p.get(1, x)  &&  x == "c");
    assert(p.get(2, x)  &&  x == "e");
     
     Sequence s;
     assert(s.empty());
     assert(s.find("laobing") == -1);
     assert(s.insert("laobing") == 0);
     assert(s.size() == 1  &&  s.find("laobing") == 0);
     
     Sequence s1;
     s1.insert(0, "paratha");
     s1.insert(0, "focaccia");
     Sequence s2;
     s2.insert(0, "roti");
     s1.swap(s2);
     assert(s1.size() == 1  &&  s1.find("roti") == 0  &&  s2.size() == 2  &&
     s2.find("focaccia") == 0  &&  s2.find("paratha") == 1);

     Sequence s;
     s.insert(0, "dosa");
     s.insert(1, "pita");
     s.insert(2, "");
     s.insert(3, "matzo");
     assert(s.find("") == 2);
     s.remove("dosa");
     assert(s.size() == 3  &&  s.find("pita") == 0  &&  s.find("") == 1  &&
     s.find("matzo") == 2);

 */
    cout << "Passed all tests" << endl;
}
 
