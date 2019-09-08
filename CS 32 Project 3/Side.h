//
//  Side.h
//  CS 32 Project 3
//
//  Created by Madeleine Murphy on 5/13/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#ifndef Side_h
#define Side_h

enum Side { NORTH, SOUTH };

const int NSIDES = 2;
const int POT = 0;

inline
Side opponent(Side s)
{
    return Side(NSIDES - 1 - s);
}

#endif /* Side_h */
