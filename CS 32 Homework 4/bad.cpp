//
//  bad.cpp
//  Homework 4
//
//  Created by Madeleine Murphy on 5/27/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

void removeBad(list<Movie*>& li)
{
 
    for (auto it = li.begin(); it != li.end(); it++)
    {
        Movie* mp = *it;
        if (mp->rating() < 55)
        {
            li.erase(it);
            it = li.begin();
            it--;
            delete mp;
        }
    }
}

