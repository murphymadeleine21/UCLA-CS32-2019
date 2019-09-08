//
//  newSequence.cpp
//  newSequence hw
//
//  Created by Madeleine Murphy on 4/16/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include "newSequence.h"

Sequence::Sequence(int len)   // Create an empty sequence (i.e., one with no items)
{
    m_capacity = len;
    m_size = 0;
    m_sequence = new ItemType[m_capacity]; //+1??
}

Sequence::~Sequence()           //destructor deletes whole array of pointers
{
    delete [] m_sequence;
}

Sequence::Sequence(const Sequence& other)        //copy constructor
{
    m_capacity = other.m_capacity;
    m_size = other.m_size;
    m_sequence = new ItemType[m_capacity];
    for (int i = 0; i < m_capacity; i++)            //manually copy everything
    {
        m_sequence[i] = other.m_sequence[i];
    }
}

Sequence& Sequence::operator=(const Sequence& rhs) //assignment operator
{
    if(this != &rhs) //protect against the alias
    {
        delete []m_sequence;
        m_capacity = rhs.m_capacity;
        m_size = rhs.m_size;
        m_sequence = new ItemType[m_capacity];
        for (int i = 0; i < m_capacity; i++)
        {
            m_sequence[i] = rhs.m_sequence[i];
        }
    }
    return *this;
}

bool Sequence::empty() const // Return true if the sequence is empty, otherwise false.
{
    if (m_size == 0)
        return true;
    else
        return false;
}

int Sequence::size() const    // Return the number of items in the sequence.
{
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return pos if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// e.g., because it's implemented using a fixed-size array.)  Otherwise,
// leave the sequence unchanged and return -1.  Notice that
// if pos is equal to size(), the value is inserted at the end.
{
    if (pos > size() || pos < 0 || pos > m_capacity)
        return -1;
    
    for (int i = m_size+1; i >= pos; i--)               //move everything over 1
    {
        if (i > 0){                                     //check for out of bounds errors
            m_sequence[i] = m_sequence[i-1];
        }
    }
    m_sequence[pos] = value;                            //make that position of the sequence = value
    m_size++;
    return pos;
}

int Sequence::insert(const ItemType& value)
{
    int p = size();
    
    if (size() + 1 > m_capacity)         //if sequence is full return -1, can't add anything
        return -1;
    
    for (int i = 0; i < size(); i++)
    {
        if (value <= m_sequence[i]){                    //find where value <= sequence
            p = i;
            break;
        }
    }
    if (p != size()){
        for (int i = m_size+1; i >= p; i--)               //move everything over 1
        {
            if (i > 0){
                m_sequence[i] = m_sequence[i-1];
            }
        }
    }
    m_sequence[p] = value;                            //make that position of the sequence = value
    m_size++;
    return p;
}
// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).

bool Sequence::erase(int pos)
{
    if (0 <= pos && pos < size())
    {
        for (int i = pos; i < size(); i++){         //remove that item by moving everything over 1
            m_sequence[i] = m_sequence[i+1];
        }
        m_size--;                                   //decrement the size
        return true;
    }
    return false;
}
// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.

int Sequence::remove(const ItemType& value)
{
    int counter = 0;
    
    for (int i = 0; i < size(); i++){
        if (value == m_sequence[i]){
            erase(i);
            counter++;
        }
    }
    return counter;
}
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).

bool Sequence::get(int pos, ItemType& value) const
{
    if (0 <= pos && pos < size())
    {
        value = m_sequence[pos];
        return true;
    }
    return false;
}
// If 0 <= pos < size(), copy into value the item at position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.

bool Sequence::set(int pos, const ItemType& value)
{
    if (0 <= pos && pos < size())
    {
        m_sequence[pos] = value;
        return true;
    }
    return false;
}
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.

int Sequence::find(const ItemType& value) const
{
    int p = -1;
    for (int i = 0; i < size(); i++)
    {
        if (value == m_sequence[i]){
            p = i;
            break;
        }
    }
    return p;
}
// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.

void Sequence::swap(Sequence& other)
{
    Sequence temp = other;
    other = *this;
    *this = temp;
}
// Exchange the contents of this sequence with the other one.

