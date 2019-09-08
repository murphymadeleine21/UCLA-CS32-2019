//
//  Game.cpp
//  CS 32 Project 3
//
//  Created by Madeleine Murphy on 5/13/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include "Game.h"

Game::Game(const Board& b, Player* south, Player* north)
: m_board(b), m_southPlayer(south), m_northPlayer(north), m_whoseTurn(m_southPlayer), m_over(false)
{}
//Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.


void Game::display() const
{
    if (m_board.holes() <= 3)
        cout << "   ";
    else
        cout << "       ";
    cout << m_northPlayer->name() << endl; //North player name
    cout << "   ";
    
    int countSpaces = 1;
    for (int i = 1; i <= m_board.holes(); i++)           //North player holes
    {
        cout << beans(NORTH, i) << "  ";
        countSpaces += 3;
    }
    cout << endl;
    
    cout << " " << beans(NORTH, 0);             //North player pot
    int k = 0;
    while (k < countSpaces)
    {
        cout << " ";
        k++;
    }
    cout << beans(SOUTH, 0) << endl;     //South player pot
    cout << "   ";
    for (int i = 1; i <= m_board.holes(); i++)           //South player holes
    {
        cout << beans(SOUTH, i) << "  ";
    }
    cout << endl;
    
    if (m_board.holes() <= 3)
        cout << "   ";
    else
        cout << "        ";
    cout << m_southPlayer->name() << endl; //South player name
    
}
//Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.


void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    if (m_board.beansInPlay(NORTH) > 0 && m_board.beansInPlay(SOUTH) > 0)   //more moves are possible
    {
        over = false;
        return;
    }
    else                //one or both sides has 0 beans in play
    {
        over = true;
        if (beans(NORTH, 0) > beans(SOUTH, 0))
        {
            hasWinner = true;
            winner = NORTH;
        }
        else if (beans(SOUTH, 0) > beans(NORTH, 0))
        {
            hasWinner = true;
            winner = SOUTH;
        }
        else
            hasWinner = false;
    }
    
}
//If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else. Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.


bool Game::move()
{
    display();
    status(m_over, m_hasWinner, m_winner);
    if (m_over == true)
    {
        ///do any necessary sweeping
        if (m_board.beansInPlay(NORTH) == 0 && m_board.beansInPlay(SOUTH) != 0)
        {
            for (int i = 1; i <= m_board.holes(); i++)
                m_board.moveToPot(SOUTH, i, SOUTH);
            cout << "Sweeping the remaining beans into " << m_southPlayer->name() << "'s pot." << endl;
        }
        else if (m_board.beansInPlay(NORTH) != 0 && m_board.beansInPlay(SOUTH) == 0)
        {
            for (int i = 1; i <= m_board.holes(); i++)
                m_board.moveToPot(NORTH, i, NORTH);
            cout << "Sweeping the remaining beans into " << m_northPlayer->name() << "'s pot." << endl;
        }
        //update status
        status(m_over, m_hasWinner, m_winner);
        display();
        return false;
    }
    
    int hole = m_whoseTurn->chooseMove(m_board, turnSide(m_whoseTurn));
    int end = 0;
    Side s;
    if (!m_whoseTurn->isInteractive())
        cout << m_whoseTurn->name() << " chooses hole " << hole << endl;
    
    if (m_board.sow(turnSide(m_whoseTurn), hole, s, end) == true)
    {
        status(m_over, m_hasWinner, m_winner);
        if (m_over == true)                         //if that move ended the game
            return move();
        if (end == 0)           //if they landed in their own pot, go again
        {
            display();
            cout << m_whoseTurn->name() << " gets another turn." << endl;
            return move();
        }
        else if (s == turnSide(m_whoseTurn) && beans(s, end) == 1 && beans(notSide(m_whoseTurn), end) > 0)  //make a capture
        {
            m_board.moveToPot(notSide(m_whoseTurn), end, turnSide(m_whoseTurn));
            m_board.moveToPot(turnSide(m_whoseTurn), end, turnSide(m_whoseTurn));
        }
        
    }
    if (turnSide(m_whoseTurn) == SOUTH)                         //becomes other player's turn
        m_whoseTurn = m_northPlayer;
    else
        m_whoseTurn = m_southPlayer;
    return true;
}
//If the game is over, return false. Otherwise, make a complete move for the player whose turn it is (so that it becomes the other player's turn) and return true. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. If the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening.


void Game::play()
{
    m_play(false, 0);
}
//Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function. (Note: If when this function is called, South has no beans in play, so can't make the first move, sweep any beans on the North side into North's pot and act as if the game is thus over.)


int Game::beans(Side s, int hole) const
{
    return m_board.beans(s, hole);
}
//Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.


//Helper Functions

Side Game::turnSide(Player* turn)
{
    if (m_whoseTurn == m_southPlayer)
        return SOUTH;
    else
        return NORTH;
}

Side Game::notSide(Player* turn)
{
    if (m_whoseTurn == m_southPlayer)
        return NORTH;
    else
        return SOUTH;
}

Player* Game::playerSide(Side s)
{
    if (s == SOUTH)
        return m_southPlayer;
    else
        return m_northPlayer;
}

void Game::m_play(bool s, int k)
{
    if (!m_northPlayer->isInteractive() && !m_southPlayer->isInteractive()) //if neither player is interactive
    {
        if (move())
        {
            if (s)
            {
                cout << "Press ENTER ";                                 //checking periodically
                if (k == 1)
                {
                    string enter;
                    getline(cin, enter);
                }
                cin.ignore(10000, '\n');
                cout << endl;
            }
            m_play(!s, k+1);
        }
        else{
            if (m_hasWinner == false)
                cout << "The game resulted in a tie." << endl;
            else
                cout << "The winner is " << playerSide(m_winner)->name() << "." << endl;
        }
        
    }
    else        //at least one of the players is interactive
    {
        if (move())
            m_play(!s, k+1);
        else{
            if (m_hasWinner == false)
                cout << "The game resulted in a tie." << endl;
            else
                cout << "The winner is " << playerSide(m_winner)->name() << "." << endl;
        }
    }
    
    return;
}
