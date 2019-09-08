//
//  Player.cpp
//  CS 32 Project 3
//
//  Created by Madeleine Murphy on 5/13/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include "Player.h"
#include <string>
using namespace std;

/////PLAYER IMPLEMENTATIONS/////

Player::Player(string name)
: m_name(name)
{}
//Create a Player with the indicated name.

string Player::name() const
{
    return m_name;  
}
//Return the name of the player.

bool Player::isInteractive() const
{
    return false;
}
//Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.

int Player::chooseMove(const Board& b, Side s) const
{
    return -1;  
}
//Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.

Player::~Player()
{}
//Since this class is designed as a base class, it should have a virtual destructor.

//////////////////////////////////////


/////HUMAN PLAYER IMPLEMENTATIONS/////
HumanPlayer::HumanPlayer(string name) : Player(name)
{}

bool HumanPlayer::isInteractive() const
{
    return true;
}


int HumanPlayer::chooseMove(const Board& b, Side s) const
{
    if (b.beansInPlay(NORTH) == 0 || b.beansInPlay(SOUTH) == 0)
        return -1;
    
    cout << "Select a hole, " << this->name() << ": ";
    int move;
    cin >> move;
    
    if (move <=0 || move > b.holes() || b.beans(s, move) == 0)       //using recursion 
    {
        if (b.beans(s, move) == 0)
            cout << "There are no beans in that hole." << endl;
        else
        {
            if (b.holes() == 1)
                cout << "The hole number must be 1." << endl;
            else
                cout << "The hole number must be from 1 to " << b.holes() << "." << endl;
        }
        return chooseMove(b, s);
    }
    
    else return move;
}

//////////////////////////////////////


/////BAD PLAYER IMPLEMENTATIONS/////

BadPlayer::BadPlayer(string name) : Player(name)
{}


int BadPlayer::chooseMove(const Board& b, Side s) const
{
    if (s == NORTH)
    {
        int k = 1;
        while (k <= b.holes())
        {
            if (b.beans(NORTH, k) != 0)     //returns the first hole on that side that is valid
                return k;
            k++;
        }
    }
    
    if (s == SOUTH)
    {
        int k = 1;
        while (k <= b.holes())
        {
            if (b.beans(SOUTH, k) != 0)     //returns the first hole on that side that is valid
                return k;
            k++;
        }
    }
    return -1;
}

bool BadPlayer::isInteractive() const
{
    return false;
}

//////////////////////////////////////

/////SMART PLAYER IMPLEMENTATIONS/////

SmartPlayer::SmartPlayer(string name) : Player(name)
{
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
    int bestHole = 1;
    int value = 0;
    return chooseMoveHelper(b, s, bestHole, value);
    
}

bool SmartPlayer::isInteractive() const
{
    return false;
}
int SmartPlayer::chooseMoveHelper(const Board& b, Side s, int& bestHole, int& value) const
{
    Board boardCopy = b;      //make a copy of the board
    Board original = b;
    int depth = 5;
    if (boardCopy.beansInPlay(s) == 0)          //there are no more moves to make
    {
        bestHole = -1;
        value = evaluate(boardCopy, s, bestHole, depth, value, s);
        return bestHole;
    }
//    if (depth == 0)
//    {
//        bestHole = -1;
//        value = evaluate(boardCopy, s, bestHole, depth, value, s);
//        return bestHole;
//    }
    int max = -1000;
    for (int i = 1; i <= boardCopy.holes(); i++)
    {
        depth = 5;
        value = 0;
        boardCopy = original;                       //unmake any moves
        if (boardCopy.beans(s, i) > 0){
            int thisMax = evaluate(boardCopy, s, i, depth, value, s);
            if (max < thisMax){
                max = thisMax;
                bestHole = i;
            }
        }
       if (max == 1000)
            return bestHole;
      
        boardCopy = original;                       //unmake move we just made
        if (i + 1 > boardCopy.holes() || boardCopy.beans(s, i+1) == 0)
            continue;
        depth = 5;
        value = 0;
        if (max <= evaluate(boardCopy, s, i+1, depth, value, s)){
            bestHole = i+1;
            max = evaluate(boardCopy, s, i+1, depth, value, s);
        }
    }
    depth = 5;
    evaluate(boardCopy, s, bestHole, depth, value, s); //make sure we have the correct item for value
    return bestHole;
}

int SmartPlayer::evaluate(Board& b, Side s, int hole, int& depth, int& value, Side original) const
{
    if (depth == 0)
        return value;
    
    int end = 0;
    Side x;
    if (!b.sow(s, hole, x, end))
        return value;
  
//    cerr << "North: ";
//    for (int k = 1; k <= b.holes(); k++)
//    {
//        cerr << b.beans(NORTH, k) << " ";
//    }
//    cerr << endl;
//
//    cerr << "South: ";
//    for (int k = 1; k <= b.holes(); k++)
//    {
//        cerr << b.beans(SOUTH, k) << " ";
//    }
//    cerr << endl;
//
//    cerr << "North pot: " << b.beans(NORTH, 0) << endl;
//    cerr << "South pot: " << b.beans(SOUTH, 0) << endl;
//    cerr << endl;
   
   
    if (end == 0)           //if they landed in their own pot, go again
    {
        if (b.beansInPlay(NORTH) != 0 && b.beansInPlay(SOUTH) != 0)     //cant be over
        {
            int max = -1000;
            Board currentBoard = b;                                    //they want to pick the maximum they can when they go again
            for (int i = 1; i <= b.holes(); i++){
                b = currentBoard;
                value = 0;
                int check = evaluate(b, s, i, depth, value, original);
                if (max <= check)
                    max = check;
            }
            return max;
        }
    }
    
    if (x == s && b.beans(s, end) == 1 && b.beans(notSide(s), end) > 0)  //make a capture
    {
        b.moveToPot(notSide(s), end, s);
        b.moveToPot(s, end, s);
    }
    
    if (b.beansInPlay(NORTH) == 0 || b.beansInPlay(SOUTH) == 0)     //if the game is over
    {
         //Do any necessary sweeping
        for (int i = 1; i <= b.holes(); i++)
        {
            b.moveToPot(SOUTH, i, SOUTH);
            b.moveToPot(NORTH, i, NORTH);
        }
        if (original == NORTH)
        {
            if (b.beans(original, 0) > b.beans(SOUTH, 0))           //we won
                value = 1000;
            else if (b.beans(original, 0) < b.beans(SOUTH, 0))      //we lost
                value = -1000;
            else                                                    //a tie
                value = 0;
        }
        else if (original == SOUTH)
        {
            if (b.beans(original, 0) > b.beans(NORTH, 0))           //we won
                value = 1000;
            else if (b.beans(original, 0) < b.beans(NORTH, 0))      //we lost
                value = -1000;
            else                                                    //a tie
                value = 0;
        }
        return value;
    }
    
    
    //The game is still in play
                                       //compare the values in the pots
    value = b.beans(original, 0) - b.beans(notSide(original), 0);
   
    
    if (s == original)                  //next is opponent's move
    {
        depth--;
        int currentMin = 1000;
        Board boardcopy = b;
        for (int i = 1; i < b.holes(); i++)
        {
            b = boardcopy;
            if (original == SOUTH)
            {
                 if (b.beans(NORTH, i) == 0)                //find a valid move only
                     continue;
                int checkThis = evaluate(b, NORTH, i, depth, value, original);      //evaluate that move;
                if (currentMin > checkThis)
                    currentMin = checkThis;
//                evaluate(b, NORTH, i+1, depth, value, original);    //compare to next possible move
//                int checkNext = value;
//                if (currentMin > checkNext)                         //find the minimum
//                    currentMin = checkNext;
            }
            else
            {
                if (b.beans(SOUTH, i) == 0)             //same as above but for other side
                    continue;
                int checkThis = evaluate(b, SOUTH, i, depth, value, original);;
                if (currentMin > checkThis)
                    currentMin = checkThis;
//                evaluate(b, SOUTH, i+1, depth, value, original);
//                int checkNext = value;
//                if (currentMin > checkNext)
//                    currentMin = checkNext;
            }
        }
        //check the last element in case last element is only valid
        int checkThis = 0;
        if (original== SOUTH)
            checkThis = evaluate(b, NORTH, b.holes(), depth, value, original);
        else
            checkThis = evaluate(b, SOUTH, b.holes(), depth, value, original);
        if (checkThis < currentMin)
            currentMin = checkThis;
        return currentMin;
    }
    else                                            //our turn
    {
        depth--;
        int currentMax = -1000;
        Board boardcopy = b;
        for (int i = 1; i < b.holes(); i++)
        {
            b = boardcopy;
            if (original == SOUTH)
            {
                if (b.beans(SOUTH, i) == 0)                //find a valid move only
                    continue;
                int checkThis =  evaluate(b, SOUTH, i, depth, value, original);      //evaluate that move;
                if (currentMax < checkThis)
                    currentMax = checkThis;
//                evaluate(b, NORTH, i+1, depth, value, original);    //compare to next possible move
//                int checkNext = value;
//                if (currentMax < checkNext)                         //find the max
//                    currentMax = checkNext;
            }
            else
            {                                                       //same as above
                if (b.beans(NORTH, i) == 0)
                    continue;
                int checkThis =  evaluate(b, NORTH, i, depth, value, original);;
                if (currentMax < checkThis)
                    currentMax = checkThis;
//                evaluate(b, SOUTH, i+1, depth, value, original);
//                int checkNext = value;
//                if (currentMax < checkNext)
//                    currentMax = checkNext;
            }
        }
        //check the last element in case last element is only valid
        int checkThis = 0;
        if (original== SOUTH)
            checkThis = evaluate(b, SOUTH, b.holes(), depth, value, original);
        else
            checkThis = evaluate(b, NORTH, b.holes(), depth, value, original);
        if (checkThis > currentMax)
            currentMax = checkThis;
        return currentMax;
    }
}



Side SmartPlayer::notSide(Side s) const
{
    if (s == SOUTH)
        return NORTH;
    else
        return SOUTH;
}
