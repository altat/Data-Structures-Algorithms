// Created by: Tanvir Tatla

#include "intset.h"

const int INIT_SIZE = 5;


// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for class IntSet
IntSet::IntSet(int a, int b, int c, int d, int e)
{
   // initialize maxNum and count to zero.
   maxNum = 0;
   count = 0;

   // place parameters into array
   int numbers[] = { a, b, c, d, e };

   // find largest number in parameter array
   for (int i = 0; i < INIT_SIZE; i++) {
      if (numbers[i] > maxNum)
         maxNum = numbers[i];
   }

   // initialize size and allocate for bool array
   size = maxNum + 1;
   setPtr = new bool[size];

   // initialize setPtr to false
   for (int i = 0; i < size; i++) {
      setPtr[i] = false;
   }

   // add parameters to set if non-negative
   for (int i = 0; i < INIT_SIZE; i++) {
      if (numbers[i] >= 0)
      {
         setPtr[numbers[i]] = true;
         count++;
      }
   }
}

// ---------------------------------------------------------------------------
// Copy constructor for class IntSet
IntSet::IntSet(const IntSet& original)
{
   size = original.size;
   setPtr = new bool[size];

   // copy original values to new set
   for (int i = 0; i < size; i++) {
      setPtr[i] = original.setPtr[i];
   }

   maxNum = original.maxNum;
   count = original.count;
}

// ---------------------------------------------------------------------------
// Destructor 
// Destructor for class IntSet
IntSet::~IntSet()
{
   delete[] setPtr;
   setPtr = NULL;
}

// --------------------------------------------------------------------------
// insert
// Return true if n is successfully inserted and false if unsuccessful
bool IntSet::insert(int n)
{
   // if int to be inserted is non-negative AND can be inserted into array 
   // without resizing AND does not already exist in set.
   if (n >= 0 && n < size && !isInSet(n)) {
      // insert and find new maxNum
      setPtr[n] = true;
      count++;
      maxNum = (n > maxNum) ? n : maxNum;
      return true;
   }

   // else if bool array needs to be resized
   else if (n >= size) {
      // create new array
      size = n + 1;
      bool *temp = new bool[size];

      // loop over new array to initialize it
      for (int i = 0; i < n; i++) {
         // copy ints from old array into new array
         if (i <= maxNum && setPtr[i])
            temp[i] = true;
         else
            temp[i] = false;
      }

      // insert n (parameter) into new array
      temp[n] = true;
      count++;
      delete[] setPtr;
      setPtr = temp;
      maxNum = n;

      return true;
   }

   // return false if n was invalid or already existed in set
   else return false;
}

// --------------------------------------------------------------------------
// remove
// Return true if n is successfully removed and false if unsuccessful
bool IntSet::remove(int n)
{
   // if n exists in set
   if (isInSet(n)) {
      setPtr[n] = false;
      count--;

      // if n was maxNum, then find new maxNum
      if (n == maxNum) {
         // loop over array from n to zero
         for (int i = n; i >= 0; i--) {
            if (setPtr[i])
            {
               maxNum = i;
               break;
            }

            // if set has no numbers, then set maxNum to -1
            else maxNum = -1;
         }
      }

      return true;
   }

   // return false if n does not exist in set
   else return false;
}

// --------------------------------------------------------------------------
// isInSet
// Return true if n is in the set or false if not in set
bool IntSet::isInSet(int n) const
{
   if (n < 0 || n > maxNum) return false;
   return setPtr[n];
}

// --------------------------------------------------------------------------
// remove
// Return true if count is 0 (set is empty) and false otherwise
bool IntSet::isEmpty() const
{
   return count == 0;
}

// --------------------------------------------------------------------------
// operator+
// Returns union of two IntSets
IntSet IntSet::operator+(const IntSet& set) const
{
   IntSet temp;

   int max = (maxNum > set.maxNum) ? maxNum : set.maxNum;

   // loop over larger IntSet
   for (int i = 0; i <= max; i++) {
      // inserts whenever either set contains a number
      if (isInSet(i) || set.isInSet(i))
         temp.insert(i);
   }

   return temp;
}

// --------------------------------------------------------------------------
// operator*
// Returns intersection of two IntSets
IntSet IntSet::operator*(const IntSet& set) const
{
   IntSet temp;

   int smallMax = (maxNum < set.maxNum) ? maxNum : set.maxNum;

   // loop over smaller IntSet
   for (int i = 0; i <= smallMax; i++) {
      // insert whenever both sets contain the same number
      if (isInSet(i) && set.isInSet(i))
         temp.insert(i);
   }

   return temp;
}

// --------------------------------------------------------------------------
// operator-
// Returns difference of two IntSets
IntSet IntSet::operator-(const IntSet& set) const
{
   IntSet copy(*this);

   // loop over 2nd IntSet (parameter)
   for (int i = 0; i <= set.maxNum; i++) {
      // remove whenever both sets contain the same number
      if (copy.isInSet(i) && set.isInSet(i))
         copy.remove(i);
   }

   return copy;
}

// --------------------------------------------------------------------------
// operator=
// Assigns/sets value of right side operand (param) to left side (this)
IntSet IntSet::operator=(const IntSet& set) 
{
   // check if this and parameter are the same
   if (&set != this) {
      delete[] setPtr;
      size = set.size;
      setPtr = new bool[size];

      for (int i = 0; i < size; i++) {
         setPtr[i] = set.setPtr[i];
      }

      maxNum = set.maxNum;
      count = set.count;
   }

   return *this;
}

// --------------------------------------------------------------------------
// operator+=
// Returns unification of right and left operands and assigns result to left
IntSet IntSet::operator+=(const IntSet& set)
{
   for (int i = 0; i <= set.maxNum; i++) {
      if (set.isInSet(i))
         insert(i);
   }

   return *this;
}

// --------------------------------------------------------------------------
// operator*= 
// Returns intersection of right and left operands and assigns result to left
IntSet IntSet::operator*=(const IntSet& set)
{
   for (int i = 0; i <= maxNum; i++) {
      if (isInSet(i) && !set.isInSet(i))
         remove(i);
   }

   return *this;
}

// --------------------------------------------------------------------------
// operator-= 
// Difference of two IntSets by subtracting the right operand from 
// the left. Assigns the result to the left operand.
IntSet IntSet::operator-=(const IntSet& set)
{
   for (int i = 0; i <= maxNum; i++) {
      if (isInSet(i) && set.isInSet(i))
         remove(i);
   }

   return *this;
}

// --------------------------------------------------------------------------
// operator==
// Returns true when two IntSets are the same. Otherwise returns false.
bool IntSet::operator==(const IntSet& set) const
{
   // if the largest integer and number of integers in both sets are the same
   if (maxNum == set.maxNum && count == set.count) {

      // compare individual numbers in each set
      // loop over left operand's set
      for (int i = 0; i <= maxNum; i++) {
         if (setPtr[i] != set.setPtr[i])
            // difference was found
            return false;
      }

      // Both IntSets are equal if no differences were found
      return true;
   }

   else return false;
}

// --------------------------------------------------------------------------
// operator!=
// Returns true when two IntSets are different. Otherwise returns false.
bool IntSet::operator!=(const IntSet& set) const
{
   // if the largest integer and number of integers in both sets are the same
   if (maxNum == set.maxNum && count == set.count) {

      // compare individual numbers in each set
      for (int i = 0; i <= maxNum; i++) {
         if (setPtr[i] != set.setPtr[i])
            return true;
      }

      // no differences were found
      return false;
   }

   else return true;
}

// --------------------------------------------------------------------------
// operator<<
// Returns ostream of the set's integers
// output is integers in set enclosed by curly brackets. Each integer has a 
// space before it. If set is empty then output is '{}'
ostream& operator<<(ostream& output, const IntSet& set)
{
   output << '{';

   for (int i = 0; i <= set.maxNum; i++) {
      if (set.isInSet(i))
         output << ' ' << i;
   }

   output << '}';

   return output;
}

// --------------------------------------------------------------------------
// operator>>
// Returns istream. Reads user input and adds valid integers to set (parameter)
// ignores negative integers and characters/strings. Stops reading upon 
// hitting 'return' or 'enter' ('\n'). 
// Make sure you enter valid integers on a single line (with each integer 
// separated by a space). Hit the 'enter' key when you are done.
istream& operator>>(istream& input, IntSet& set)
{
   int number;

   do {
      input >> number;

      // ignore negative integers
      if (number < 0) continue;

      // ignore inputs that are not ints (chars and strings)
      else if (input.fail()) {
         input.clear();
         input.ignore();
      }

      // add if input is valid integer
      else set.insert(number);

   } while (input.peek() != '\n'); // keep reading input until new line

   return input;
}