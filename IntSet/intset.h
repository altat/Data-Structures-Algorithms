// Created by: Tanvir Tatla

#ifndef INTSET_H
#define INTSET_H
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
// IntSet class:  ADT used to implement a mathematical set of non-negative 
// integers (includes zero). Each object of class IntSet can keep track of 
// whether integers are in the set or not. Can also:
//   -- unify, intersect, and return the difference of IntSets
//   -- allows for the assignment of IntSets
//   -- allows for the comparison of IntSets
//   -- print IntSets
//   -- insert and remove integers from a set
//
// Implementation and assumptions:
//   -- Overload +,*,-,=,==,!=,+=,*=,-=,<<, and >> operators
//   -- constructor can take up to 5 parameters where default values are -1
//   -- invalid integers (negative ints/chars) will be ignored when using >>
//   -- press 'enter' or 'return' to end >> (or any other way to enter '\n')
//   -- in <<, integers are displayed on 1 line between curly brackets
//---------------------------------------------------------------------------

class IntSet
{
   friend ostream& operator<<(ostream&, const IntSet&);
   friend istream& operator>>(istream&, IntSet&);

public:
   // default constructor. If parameters are not set, then parameters will be 
   // set to -1
   IntSet(int = -1, int = -1, int = -1, int = -1, int = -1);

   // copy constructor
   IntSet(const IntSet&);

   // destructor
   ~IntSet();

   bool insert(int);
   bool remove(int);

   bool isInSet(int) const;
   bool isEmpty() const;

   // mathematical operators
   IntSet operator+(const IntSet &) const;
   IntSet operator*(const IntSet &) const;
   IntSet operator-(const IntSet &) const;

   // assignment operator
   IntSet operator=(const IntSet &);

   // more mathematical operators
   IntSet operator+=(const IntSet &);
   IntSet operator*=(const IntSet &);
   IntSet operator-=(const IntSet &);

   // relational operators
   bool operator==(const IntSet &) const;
   bool operator!=(const IntSet &) const;

private:
   // size of bool array (setPtr)
   int size;

   // pointer to bool array
   bool *setPtr;

   // largest number in set
   int maxNum;

   // count of numbers in set
   int count;
};

#endif