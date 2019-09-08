//
//  Game.h
//  CS 32 Project 1
//
//  Created by Madeleine Murphy on 4/4/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#ifndef Arena_h
#define Arena_h

#include "globals.h"
#include "History.h"

class Zombie;
class Player;
class History;

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     zombieCount() const;
    int     numZombiesAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;
    History& history(); //make const?
    
    // Mutators
    bool   addZombie(int r, int c);
    bool   addPlayer(int r, int c);
    bool   attackZombieAt(int r, int c, int dir);
    bool   moveZombies();
    
private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Zombie* m_zombies[MAXZOMBIES];
    int     m_nZombies;
    History m_history;
};
#endif /* Arena_h */
