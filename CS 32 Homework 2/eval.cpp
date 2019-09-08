//
//  eval.cpp
//  CS 32 HW 2
//
//  Created by Madeleine Murphy on 4/28/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int convert(string infix, string& postfix);

int evaluate(string infix, string& postfix, bool& result);
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.

int evaluate(string infix, string& postfix, bool& result)
{
    if (convert(infix, postfix) != 1)
    {
        stack <bool> operand;
        
        for (int i = 0; i < postfix.size(); i++)
        {
            if (postfix.at(i) == 'T')   //operand
            {
                bool t = true;
                operand.push(t);
            }
            else if (postfix.at(i) == 'F')   //operand
            {
                bool f = false;
                operand.push(f);
            }
            
            else if (postfix.at(i) == '!')       //if it's a !
            {
                bool operand1 = operand.top();
                operand.pop();
                operand.push(!operand1);
            }
            else                            //it's an operator
            {
                bool operand2 = operand.top();
                operand.pop();
                bool operand1 = operand.top();
                operand.pop();
                
                if (postfix.at(i) == '&')
                {
                    operand.push(operand1&operand2);        //evaluate &, if both true == true, otherwise false
                }
                
                else if (postfix.at(i) == '^')
                {
                    bool t = true;
                    bool f = false;
                    if (operand1 != operand2)       //if they're exclusive, push true
                        operand.push(t);
                    else
                        operand.push(f);            //otherwise push false
                }
            }
        }
        
        result = operand.top();             //set result to the expression
        return 0;                           //return 0
    }
    else                                    //if invalid infix, return 1
        return 1;
}


int convert(string infix, string& postfix)
{
    postfix = "";
    stack<char> eval;
    
    for (int i = 0; i < infix.size(); i++)
    {
        switch (infix.at(i)) {
            case 'T':
            case 'F':
                if (i!= 0 && infix.at(i-1) ==  ')')      //cannot be ')' before T/F
                    return 1;
                if (i != infix.size()-1 && infix.at(i+1) == '(')       //cannot be '(' after T/F
                    return 1;
                if (i!= 0 && infix.at(i-1) ==  'T')                    //cannot be 'T' before T/F
                    return 1;
                if (i!= 0 && infix.at(i-1) ==  'F')                    //cannot be 'F' before T/F
                    return 1;
                if (i != infix.size()-1 && infix.at(i+1) == 'T')       //cannot be 'T' after T/F
                    return 1;
                if (i != infix.size()-1 && infix.at(i+1) == 'T')       //cannot be 'F' after T/F
                    return 1;
                postfix += infix.at(i);
                if (!eval.empty() && eval.top() == '!')
                {
                    postfix += eval.top();
                    eval.pop();
                }
                break;
            case '(':
                if (i+1 == infix.size())            //cannot come last
                    return 1;
                if (i != infix.size()-1 && infix.at(i+1) == ')')        //cannot be ()
                    return 1;
                eval.push(infix.at(i));
                break;
            case ')':
                if (eval.empty())               //if the stack is empty, we know there is not first (
                    return 1;
                while (!eval.empty() && eval.top() != '(')           //if we find (
                {
                    postfix += eval.top();      //append the stack top to postfix
                    eval.pop();                 //pop the stack
                }
                eval.pop();                     //remove the (
                while (!eval.empty() && eval.top() == '!')
                {
                    postfix += eval.top();      //if next top is a !, add that to postfix
                    eval.pop();
                }
                break;
            case '!':
                if (i+1 == infix.size())        //cannot be last item
                    return 1;
                if (i != 0 && i != infix.size() - 1)            //characters before and after cannot be letters, i.e. T!F
                {
                    if (infix.at(i-1) == 'T' || infix.at(i-1) == 'F')
                    {
                        if (infix.at(i+1) == 'T' || infix.at(i+1) == 'F')
                            return 1;
                    }
                }
                eval.push(infix.at(i));
                break;
            case '&':
                if (postfix == "")              ////if the postfix string is empty
                    return 1;
                if (i!= 0 && infix.at(i-1) == '(')          //cannot come after open parenthesis
                    return 1;
                if (i+1 == infix.size())        //cannot come last
                    return 1;
                if (i!= 0 && infix.at(i-1) == '&')   //cannot come after '&'
                    return 1;
                if (i != infix.size()-1 && infix.at(i+1) == '&') //cannot come before &
                    return 1;
                if (i!= 0 && infix.at(i-1) == '^')   //cannot come after '^'
                    return 1;
                if (i != infix.size()-1 && infix.at(i+1) == '^') //cannot come before ^
                    return 1;
                
                while (!eval.empty() && eval.top() != '(' && eval.top() != '^') //While the stack is not empty and the stack top is not '(' and precedence of ch <= precedence of stack top
                {
                    postfix += eval.top();      //add top to postfix
                    eval.pop();                 //pop the top
                }
                eval.push(infix.at(i));     //push ch onto stack
                break;
            case '^':
                if (postfix == "")              ////if the postfix string is empty
                    return 1;
                if (i!= 0 && infix.at(i-1) == '(')          //cannot come after open parenthesis
                    return 1;
                if (i+1 == infix.size())        //cannot come last
                    return 1;
                if (i!= 0 && infix.at(i-1) == '&')   //cannot come after '&'
                    return 1;
                if (i != infix.size()-1 && infix.at(i+1) == '&') //cannot come before &
                    return 1;
                if (i!= 0 && infix.at(i-1) == '^')   //cannot come after '^'
                    return 1;
                if (i != infix.size()-1 && infix.at(i+1) == '^') //cannot come before ^
                    return 1;
                
                while (!eval.empty() && eval.top() != '(') //While the stack is not empty and the stack top is not '(' and precedence of ch <= precedence of stack top (going to be <= to every operand)
                {
                    postfix += eval.top();
                    eval.pop();
                }
                eval.push(infix.at(i));     //push ch onto stack
                break;
            case ' ':
                break;
            default:
                return 1;
                break;
                
        }
    }
    while (!eval.empty())
    {
        if (eval.top() == '(')          //if we have a leftover (, we know it was an invalid expression
            return 1;
        
        postfix += eval.top();          //append the stack top to postfix
        eval.pop();                     //pop the stack
    }
    
    if (postfix == "")                  //if the postfix is empty not valid
        return 1;
    if (postfix.size() > 1)
    {
        for (int i = 0; i < postfix.size(); i++)
        {
            if (postfix.at(i) == '&' || postfix.at(i) == '^' || postfix.at(i) == '!')
            {
                return 0;
            }
            else if (postfix.at(i) != '&' && postfix.at(i) != '^' && postfix.at(i) != '!' && i + 1 == postfix.size())
                return 1;   //if the entire string does not have any operands, return 1
        }
    }
    
    return 0;
}


