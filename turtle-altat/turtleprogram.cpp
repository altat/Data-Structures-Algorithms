/**
 * Implementation for TurtleProgram
 *
 * @author Tanvir Tatla
 * @date 6 October 2019
 */

#include "turtleprogram.h"
#include <cassert>

 // --------------------------------------------------------------------------
 // default constructor
TurtleProgram::TurtleProgram() {
   Commands = nullptr;
   Size = 0;
}

// --------------------------------------------------------------------------
// single parameter constructor
// Takes a single string as a directional command
TurtleProgram::TurtleProgram(const string& Command) {
   Size = 1;
   Commands = new string[Size];
   Commands[0] = Command;
}

// --------------------------------------------------------------------------
// double parameter constructor
// First string is direction and second string is distance
TurtleProgram::TurtleProgram(const string& Command, const string& Times) {
   Size = 2;
   Commands = new string[Size];
   Commands[0] = Command;
   Commands[1] = Times;
}

// --------------------------------------------------------------------------
// copy constructor
// makes a deep copy of parameter
TurtleProgram::TurtleProgram(const TurtleProgram& Tp) {
   Size = Tp.getLength();

   Size > 0 ? Commands = new string[Size] : Commands = nullptr;

   // copies from Tp one command at a time
   for (int I = 0; I < Size; I++) {
      Commands[I] = Tp.getIndex(I);
   }
}

// --------------------------------------------------------------------------
// getLength
// returns the length of the program
int TurtleProgram::getLength() const {
   return Size;
}
// --------------------------------------------------------------------------
// getIndex
// returns the command at the specified index (param)
string TurtleProgram::getIndex(const int& I) const {
   if (I >= Size) return nullptr;

   return Commands[I];
}

// --------------------------------------------------------------------------
// setIndex
// sets the command at the specified index (param)
void TurtleProgram::setIndex(const int& I, const string& Str) {
   if (I >= Size) return;

   Commands[I] = Str;
}

// --------------------------------------------------------------------------
// operator!=
// checks for inequality. returns false if equal
bool TurtleProgram::operator!=(const TurtleProgram& Rhs) const {
   return !(*this == Rhs);
}
// --------------------------------------------------------------------------
// operator==
// checks for equality. returns true if equal
bool TurtleProgram::operator==(const TurtleProgram& Rhs) const {
   if (Size != Rhs.Size) return false;

   for (int I = 0, J = Size; I < J; I++) {
      if (this->getIndex(I) != Rhs.getIndex(I)) {
         return false;
      }
   }

   return true;
}

// --------------------------------------------------------------------------
// operator+
// Returns sum of Lhs and Tp
TurtleProgram TurtleProgram::operator+(const TurtleProgram& Tp) const {
   TurtleProgram Bigger; // return value
   Bigger.Size = this->getLength() + Tp.getLength();
   Bigger.Commands = new string[Bigger.Size]; //new array for combined size

   // copies commands from Lhs into new array
   for (int I = 0, J = Size; I < J; I++) {
      Bigger.setIndex(I, this->getIndex(I));
   }

   // copies commands from param into new array
   for (int I = Size, J = Bigger.Size, K = 0; I < J; I++, K++) {
      Bigger.setIndex(I, Tp.getIndex(K));
   }

   return Bigger;
}
// --------------------------------------------------------------------------
// operator+=
// Appends Tp to Lhs
TurtleProgram& TurtleProgram::operator+=(const TurtleProgram& Tp) {
   *this = *this + Tp;
   return *this;
}

// --------------------------------------------------------------------------
// operator*
// Returns product of Lhs and Times paramter
TurtleProgram TurtleProgram::operator*(const int& Times) const {
   assert(Times > 0); // check if multiplying by integer greater than 0
   TurtleProgram Bigger; // value to return
   Bigger.Size = Size * Times;
   Bigger.Commands = new string[Bigger.Size]; // creates Bigger array

   // outer loop tells inner loop how many multiples of Lhs to add
   for (int I = 0; I < Times; I++) {
      // inner loop adds one multiple of Lhs into Bigger's array
      for (int J = 0; J < Size; J++) {
         int Index = J + (Size * I);
         Bigger.setIndex(Index, this->getIndex(J));
      }
   }

   return Bigger;
}
// --------------------------------------------------------------------------
// operator*=
// Assigns product of Lhs and Times to Lhs
TurtleProgram& TurtleProgram::operator*=(const int& Times) {
   assert(Times > 0);

   *this = *this * Times;
   return *this;
}

// --------------------------------------------------------------------------
// operator= (copy assignment)
// makes a deep copy and assigns it to Lhs
TurtleProgram& TurtleProgram::operator=(const TurtleProgram& Rhs) {
   // skip if statement when Rhs and this are same.
   if (*this != Rhs) {
      TurtleProgram Temp(Rhs); // make a dummy of Rhs
      swap(*this, Temp); // swap member variables of dummy and this
   }

   return *this;
}

// --------------------------------------------------------------------------
// destructor
TurtleProgram::~TurtleProgram() {
   delete[] Commands;
   Commands = nullptr;
}

// --------------------------------------------------------------------------
// operator<<
// Overloaded output operator for class Array
ostream& operator<<(ostream& Out,
   const TurtleProgram& Tp) {
   if (Tp.getLength() <= 0) return Out << "[]"; // empty TurtleProgram

   Out << "[" << Tp.getIndex(0);

   for (int I = 1, J = Tp.getLength(); I < J; I++) {
      Out << " " << Tp.getIndex(I);
   }
   
   Out << "]";
   return Out;                      // e.g., enables cout << x << y;
}

// --------------------------------------------------------------------------
// swap
// Swaps the pointers for member variables of Left and Right
void swap(TurtleProgram& Left, TurtleProgram& Right) {
   using std::swap;

   swap(Left.Size, Right.Size);
   swap(Left.Commands, Right.Commands);
}