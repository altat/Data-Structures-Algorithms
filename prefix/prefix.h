// Author: Tanvir Tatla
//--------------------------  class Prefix  -----------------------------------
// Evaluates prefix expressions and converts/outputs prefix to postfix 
// For example: 
// *+234 = 20       As postfix:  23+4*
//          
// Assumptions/Implementation:  
//    -- Assumes prefix expressions are formatted correctly and don't
//       contain invalid symbols
//    -- Assumes data file exists and can be read 
//    -- invalid symbols will not be included in evaluation or postfix output
//       invalid symbols include anything that is not a digit or +,*,-,/
//    -- Division by zero will return -1 and print an error message
//
//----------------------------------------------------------------------------

#ifndef PREFIX_H
#define PREFIX_H
#include <iostream>
#include <fstream>
using namespace std;

int const MAXSIZE = 100;

class Prefix {
    friend ostream& operator<<(ostream&, const Prefix&);

public:
    Prefix();                              // constructor
    void setPrefix(ifstream& infile);      // Set a prefix expression
    int evaluatePrefix() const;            // evaluate prefix expression
    void outputAsPostfix(ostream&) const;  // convert prefix to postfix

private:
    char expr[MAXSIZE+1];                      // array for storing symbols in 
                                               // prefix expression

    int evaluatePrefixHelper(int&) const;      // recursive helper for 
                                               // evaluatePrefix

    void toPostfix(int&, char [], int&) const; // recursive helper for 
                                               // outputAsPostfix

    static bool isValidSymbol(const char);     // check if symbol is valid
};

#endif

