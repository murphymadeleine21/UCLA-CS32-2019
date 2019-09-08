//
//  diff.cpp
//  Project 4
//
//  Created by Madeleine Murphy on 6/2/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include <stdio.h>
#include "hash.h"
#include <iostream>
#include <fstream>
#include <sstream>  // for istringstream and ostringstream
#include <string>
#include <cassert>
#include <algorithm>
#include <iterator>
using namespace std;


void createDiff(istream& fold, istream& fnew, ostream& fdiff);
bool applyDiff(istream& fold, istream& fdiff, ostream& fnew);
bool getCommand(istream& inf, char& cmd, int& length, int& offset);
bool getInt(istream& inf, int& n);

void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
    
    if (!fold)          //is this necessary?
        return;
    
    char s;
    string infile;
    while (fold.get(s))        //read contents of old file into a string
    {
        infile += s;
    }
    //cerr << infile << endl;
    
    char x;
    string newfile;
    while (fnew.get(x))        //read contents of new file into a string
    {
        newfile += x;
    }
    //cerr << newfile << endl;
    
    int bucketLength = 8;
    if (newfile.size() < 1000)
        bucketLength = 8;
    else if (newfile.size() > 1000 && newfile.size() < 5000)
        bucketLength = 12;
    else
        bucketLength = 16;

    HashTable original;
    unsigned long maxChunks = infile.size() - bucketLength + 1;
    for (unsigned int i = 0; i < maxChunks; i++)     //put every 8 bytes of original string in hash table
    {
        string bucket(infile, i, bucketLength);
        original.add(bucket, i);                //adding to the hash table
    }
    
    bool found;
    //process new files string
    for (int i = 0; i < newfile.size(); i++)
    {
        string match = "";
        vector<int> pos;
        for (int j = i; j < i+bucketLength && j < newfile.size(); j++) //add N bytes to our match string
        {
            match += newfile[j];
        }
        found = false;
        original.search(match, found, pos);
        if (found == true)
        {
            //determine how long the match goes on
            int maxLength = bucketLength;
            int maxPos = pos[0];
            if (pos.size() > 300)     //helps with files like strange that don't have a lot of variability
            {
                int k = i + bucketLength;
                int n = maxPos + bucketLength;
                while (k < newfile.size() && n < infile.size() && newfile[k] == infile[n])
                {
                    maxLength++;
                    k++;
                    n++;
                }
            }
            else
            {
                for (auto r = pos.begin(); r != pos.end(); r++)     //run through every possible match position
                {
                    int length = bucketLength;
                    int k = i + bucketLength;
                    int n = *r + bucketLength;
                    while (k < newfile.size() && n < infile.size() && newfile[k] == infile[n])
                    {
                        length++;       //increment how long the match goes on
                        k++;
                        n++;
                    }
                    if (length >= maxLength){       //find the match that is the longest
                        maxLength = length;
                        maxPos = *r;
                    }
                    
                }
            }
            //write a Copy instruction to the diff file to copy length bytes from offset pos from the source file
            fdiff << "C" << maxLength << "," << maxPos;
            //cerr << "C" << length << "," << pos;
            i += maxLength-1;      //account for the i++
        }
        else
        {
            
            int length = 1;
            int j = i;
            while (found == false && j < newfile.size()-1)      //find the next position that has an 8 byte match
            {
                j++;
                string nextMatch = "";
                for (int k = j; k < j+bucketLength && k < newfile.size(); k++)
                    nextMatch += newfile[k];
                found = false;
                original.search(nextMatch, found, pos);
                length++;
            }
            //add up to next match or up to end of file if no more matches are present
            string add;
            if (found == true)
            {
                length--;
                for (int k = 0; k < length; k++)
                    add += newfile[k+i];
                fdiff << "A" << length << ":" << add;
               // cerr << "A" << length << ":" << add;
                i += length-1;      //account for the i++
            }
            else
            {
                for (int k = 0; k < length; k++)
                    add += newfile[k+i];
                fdiff << "A" << length << ":" << add;
                //cerr << "A" << length << ":" << add;
                i += length-1;      //account for the i++
            }
        }
    }
   // cerr<< endl;
    
}

bool getInt(istream& inf, int& n)
{
    char ch;
    if (!inf.get(ch)  ||  !isascii(ch)  ||  !isdigit(ch))
    {
        inf.unget();
        return false;
    }
    inf.unget();
    inf >> n;
    return true;
}

bool getCommand(istream& inf, char& cmd, int& length, int& offset)
{
   // cerr << "Command is" << cmd << endl;
    
    if (!inf.get(cmd))
    {
        cmd = 'x';  // signals end of file
        return true;
    }
    char ch;
    switch (cmd)
    {
        case 'A':
            return getInt(inf, length) && inf.get(ch) && ch == ':';
        case 'C':
            return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);
        case '\r':
        case '\n':
            return true;
    }
    return false;
}

bool applyDiff(istream& fold, istream& fdiff, ostream& fnew)
{
    char s;
    string oldfile;
    while (fold.get(s))        //read contents of old file into a string
    {
        oldfile += s;
    }
  //  cerr << oldfile << endl;
    
    char x;
    string diff;
    while (fdiff.get(x))        //read contents of diff file into a string
    {
        diff += x;
    }
   // cerr << diff << endl;
    
    fdiff.clear();
    fdiff.seekg(0);
    for (int i = 0; i < diff.size(); i++)
    {
        
        char command = diff[i];
        int length;
        int offset;
        //cerr << "Command is " << command << endl;
        if (getCommand(fdiff, command, length, offset))
        {
            if (command == 'C') //copy instruction
            {
            if (!isdigit(diff[i+1]))                           //if the charactter following 'C' is not a len digit, false
                return false;
            i++;
            while (isdigit(diff[i]))        //move thru the len
                i++;
            if (diff[i] != ',' && diff[i] != '\n')  //should be followed by ','
                return false;
            while (diff[i] == ',' || diff[i] == '\n') //do nothing
                i++;
            if (!isdigit(diff[i]))              //should be offset
                return false;
            while (isdigit(diff[i]))        //move thru the offset
                    i++;
                i--; //for when we hit next character

//
//            if (offset >= oldfile.size())       //cannot copy from an offset past the end
//                return false;
//

                for (int r = offset; r - offset < length; r++)
                {
                    if (oldfile[r] == '\0'){
                        break;
                    }
                    fnew << oldfile[r];
                   // cerr << oldfile[r];
                }
                
            }
            else if (command == 'A') //add instruction
            {
                i++;
                if (!isdigit(diff[i]))                   //if the charactter following 'A' is not a len digit, false
                    return false;
                while (isdigit(diff[i]))        //move thru the len
                    i++;
                if (diff[i] != ':' && diff[i] != '\n')  //should be followed by ':'
                    return false;
                while (diff[i] == ':')
                    i++;
                
                for (int k = 0; k < length; k++)
                {
                    fnew << diff[i];                    //output the added sequence
                    //cerr << diff[i];
                    i++;
                }
                fdiff.clear();
                fdiff.seekg(i);
                i--;
                
                
            }
            else if (command == '\n' || command == '\r')
            {
                //do nothing
            }
            
        }
    }
    return true;
}

bool runtest(string oldName, string newName, string diffName, string newName2)
{
    if (diffName == oldName  ||  diffName == newName  ||
        newName2 == oldName  ||  newName2 == diffName  ||
        newName2 == newName)
    {
        cerr << "Files used for output must have names distinct from other files" << endl;
        return false;
    }
    ifstream oldFile(oldName, ios::binary);
    if (!oldFile)
    {
        cerr << "Cannot open " << oldName << endl;
        return false;
    }
    ifstream newFile(newName, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName << endl;
        return false;
    }
    ofstream diffFile(diffName, ios::binary);
    if (!diffFile)
    {
        cerr << "Cannot create " << diffName << endl;
        return false;
    }
    createDiff(oldFile, newFile, diffFile);
    diffFile.close();
    
    oldFile.clear();   // clear the end of file condition
    oldFile.seekg(0);  // reset back to beginning of the file
    ifstream diffFile2(diffName, ios::binary);
    if (!diffFile2)
    {
        cerr << "Cannot read the " << diffName << " that was just created!" << endl;
        return false;
    }
    ofstream newFile2(newName2, ios::binary);
    if (!newFile2)
    {
        cerr << "Cannot create " << newName2 << endl;
        return false;
    }
    assert(applyDiff(oldFile, diffFile2, newFile2));
    newFile2.close();
    
    newFile.clear();
    newFile.seekg(0);
    ifstream newFile3(newName2, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName2 << endl;
        return false;
    }
    if ( ! equal(istreambuf_iterator<char>(newFile), istreambuf_iterator<char>(),
                 istreambuf_iterator<char>(newFile3), istreambuf_iterator<char>()))
    {
        
        cerr << newName2 << " is not identical to " << newName
        << "; test FAILED" << endl;
        return false;
    }
    return true;
}
int main()
{
//    ifstream o("/Users/MurphyMadeleine17/Desktop/warandpeace1.txt");
//    ifstream p("/Users/MurphyMadeleine17/Desktop/warandpeace2.txt");
//    ofstream n("/Users/MurphyMadeleine17/Desktop/diff.txt");
//    createDiff(o, p, n);
   assert(runtest("/Users/MurphyMadeleine17/Desktop/greeneggs1.txt", "/Users/MurphyMadeleine17/Desktop/greeneggs2.txt", "/Users/MurphyMadeleine17/Desktop/diff.txt", "/Users/MurphyMadeleine17/Desktop/new.txt"));
    //assert(runtest("strange1.txt", "strange2.txt", "diff.txt", "new.txt"));

    cerr << "Test PASSED" << endl;
}
