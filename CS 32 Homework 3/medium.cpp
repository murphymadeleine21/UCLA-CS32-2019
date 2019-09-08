//
//  medium.cpp
//  CS 32 Homework 3
//
//  Created by Madeleine Murphy on 5/4/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//



//Your declarations and implementations would go here

class Medium
{
public:
    Medium (string id)
    {
        m_id = id;
    }
    virtual string connect() const = 0;
    string id() const
    {
        return m_id;
    }
    virtual string transmit(string msg) const
    {
        string s = "text: ";
        s += msg;
        return s;
    }
    virtual ~Medium()
    {
        cout << m_id << "." << endl;
    }
private:
    string m_id;
};

class TwitterAccount : public Medium
{
public:
    TwitterAccount(string id) : Medium(id)
    {}
    string connect() const
    {
        return "Tweet";
    }
    ~TwitterAccount()
    {
        cout << "Destroying the Twitter account ";
    }
};


class Phone : public Medium
{
public:
    Phone(string id, CallType n) : Medium(id)
    {
        m_call = n;
    }
    string connect() const
    {
        return "Call";
    }
    string transmit(string msg) const
    {
        if (m_call == VOICE)
        {
            string s = "voice: ";
            s += msg;
            return s;
        }
        else{
            string s = "text: ";
            s += msg;
            return s;
        }
    }
    ~Phone()
    {
        cout << "Destroying the phone ";
    }
private:
    CallType m_call;
};


class EmailAccount : public Medium
{
public:
    EmailAccount(string id) : Medium(id)
    {}
    string connect() const
    {
        return "Email";
    }
    ~EmailAccount()
    {
        cout << "Destroying the email account ";
    }
};

 


