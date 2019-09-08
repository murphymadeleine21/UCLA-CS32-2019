//
//  mazestack.cpp
//  CS 32 HW 2
//
//  Created by Madeleine Murphy on 4/26/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include <stdio.h>
#include <stack>
#include <iostream>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

 bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

/*
 Push the starting coordinate (sr,sc) onto the coordinate stack and
 update maze[sr][sc] to indicate that the algorithm has encountered
 it (i.e., set maze[sr][sc] to have a value other than '.').
 While the stack is not empty,
 {   Pop the top coordinate off the stack. This gives you the current
 (r,c) location that your algorithm is exploring.
 If the current (r,c) coordinate is equal to the ending coordinate,
 then we've solved the maze so return true!
 Check each place you can move from the current cell as follows:
 If you can move SOUTH and haven't encountered that cell yet,
 then push the coordinate (r+1,c) onto the stack and update
 maze[r+1][c] to indicate the algorithm has encountered it.
 
 
 If you can move WEST and haven't encountered that cell yet,
 then push the coordinate (r,c-1) onto the stack and update
 maze[r][c-1] to indicate the algorithm has encountered it.
 
 
 If you can move NORTH and haven't encountered that cell yet,
 then push the coordinate (r-1,c) onto the stack and update
 maze[r-1][c] to indicate the algorithm has encountered it.
 
 
 If you can move EAST and haven't encountered that cell yet,
 then push the coordinate (r,c+1) onto the stack and update
 maze[r][c+1] to indicate the algorithm has encountered it.
 }
 There was no solution, so return false
 */



 bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    stack <Coord> coords;
    Coord a(sr, sc);
    
    coords.push(a);
    maze[sr][sc] = 'E';
    
    while (!coords.empty())
    {
        Coord current = coords.top();       //put coordinates into a new current coord
    
        coords.pop();                       //pop the top coordinate of the stack
        
        int r = current.r();                //the coordiantes that we are looking at right now
        int c = current.c();
        
        if (sr == er && sc == ec)               //if first coordinate is the end, you're done!
            return true;
        
        if (r == er && c == ec)                 //if current coordinate is the end, you're done!
            return true;
        
        //Check South
        if (maze[r+1][c] == '.')                //if we can move south and have not encountered it yet
        {
            Coord s(r+1, c);
            coords.push(s);                     //push coordinate onto stack
            maze[r+1][c] = 'E';                 //update maze
        }
        
        //Check West
        if (maze[r][c-1] == '.')                //if we can move west and have not encountered it yet
        {
            Coord w(r, c-1);
            coords.push(w);                     //push coordinate onto stack
            maze[r][c-1] = 'E';                 //update maze
        }
        
        //Check North
        if (maze[r-1][c] == '.')                //if we can move north and have not encountered it yet
        {
            Coord n(r-1, c);
            coords.push(n);                     //push coordinate onto stack
            maze[r-1][c] = 'E';                 //update maze
        }
        
        //Check East
        if (maze[r][c+1] == '.')                //if we can move east and have not encountered it yet
        {
            Coord e(r, c+1);
            coords.push(e);                     //push coordinate onto stack
            maze[r][c+1] = 'E';                 //update maze
        }
        
    }
    return false;
    
}




