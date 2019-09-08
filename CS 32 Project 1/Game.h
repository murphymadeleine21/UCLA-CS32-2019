//
//  Game.h
//  CS 32 Project 1
//
//  Created by Madeleine Murphy on 4/4/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <string>

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};
#endif /* Game_h */
