//
//  Board.cpp
//  CS 32 Project 3
//
//  Created by Madeleine Murphy on 5/13/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include "Board.h"
#include "Side.h"
#include <iostream>
using namespace std;

Board::Board(int nHoles, int nInitialBeansPerHole)
{
    if (nHoles < 0)
        nHoles = 1;
    if (nInitialBeansPerHole < 0)
        nInitialBeansPerHole = 0;
    
    m_north = new int[nHoles];
    m_south = new int[nHoles];
    
    m_totalHoles = nHoles*2;
    m_holesOnSide = nHoles;
    
    for (int i = 0; i < nHoles; i++)
    {
        m_north[i] = nInitialBeansPerHole;
        m_south[i] = nInitialBeansPerHole;
    }
    
    m_southPot = 0;
    m_northPot = 0;
    
    m_totalBeans = nInitialBeansPerHole*m_totalHoles;
    
  
}
//Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole. If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.


int Board::holes() const
{
    return m_holesOnSide;
}
//Return the number of holes on a side (not counting the pot).


int Board::beans(Side s, int hole) const
{
    if (s == NORTH)
    {
        if (hole == 0)
            return m_northPot;
        else if (hole <= holes())
            return m_north[hole-1];
    }
    
    if (s == SOUTH)
    {
        if (hole == 0)
            return m_southPot;
        else if (hole <= holes())
            return m_south[hole-1];
    }

    return -1;
}
//Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.


int Board::beansInPlay(Side s) const
{
    if (s == NORTH)
    {
        int Ntotal = 0;
        for (int i = 0; i < holes(); i++)
            Ntotal += m_north[i];
        return Ntotal;
    }
    
    if (s == SOUTH)
    {
        int Stotal = 0;
        for (int k = 0; k < holes(); k++)
            Stotal += m_south[k];
        return Stotal;
    }
    return 0;  
}
//Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.


int Board::totalBeans() const
{
    return m_totalBeans;  
}
//Return the total number of beans in the game, including any in the pots.


bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    if (hole > holes() || hole < 0) //if the hole is invalid
        return false;
    if (hole == 0)      //if hole is a pot
        return false;
    
    if (s == NORTH)
    {
        if (m_north[hole-1] == 0)   //if the hole is empty
            return false;
        
        int beansToSow = m_north[hole-1];   //store number of beans to sow
        m_north[hole-1] = 0;                //remove the beans from the hole
        Side currentSide = NORTH;           //keep track of side we're on
        int currentHole = hole-1;           //keep track of hole we're in, starting at the one after we started with
                                                //(counterclockwise if north, so subtract 1)
        
        while (beansToSow != 0)
        {
            if (currentSide == NORTH && currentHole == 0) //we're s's pot, North
            {
                m_northPot++;                               //add to north's pot
                beansToSow--;
                currentSide = SOUTH;                        //switch sides
                currentHole = 1;                            //go to next hole, which is 1st of south
            }
            else if (currentSide == NORTH)  //we're at a hole in North
            {
                m_north[currentHole-1]++;   //add one bean to that hole
                currentHole--;              //move counterclockwise
                beansToSow--;
            }
            else if (currentSide == SOUTH && currentHole > holes()) //we're at South's pot, our opponents pot
            {
                currentSide = NORTH;        //switch back to North's side
                currentHole = holes();      //current hole is last of north's holes, b/c counterclockwise motion
            }
            else if (currentSide == SOUTH) //we're at a hole in South
            {
                m_south[currentHole-1]++;   //add one bean to that hole
                currentHole++;              //move counterclockwise (forward on south)
                beansToSow--;
            }
        }
        endSide = currentSide;
        if (endSide == SOUTH && currentHole == 1)   //we ended in North's pot
        {
            endSide = NORTH;
            endHole = 0;
        }
        else if (endSide == SOUTH)
            endHole = currentHole-1;
        else if (endSide == NORTH)
            endHole = currentHole + 1;
    }
    
    if (s == SOUTH)
    {
        if (m_south[hole-1] == 0)   //if the hole is empty
            return false;
        
        int beansToSow = m_south[hole-1];   //store number of beans to sow
        m_south[hole-1] = 0;                //remove the beans from the hole
        Side currentSide = SOUTH;           //keep track of side we're on
        int currentHole = hole+1;           //keep track of hole we're in, starting at the one after we started with
                                                //(counterclockwise in south, so add 1)
        while (beansToSow != 0)
        {
            if (currentSide == SOUTH && currentHole > holes()) //we're at South's pot, our pot
            {
                m_southPot++;                               //add to south's pot
                beansToSow--;
                currentSide = NORTH;        //switch back to North's side
                currentHole = holes();      //current hole is last of north's holes, b/c counterclockwise motion
            }
            else if (currentSide == SOUTH) //we're at a hole in South
            {
                m_south[currentHole-1]++;   //add one bean to that hole
                currentHole++;              //move counterclockwise (forward on south)
                beansToSow--;
            }
            else if (currentSide == NORTH && currentHole == 0) //we're North's pot, our opponent's pot
            {
                currentSide = SOUTH;                        //switch back to South's side
                currentHole = 1;                            //go to next hole, which is 1st of south
            }
            else if (currentSide == NORTH)  //we're at a hole in North
            {
                m_north[currentHole-1]++;   //add one bean to that hole
                currentHole--;              //move counterclockwise
                beansToSow--;
            }
        }
        endSide = currentSide;
        if (endSide == NORTH && currentHole == holes())   //we ended in South's pot
        {
            endSide = SOUTH;
            endHole = 0;
        }
        else if (endSide == SOUTH)
            endHole = currentHole-1;
        else if (endSide == NORTH)
            endHole = currentHole + 1;
    }
   
    return true;
}
//If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The parameters endSide and endHole are set to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)


bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    if (hole > holes() || hole < 0) //if the hole is invalid
        return false;
    if (hole == 0)      //if hole is a pot
        return false;
    
    if (s == SOUTH)
    {
        int beansInHole = m_south[hole-1];
        m_south[hole-1] = 0;        //remove the beans
        if (potOwner == NORTH)      //add the beans to pot belonging to potOwner
            m_northPot += beansInHole;
        else if (potOwner == SOUTH)
            m_southPot += beansInHole;
    }
    if (s == NORTH)
    {
        int beansInHole = m_north[hole-1];
        m_north[hole-1] = 0;        //remove the beans
        if (potOwner == NORTH)      //add the beans to pot belonging to potOwner
            m_northPot += beansInHole;
        else if (potOwner == SOUTH)
            m_southPot += beansInHole;
    }
   
    return true;  
}
//If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.


bool Board::setBeans(Side s, int hole, int beans)
{
    if (hole > holes() || hole < 0) //if the hole is invalid
        return false;
    if (beans < 0)
        return false;
    
    if (s == NORTH)
    {
        if (hole == 0)  //if we're at norths pot
        {
            if (this->beans(NORTH, 0) < beans)  //if we're adding to the pot
            {
                m_northPot = beans;
                m_totalBeans += beans;          //total increases
            }
            else if (this->beans(NORTH, 0) == beans)    //they're the same
                return true;
            else                                //the pot is becoming smaller, so we need to subtract from total
            {
                m_totalBeans -= m_northPot - beans;
                m_northPot = beans;
            }
        }
        else                                //same thing but for North's holes
        {
            if (this->beans(NORTH, hole) < beans)   //the hole is getting bigger
            {
                m_north[hole-1] = beans;
                m_totalBeans += beans;
            }
            else if (this->beans(NORTH, hole) == beans) //the hole is staying the same
                return true;
            else                                        //the hole is getting smaller
            {
                m_totalBeans -= m_north[hole-1] - beans;
                m_north[hole-1] = beans;
                
            }
        }
    }
    
    if (s == SOUTH)         //same idea, but for south now
    {
        if (hole == 0)          //we're at south's pot
        {
            if (this->beans(SOUTH, 0) < beans)
            {
                m_southPot = beans;
                m_totalBeans += beans;
            }
            else if (this->beans(SOUTH, 0) == beans)
                return true;
            else
            {
                m_totalBeans -= m_southPot - beans;
                m_southPot = beans;
            }
        }
        else                //we're at a south hole
        {
            if (this->beans(SOUTH, hole) < beans)
            {
                m_south[hole-1] = beans;
                m_totalBeans += beans;
            }
            else if (this->beans(SOUTH, hole) == beans)
                return true;
            else
            {
                m_totalBeans -= m_south[hole-1] - beans;
                m_south[hole-1] = beans;
            }
        }
    }
    
    return true;  
}
//If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This may change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)


Board::~Board()
{
    delete [] m_north;
    delete [] m_south;
}

Board::Board(const Board& other) //copy constructor
: m_totalHoles(other.m_totalHoles), m_holesOnSide(other.m_holesOnSide), m_totalBeans(other.m_totalBeans), m_northPot(other.m_northPot), m_southPot(other.m_southPot)
{
    m_north = new int[m_holesOnSide];
    m_south = new int[m_holesOnSide];
    
    for (int k = 0; k < holes(); k++){
        m_north[k] = other.m_north[k];
        m_south[k] = other.m_south[k];
    }
}

Board& Board::operator=(const Board& rhs) //assignment operator
{
    if (this != &rhs)
    {
        delete [] m_north;
        delete [] m_south;
        
        m_totalHoles = rhs.m_totalHoles;
        m_holesOnSide = rhs.m_holesOnSide;
        m_totalBeans = rhs.m_totalBeans;
        m_southPot = rhs.m_southPot;
        m_northPot = rhs.m_northPot;
        
        m_north = new int[m_holesOnSide];
        m_south = new int[m_holesOnSide];
        
        for (int k = 0; k < holes(); k++){
            m_north[k] = rhs.m_north[k];
            m_south[k] = rhs.m_south[k];
        }
    }
    return *this;
}
