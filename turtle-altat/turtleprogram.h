/**
 * TurtleProgram is a set of instructions directing the on-screen turtle 
 * to draw graphics. To draw a square, one would execute:
 * F 10 R 90 F 10 R 90 F 10 R 90 F 10 R 90
 * Each object of class TurtleProgram can:
 *   - add, multiply, add assign, multiply assign
 *   - allow for assignment or comparison
 *   - access and mutate member variables
 *
 * Assumes size is greater than zero when multiplying.
 *
 * @author Tanvir Tatla
 * @date 6 October 2019
 */

#ifndef TURTLEPROGRAM_H
#define TURTLEPROGRAM_H

#include <iostream>

using namespace std;

class TurtleProgram {
  friend ostream &operator<<(ostream &Out, const TurtleProgram &Tp);

public:
  TurtleProgram(); // default constructor
  explicit TurtleProgram(const string &Command); // single param constructor
  TurtleProgram(const string &Command, const string &Times); //2 param constr
  TurtleProgram(const TurtleProgram &Tp); // deep copy constructor
  virtual ~TurtleProgram(); // destructor

  // accessors and mutators
  int getLength() const;
  string getIndex(const int &I) const;
  void setIndex(const int &I, const string &Str);

  // comparison operators
  bool operator==(const TurtleProgram &Rhs) const; 
  bool operator!=(const TurtleProgram &Rhs) const;

  TurtleProgram &operator=(const TurtleProgram &Rhs); // assignment operator

  // overloaded math operators
  TurtleProgram operator+(const TurtleProgram &Tp) const;
  TurtleProgram &operator+=(const TurtleProgram &Tp);
  TurtleProgram operator*(const int &Times) const;
  TurtleProgram &operator*=(const int &Times);

  // swap member variables
  friend void swap(TurtleProgram& Left, TurtleProgram& Right);

protected:
private:
   string* Commands; // String array to hold commands
   int Size; // keep track of size of Commands array
};

#endif // TURTLEPROGRAM_H
