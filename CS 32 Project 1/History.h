//
//  History.hpp
//  CS 32 Project 1
//
//  Created by Madeleine Murphy on 4/8/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#ifndef History_hpp
#define History_hpp
#include "globals.h"
#include <stdio.h>
class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_rows;
    int m_cols;
    char grid[MAXROWS][MAXCOLS];
};


#endif /* History_hpp */
