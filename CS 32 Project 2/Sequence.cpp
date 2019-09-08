//
//  Sequence.cpp
//  CS 32 Project 2
//
//  Created by Madeleine Murphy on 4/18/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//


#include "Sequence.h"

Sequence::Sequence()
{
    head = nullptr;     //create an empty linked list
    tail = nullptr;     //set tail to nullptr also?
    
    m_size = 0;
}

int Sequence::size() const
{
    return m_size;
}

bool Sequence::empty() const
{
    return (m_size == 0);
    
}


Sequence::~Sequence()
{
    Node *p;
    p = head;
    while (p != nullptr)            //delete every node in the list
    {
        Node *n = p->m_next;
        delete p;
        p = n;
    }
}

Sequence::Sequence(const Sequence& other)
{
    if (other.head == nullptr)      //if empty list
    {
        head = nullptr;
        tail = nullptr;
        m_size = 0;
    }
    else
    {
        head = nullptr;             //make sure we make it an empty list
        tail = nullptr;
        m_size = 0;
        ItemType p;
        for (int i = 0; i < other.m_size; i++)      //add items to the list
        {
            other.get(i, p);
            addToRear(p);
        }
        m_size = other.m_size;
    }
    //return someSeq;

}


Sequence& Sequence::operator=(const Sequence& rhs)
{
    if (this != &rhs)
    {
        Sequence temp(rhs);
        swap(temp);
    }
    return *this;
}

int Sequence::insert(int pos, const ItemType& value)
{
    if (pos < 0 || pos > size())
        return -1;
    
    else if (pos == 0)          //if we're adding to the front
        addToFront(value);
    
    else if (pos == size())     //if we're adding to the back
        addToRear(value);
    
    else
        addItem(pos, value);
    
    return pos;
}

int Sequence::insert(const ItemType& value)
{
    if (head == nullptr)
        addToFront(value);
    
    else if (head->data >= value)        //check if belongs as the first value
    {
        addToFront(value);
        return 0;
    }
    
    else{
        Node *p;
        int counter = 1;
                                            //we want to find the position one above
        for (p = head; p != nullptr && p->m_next != nullptr && value > p->m_next->data; p = p->m_next)
            counter++;

        addItem(counter, value);
        return counter;
    }
    return 0;
}

bool Sequence::erase(int pos)
{
    if (pos < 0  ||  pos >= size())
        return false;
    if (head == nullptr)                            //can't erase if any of these conditions are met
        return false;
    
    return (deleteItem(pos));                       //helper function
}

int Sequence::remove(const ItemType& value)
{
    if (head == nullptr)
        return 0;
    
    Node *p = head;
    int counter = 0;
    int pos = 0;
    while (p != nullptr)
    {
        if (p->data == value)
        {
            p = p->m_next;
            erase(pos);                 //if we find one that matches, delete it & increase counter
            counter++;                  //remember that the next element now becomes this position
            pos--;
        }
        else
            p = p->m_next;
        pos++;
    }
    return counter;                                 //return number of items removed
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0  ||  pos >= size())
        return false;
    
    if (head == nullptr)
        return false;
    
    Node *p;
    int counter = 0;
    for (p = head; p != nullptr; p = p->m_next)     //locate the position and get p to point at it
    {
        if (counter == pos){
            value = p->data;                                //copy the data
            return true;
        }
        counter++;
    }
    
    return false;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0  ||  pos >= size())
        return false;
    
    if (head == nullptr)
        return false;
    
    Node *p;
    int counter = 0;
    for (p = head; p != nullptr; p = p->m_next)     //locate the position and get p to point at it
    {
        if (counter == pos)
            break;
        counter++;
    }
    p->data = value;                                //copy the data
    return true;
}

int Sequence::find(const ItemType& value) const
{
    Node *p;
    int counter = 0;
    for (p = head; p != nullptr; p = p->m_next)
    {
        if (p->data == value)
            return counter;
        counter++;
    }
    return -1;
}

void Sequence::swap(Sequence& other)
{
    // Swap elements.  Since the only elements that matter are those up to
    // m_size and other.m_size, only they have to be moved.
    
    Node *h = head;     //temporary pointers
    Node *t = tail;
    
    head = other.head;      //swap the heads and tails
    tail = other.tail;
    
    other.head = h;
    other.tail = t;
    
    int tempSize = m_size;      //swap the sizes
    m_size = other.m_size;
    other.m_size = tempSize;
}

void Sequence::addItem(int pos, const ItemType& value)
{
    if (head == nullptr)
        addToFront(value);
    
    else if (pos == 0)          //double check that it doesnt belong at front? might not need later
        addToFront(value);
    
    else if (pos == size())     //if position is the last position (should maybe be size+1?)
        addToRear(value);
    
    else        //node goes in the middle of the list
    {
        int counter = 0;            //position
        Node *p = head;             //start at the first node
        while (p != nullptr)
        {
            if (counter == pos-1)     //find the node above it
                break;
            counter++;              //counter lets us know what position we are at
            p = p->m_next;            //we move down the line until we find the right position
        }
        
        if (p->m_next == nullptr)       //check that p->m_next is not a nullptr
            addToRear(value);
        else
        {
            Node *latest = new Node;            //make a new node
            latest->data = value;               //put value in node
            latest->m_next = p->m_next;         //give latest a pointer to what p pointed to
            if (latest->m_next->m_prev != nullptr)  //don't access a nullptr
                latest->m_next->m_prev = latest;    //update next objects previous
            latest->m_prev = p;                 //new nodes previous becomes prior node
            p->m_next = latest;                 //now point p to new node
            m_size++;
        }
    }
}

void Sequence::addToFront(const ItemType& value)
{
    Node *p;                    //make a new pointer to a node
    p = new Node;               //make a new node
    p->data = value;            //put value in node
    
    if (head == nullptr)
    {
        p->m_next = head;   //if list is empty will this set next to nullptr
        p->m_prev = nullptr;
        head = p;       //link head pointer to nw top node
        tail = p;
    }
    else
    {
        p->m_next = head;   //if list is empty will this set next to nullptr
        p->m_prev = nullptr;
        p->m_next->m_prev = p;
        head = p;       //link head pointer to nw top node
    }
    
    m_size++;
}

void Sequence::addToRear(const ItemType& value)
{
    if (head == nullptr || tail == nullptr)
        addToFront(value);
    else
    {
        Node *n;                //create a new pointer to a node
        n = new Node;           //create a new node
        n->data = value;        //set that nodes data to value
        n->m_next = nullptr;    //last always nullptr
        n->m_prev = tail;       //n's previous will point to what tail is pointing to
        tail->m_next = n;         //tail now points to this node
        tail = n;               //link tail to new node HOW IS THIS DIFF FROM tail->next = n???
        
        m_size++;
    }
}


bool Sequence::deleteItem(int pos)
{
    
    if (pos == 0)                   //if we are deleting the first node
    {
        if (m_size > 1){
        Node *killMe = head;
        head = killMe->m_next;
        killMe->m_next->m_prev = nullptr;   //first item in the list has a nullptr for previous
        delete killMe;                  //do we delete this or will the destructor take care of this?
        m_size--;
        return true;
        }
        else
        {
            Node *killMe = head;
            head = killMe->m_next;
            killMe->m_prev = nullptr;   //first item in the list has a nullptr for previous
            delete killMe;                  //do we delete this or will the destructor take care of this?
            m_size--;
            return true;
        }
            
    }
    
    else
    {
        int counter = 0;            //position
        Node *p = head;             //start at the first node
        while (p != nullptr)
        {
            if (counter == pos-1)     //find the node above it
                break;
            counter++;              //counter lets us know what position we are at
            p = p->m_next;            //we move down the line until we find the right position
        }
        if (p->m_next->m_next != nullptr)
        {
            Node *killMe = p->m_next;
            p->m_next = killMe->m_next;
            killMe->m_next->m_prev = killMe->m_prev;
            delete killMe;
            m_size--;
            return true;
        }
        else if (p->m_next->m_next == nullptr)       //if it is the last last element in the list
        {
            Node *killMe = p->m_next;
            p->m_next = nullptr;            //make this element the last element now
            tail = p;
            delete killMe;
            m_size--;
            return true;
        }
    }
    return false;
}


int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if (seq1.empty()|| seq2.empty())
        return -1;
    
    if (seq1.size() < seq2.size())
        return -1;
    
    
    if (seq1.size() == seq2.size())
    {
        ItemType p;
        ItemType r;
        for (int k = 0; k < seq1.size(); k++)  //if we have the case where they are same length, every position must match
        {
            seq1.get(k,p);
            seq2.get(k,r);
            if (!(p == r))
                return -1;
        }
        return 0;
    }
    
    for (int k = 0; k <= seq1.size(); k++)
    {
        ItemType a;
        ItemType b;
        seq1.get(k, a);
        seq2.get(0, b);
        if (a == b)                     //find the first time of seq1 = first element of seq2
        {
            int initial = k;
            int i = 1;
            
            for (int j = k+1; j < (seq2.size()+initial); j++)
            {
                seq1.get(j, a);
                seq2.get(i, b);
                if (a != b)             //if they are not the same until seq2 is over, return -1
                {
                    initial = -1;
                    break;
                }
                i++;
            }
            return initial;
        }
    }
    
    return -1;
}



void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    Sequence temp;          //make an empty sequence, protect against alias
    
    if (seq1.empty() && !(seq2.empty()))            //if seq1 is empty, copy seq2 into result
    {
            for (int i = 0; i < seq2.size(); i++)
            {
                ItemType p;                         //use get and insert!
                seq2.get(i, p);
                temp.insert(i, p);
            }
    }
    
    else if (seq2.empty() && !(seq1.empty()))  //if seq2 is empty, copy seq1 into result
    {
            for (int i = 0; i < seq1.size(); i++)
            {
                ItemType p;
                seq1.get(i, p);
                temp.insert(i, p);
            }
    
    }
    
    else if (!seq1.empty() && !seq2.empty())    //if neither are empty
    {
        if (seq1.size() == seq2.size())         //if theyre equal in size
        {
            int counter = 0;
            for (int i = 0; i < seq1.size(); i++)
            {
                ItemType a;
                ItemType b;
                seq1.get(i, a);
                seq2.get(i, b);
                temp.insert(counter, a);
                counter++;
                temp.insert(counter, b);
                counter++;
            }
        }
        
        else if (seq1.size() < seq2.size())         //if seq2 is bigger
        {
            int pos = 0;
            int counter = 0;
            for (int i = 0; i < seq1.size(); i++)       //until we reach end of seq1
            {
                ItemType a;
                seq1.get(i, a);
                temp.insert(pos, a);
                pos++;
                ItemType b;
                seq2.get(i, b);
                temp.insert(pos, b);
                pos++;
                counter++;
            }
            for (int j = counter; j < seq2.size(); j++) //add rest of seq2
            {
                ItemType a;
                seq2.get(j, a);
                temp.insert(pos, a);
                pos++;
            }
        }
            
        else if (seq2.size() < seq1.size())         //if seq 1 is bigger
        {
            int pos = 0;
            int counter = 0;
            for (int i = 0; i < seq2.size(); i++)   //until we reach end of seq2
            {
                ItemType a;
                seq1.get(i, a);
                temp.insert(pos, a);
                pos++;
                ItemType b;
                seq2.get(i, b);
                temp.insert(pos, b);
                pos++;
                counter++;
            }
            for (int j = counter; j < seq1.size(); j++) //add rest of seq1
            {
                ItemType a;
                seq1.get(j, a);
                temp.insert(pos, a);
                pos++;
            }
        }
    }
    result.swap(temp);          //swap temp with result
}
















