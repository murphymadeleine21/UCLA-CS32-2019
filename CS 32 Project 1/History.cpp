//
//  History.cpp
//  CS 32 Project 1
//
//  Created by Madeleine Murphy on 4/8/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    
    for (int r = 0; r < nRows; r++){        //making a 2D array corresponding to rows and cols
        for (int k = 0; k < nCols; k++){
            grid[r][k] = 64;    //ASCII value before A
        }
    }
}


bool History::record(int r, int c)
{
    if (r < 1  ||  r > m_rows  ||  c < 1  ||  c > m_cols){
        return false;
    }
    grid[r-1][c-1]++;   //increment the value at that position
    return true;
}

void History::display() const
{
    int r, c;   
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < m_rows; r++)
    {
        for (c = 0; c < m_cols; c++){
            if (grid[r][c] == 64)
                cout << '.';
            else
                cout << grid[r][c];
        }
        cout << endl;
    }
    cout << endl;
}
