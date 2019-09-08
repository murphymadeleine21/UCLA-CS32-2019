//
//  odds.cpp
//  Homework 4
//
//  Created by Madeleine Murphy on 5/27/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

void removeOdds(vector<int>& v)
{
    for (auto it = v.begin(); it != v.end(); it++)
    {
        if (*it % 2 != 0)
        {
            v.erase(it);
            it = v.begin();     //dont want to skip the first element
            it--;             //we deleted an item and moved past it
        }
    }

}

