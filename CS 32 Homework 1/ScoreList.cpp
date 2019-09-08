//
//  ScoreList.cpp
//  CS 32 Homework 1
//
//  Created by Madeleine Murphy on 4/15/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include "ScoreList.h"

ScoreList::ScoreList()
{
    //default constructor
}

bool ScoreList::add(unsigned long score)
{
    if (0 <= score && score <= 100){
        m_scoreList.insert(m_scoreList.size(), score);
        return true;
    }
    return false;
}
// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.

bool ScoreList::remove(unsigned long score)
{
    if(m_scoreList.find(score)!= -1)
    {
        m_scoreList.erase(m_scoreList.find(score));
        return true;
    }
    return false;
}
// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.

int ScoreList::size() const
{
    return m_scoreList.size();
}
// Return the number of scores in the list.

unsigned long ScoreList::minimum() const
{
    if (m_scoreList.empty())
        return NO_SCORE;
    for (int i = 0; i <= 100; i++)
    {
        if (m_scoreList.find(i) != -1){
            return i;
        }
    }
    return NO_SCORE;
}
// Return the lowest score in the score list.  If the list is
// empty, return NO_SCORE.

unsigned long ScoreList::maximum() const
{
    if (m_scoreList.empty())
        return NO_SCORE;
    for (int i = 100; i >= 0; i--)
    {
        if (m_scoreList.find(i) != -1){
            return i;
        }
    }
    return NO_SCORE;
}
// Return the highest score in the score list.  If the list is
// empty, return NO_SCORE.
