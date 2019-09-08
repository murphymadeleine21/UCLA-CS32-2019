//
//  linear.cpp
//  CS 32 Homework 3
//
//  Created by Madeleine Murphy on 5/7/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    if (n < 0) return false;
    if (n == 0) return true;
    if (n == 1) return somePredicate(a[n-1]);
    
    bool first = allTrue(a, n/2);
    bool second = allTrue(a + n/2, n - n/2);
    
    return (first == true && second == true);
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
    int counter = 0;
    if (n <= 0) return 0;
    if (n == 1)
    {
        if (somePredicate(a[n-1]) == false)
            counter++;
        return counter;
    }
    
    int first = countFalse(a, n/2);
    int second = countFalse(a + n/2, n - n/2);
    
    return first + second;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
    int pos = 0;
    if (n <= 0) return -1;
    if (n == 1)
    {
        if (somePredicate(a[n-1]) == false)
            return pos;
        pos++;
        return -1;
    }
    
    int first = firstFalse(a, n/2);
    int second = firstFalse(a + n/2, n - n/2);
    if (first == -1 && second == -1)
        return -1;
    if (first == -1 && second != -1)
        return n/2 + second;
    else
        return first;
    
}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int indexOfLeast(const string a[], int n)
{
    int currentLeast = 0;
    if (n <= 0) return -1;
    if (n == 1) return 0;
    if (n == 2)
    {
        if (a[n-2] <= a[n-1])
            return currentLeast;
        currentLeast++;
        return currentLeast;
    }
    
    int first = indexOfLeast(a, n/2);
    int second = indexOfLeast(a + n/2, n - n/2);
    
    if (a[first] <= a[second + n/2])
        return first;

    else
        return second + n/2;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 <= 0)
        return true;
    if (n1 <= 0 || n1 < n2)
        return false;
    if (a1[n1-1] == a2[n2-1])
        return includes(a1, n1-1, a2, n2-1);
    else
        return includes(a1, n1-1, a2, n2);
}



