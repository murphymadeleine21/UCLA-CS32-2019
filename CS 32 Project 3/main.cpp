//
//  main.cpp
//  CS 32 Project 3
//
//  Created by Madeleine Murphy on 5/13/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include <iostream>
#include <cassert>
using namespace std;

#include "Board.h"
#include "Player.h"
#include "Game.h"

void doBoardTests()
{
    Board b(3, 2);
    assert(b.holes() == 3  &&  b.totalBeans() == 12  &&
           b.beans(SOUTH, POT) == 0  &&  b.beansInPlay(SOUTH) == 6);
    b.setBeans(SOUTH, 1, 1);
    b.moveToPot(SOUTH, 2, SOUTH);
    assert(b.totalBeans() == 11  &&  b.beans(SOUTH, 1) == 1  &&
           b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  &&
           b.beansInPlay(SOUTH) == 3);
    Side es;
    int eh;
    b.sow(SOUTH, 3, es, eh);
    assert(es == NORTH  &&  eh == 3  &&  b.beans(SOUTH, 3) == 0  &&
           b.beans(NORTH, 3) == 3  &&  b.beans(SOUTH, POT) == 3  &&
           b.beansInPlay(SOUTH) == 1  &&  b.beansInPlay(NORTH) == 7);
}

void doGameTests()
{
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Board b(3, 0);
    b.setBeans(SOUTH, 1, 2);
    b.setBeans(NORTH, 2, 1);
    b.setBeans(NORTH, 3, 2);
    Game g(b, &bp1, &bp2);
    bool over;
    bool hasWinner;
    Side winner;
    //    Homer
    //   0  1  2
    // 0         0
    //   2  0  0
    //    Bart
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
           g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    
    g.move();
    //   0  1  0
    // 0         3
    //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
    
    g.move();
    //   1  0  0
    // 0         3
    //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
           g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
    
    g.move();
    //   1  0  0
    // 0         3
    //   0  0  1
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
           g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);
    
    g.move();
    //   0  0  0
    // 1         4
    //   0  0  0
    g.status(over, hasWinner, winner);
    assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    assert(hasWinner && winner == SOUTH);
}

void doPlayerTests()
{
    HumanPlayer hp("Marge");
    assert(hp.name() == "Marge"  &&  hp.isInteractive());
    BadPlayer bp("Homer");
    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
    SmartPlayer sp("Lisa");
    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
    Board b(3, 2);
    b.setBeans(SOUTH, 2, 0);
    cout << "=========" << endl;
    int n = hp.chooseMove(b, SOUTH);
    cout << "=========" << endl;
    assert(n == 1  ||  n == 3);
    n = bp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
    n = sp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
}
int main()
{
    //Testing Board Constructor//
    //Board(int nHoles, int nInitialBeansPerHole)
    Board h(3, 4);
    Board p(-1, -1);
    assert(h.holes() == 3);
    assert(p.holes() == 1);
    
    //Testing Board beans(Side s, int hole) const
    assert(h.beans(NORTH, 1) == 4);
    assert(h.beans(SOUTH, 1) == 4);
    assert(h.beans(NORTH, 0) == 0);
    assert(h.beans(SOUTH, 0) == 0);
    
    assert(p.beans(SOUTH, 0) == 0);
    assert(p.beans(NORTH, 0) == 0);
    assert(p.beans(NORTH, 1) == 0);
    assert(p.beans(SOUTH, 1) == 0);
    assert(p.beans(NORTH, 2) == -1);
    assert(p.beans(SOUTH, 2) == -1);
    
    //Testing beansInPlay
    assert(h.beansInPlay(NORTH) == 12);
    assert(h.beansInPlay(SOUTH) == 12);
    assert(p.beansInPlay(NORTH) == 0);
    assert(p.beansInPlay(NORTH) == 0);
    
    //Testing total beans
    assert(h.totalBeans() == 24);
    assert(p.totalBeans() == 0);
    
    
    //Testing Sow
    //sow(Side s, int hole, Side& endSide, int& endHole)
    Side es;
    int eh;
    assert(h.sow(NORTH, 1, es, eh) == true);
    assert(es == SOUTH);
    assert(eh == 3);
    
    assert(h.sow(NORTH, 1, es, eh) == false);
    assert(h.sow(NORTH, 2, es, eh) == true);
    assert(es == SOUTH);
    assert(eh == 2);
    
    assert(h.sow(NORTH, 1, es, eh) == true);
    assert(es == NORTH);
    assert(eh == 0);
    
    assert(h.sow(SOUTH, 3, es, eh) == true);
    assert(es == SOUTH);
    assert(eh == 1);
    assert(h.sow(SOUTH, 3, es, eh) == false);
    
    assert(h.sow(NORTH, 2, es, eh) == true);
    assert(es == NORTH);
    assert(eh == 1);
    assert(h.sow(NORTH, 1, es, eh) == true);
    assert(es == SOUTH);
    assert(eh == 1);
    //Testing beans in play at the moment
    assert(h.beansInPlay(NORTH) == 5);
    assert(h.beansInPlay(SOUTH) == 14);
    
    assert(h.sow(SOUTH, 1, es, eh) == true);
    assert(es == SOUTH);
    assert(eh == 2);
    
    //Testing total beans to make sure it hasn't changed
    assert(h.totalBeans() == 24);
    
    //Testing beansInPlay atm
    assert(h.beansInPlay(NORTH) == 8);
    assert(h.beansInPlay(SOUTH) == 10);
    
    assert(h.sow(SOUTH, 3, es, eh) == true);
    assert(es == SOUTH);
    assert(eh == 0);
    
    //Testing beans in hole are correct
    assert(h.beans(SOUTH, 0) == 3);
    assert(h.beans(NORTH, 0) == 4);
    assert(h.beans(NORTH, 1) == 1);
    assert(h.beans(NORTH, 2) == 1);
    assert(h.beans(NORTH, 3) == 6);
    assert(h.beans(SOUTH, 1) == 1);
    assert(h.beans(SOUTH, 2) == 8);
    assert(h.beans(SOUTH, 3) == 0);
    
    //Testing moveToPot(Side s, int hole, Side potOwner)
    assert(h.moveToPot(SOUTH, 1, SOUTH) == true);
    assert(h.beans(SOUTH, 0) == 4);
    assert(h.beans(NORTH, 0) == 4);
    assert(h.moveToPot(NORTH, 1, NORTH) == true);
    assert(h.beans(NORTH, 0) == 5);
    assert(h.moveToPot(NORTH, 2, SOUTH) == true);
    assert(h.beans(SOUTH, 0) == 5);
    
    //Testing setBeans(Side s, int hole, int beans)
            //first test total and beans at play for reference
    assert(h.beansInPlay(NORTH) == 6);
    assert(h.beansInPlay(SOUTH) == 8);
    assert(h.totalBeans() == 24);
    assert(h.setBeans(SOUTH, 1, 1) == true);
    assert(h.totalBeans() == 25);
    assert(h.beansInPlay(SOUTH) == 9);
    assert(h.setBeans(SOUTH, 2, 4) == true);
    assert(h.totalBeans() == 21);
    assert(h.beansInPlay(SOUTH) == 5);
    
    doBoardTests();
    cerr << "Passed all Board Tests" << endl;
    
    //////Early Player Tests!!//////
    
    Board yo(3, 0);
    HumanPlayer hehe("hehe");
    assert(hehe.name() == "hehe");          //testing name works with constructor inheritance
    assert(hehe.isInteractive());           //testing isInteractive
    
    BadPlayer oof("oof");
    assert(oof.name() == "oof");
    assert(!oof.isInteractive());
    assert(oof.chooseMove(yo, NORTH) == -1 && oof.chooseMove(yo, SOUTH) == -1); //testing badplayer has no moves
    
    yo.setBeans(NORTH, 1, 1);
    //assert(hehe.chooseMove(yo, NORTH) == 1);    //testing prompting until valid move
    assert(oof.chooseMove(yo, NORTH) == 1 && oof.chooseMove(yo, SOUTH) == -1);      //bad player now has one move it can make
    
    
    doPlayerTests();
    HumanPlayer hp("Marge");        //some of smallberg's player tests
    assert(hp.name() == "Marge"  &&  hp.isInteractive());
    BadPlayer bp("Homer");
    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
    SmartPlayer sp("Lisa");
    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
    Board b(3, 2);
    b.setBeans(SOUTH, 2, 0);
    cout << "=========" << endl;
    int n = hp.chooseMove(b, SOUTH);
    cout << "=========" << endl;
    assert(n == 1  ||  n == 3);
    n = bp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);

    cerr << "Passed all Player Tests" << endl;
    
    
    /////Game Tests/////
    Game li(b, &hp, &bp);
    Board c(6, 2);
    Game e(c, &hp, &bp);
    Board a(2, 2);
    Game o(a, &hp, &bp);
    //g.display();
    e.display();                    //testing that the display is working correctly
    o.display();
    li.play();
    
    BadPlayer bp2("Dan");               //two non interactive players against each other
    assert(bp2.name() == "Dan"  &&  !bp2.isInteractive());
    Game k(b, &bp, &bp2);
    k.play();

    HumanPlayer niko("Niko");       //played against some friends to see if it was working
    HumanPlayer mad("Maddie");
    HumanPlayer oli("Oliver");
    Board j(6, 3);
    Game yay(j, &niko, &mad);
    yay.play();
    Game dank(j, &oli, &mad);
  //  dank.play();
    doGameTests();      //smallberg's tests
    cout << "Passed all Game tests" << endl;
    
    
    /// SMART PLAYER TESTS!!! /////
    //Set up games where smartie has one obvious move that will cause it to win
    SmartPlayer smartie("smartie");
    Board w(3, 1);
    w.setBeans(SOUTH, 3, 0);
    w.setBeans(NORTH, 1, 0);
    w.setBeans(NORTH, 2, 0);
    /*
    0 0 1
   0     0
    1 1 0
     */
    Game goodluck(w, &smartie, &mad);
    assert(smartie.chooseMove(w, SOUTH) == 2);
    Board sm(3, 0);
    sm.setBeans(SOUTH, 1, 1);
    sm.setBeans(NORTH, 2, 2);
    /*
     0 2 0
    0     0
     1 0 0
     */
    Game test1(sm, &smartie, &mad);
    assert(smartie.chooseMove(sm, SOUTH) == 1);
    
    Board sm2(3, 0);
    sm2.setBeans(NORTH, 2, 2);
    sm2.setBeans(SOUTH, 1, 1);
    sm2.setBeans(SOUTH, 3, 1);
    /*
     0 2 0
    0     0
     1 0 1
     */
    Game test2(sm2, &smartie, &mad);
    assert(smartie.chooseMove(sm2, SOUTH) == 3 || smartie.chooseMove(sm2, SOUTH) == 1);
    test2.play();
    bool hasWinner;
    bool isOver;
    Side s;
    test2.status(isOver, hasWinner, s);
    assert(isOver == true && hasWinner == true && s == SOUTH);
    
    Board sm3(4, 0);
    sm3.setBeans(NORTH, 2, 1);
    sm3.setBeans(SOUTH, 3, 2);
    sm3.setBeans(SOUTH, 4, 1);
    /*
     0 1 0 0
    0       0
     0 0 2 1
     */
    Game test3(sm3, &smartie, &mad);
    assert(smartie.chooseMove(sm3, SOUTH) == 4);
    test3.play();
    test3.status(isOver, hasWinner, s);
    assert(isOver == true && hasWinner == true && s == SOUTH);
    
    //This tests that smartie will recognize other player's countermove as well
    Board sm4(4, 0);
    sm4.setBeans(NORTH, 3, 1);
    sm4.setBeans(SOUTH, 1, 1);
    sm4.setBeans(SOUTH, 3, 1);
    /*
     0 0 1 0
    0       0
     1 0 1 0
     */
    Game test4(sm4, &smartie, &mad);
    assert(smartie.chooseMove(sm4, SOUTH) == 3);
    test4.play();
    test4.status(isOver, hasWinner, s);
    assert(isOver == true && hasWinner == true && s == SOUTH);
    
    Board sm5(6, 0);
    sm5.setBeans(NORTH, 4, 2);
    sm5.setBeans(SOUTH, 3, 1);
    sm5.setBeans(SOUTH, 5, 2);
    /*
     0 0 0 2 0 0
    0           0
     0 0 1 0 2 0
     */
    Game test5(sm5, &smartie, &mad);
    assert(smartie.chooseMove(sm5, SOUTH) == 5 || smartie.chooseMove(sm5, SOUTH) == 3);
    test5.play();
    test5.status(isOver, hasWinner, s);
    assert(isOver == true && hasWinner == true && s == SOUTH);
    
    /*
    0 2 0 0
   0       0
    1 0 1 0
     */
    Board sm7(4, 0);
    sm7.setBeans(NORTH, 2, 2);
    sm7.setBeans(SOUTH, 1, 1);
    sm7.setBeans(SOUTH, 3, 1);
    Game test7(sm7, &smartie, &mad);
    assert(smartie.chooseMove(sm7, SOUTH) == 1);
    
    /*
    1 0 1
   0     0
    3 2 1
     */
    //smartie chooses 3, then gets other moves til it wins
    Board sm9(3, 0);
    sm9.setBeans(NORTH, 1, 1);
    sm9.setBeans(NORTH, 3, 1);
    sm9.setBeans(SOUTH, 1, 3);
    sm9.setBeans(SOUTH, 2, 2);
    sm9.setBeans(SOUTH, 3, 1);
    Game test9(sm9, &smartie, &mad);
    cout << smartie.chooseMove(sm9, SOUTH) << endl;
    assert(smartie.chooseMove(sm9, SOUTH) == 3);
    
    /*
    0 0 1 1
   0       0
    1 0 0 0
     */
    Board hi(4, 0);
    hi.setBeans(NORTH, 3, 1);
    hi.setBeans(NORTH, 4, 1);
    hi.setBeans(SOUTH, 1, 1);
    Game hitest(hi, &mad, &smartie);
    hitest.play();      //smartie must choose 3 after maddie chooses 1, which it does
    
    Board sm6(6, 3);
    Game test6(sm6, &smartie, &mad);
    test6.play();
    
    Board sm8(6, 4);
    Game test8(sm8, &smartie, &mad);
    test8.play();
    
    Board sm10(6, 4);
    SmartPlayer smarter("smarter");
    Game test10(sm10, &smarter, &smartie);
    test10.play();
    cout << "Passed all Smart Player Tests" << endl;
    
}
