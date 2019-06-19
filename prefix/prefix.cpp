// Author: Tanvir Tatla
#include "prefix.h"

//-----------------------------------------------------------------------------
// constructor
// initialize the array to the empty string,
// char arrays end with '\0' (null character) so operator<< works properly

Prefix::Prefix() {
   expr[0] = '\0'; 
} 

//-----------------------------------------------------------------------------
// setPrefix
// Set a prefix expression made of single digit operands, operators +,-,*,/
// and no blanks or tabs contained in a file. The expression is valid in
// that each valid operator has two valid operands.

void Prefix::setPrefix(ifstream& infile) { 
    infile >> expr;
}

//-----------------------------------------------------------------------------
// evaluatePrefix 
// Evaluate a prefix expr made of single digit operands and operators +,-,*,/
// Return the answer (integer arithmetic).
// division by zero returns -1 and prints an error

int Prefix::evaluatePrefix() const {
    if (expr[0] == '\0')                          // empty string
        return 0;

    int index = -1;                               // to walk through expr
    return evaluatePrefixHelper(index);
}

//-----------------------------------------------------------------------------
// evaluatePrefixHelper
// Helper function for evaluatePrefix. Uses recursion.

int Prefix::evaluatePrefixHelper(int& index) const {
    char symbol = expr[++index]; // next symbol in array
    
    if (symbol == '\0') // end of array reached
       return 0;

    else if (isdigit(symbol)) // return number if the symbol is a digit
       return symbol - '0';

    else if (symbol == '+') //return sum of next two symbols in array if '+'
       return evaluatePrefixHelper(index) + evaluatePrefixHelper(index);

    else if (symbol == '*') //return product of next two symbols in array
       return evaluatePrefixHelper(index) * evaluatePrefixHelper(index);

    else if (symbol == '-') { //return difference of next 2 symbols in array
       int x = evaluatePrefixHelper(index);
       int y = evaluatePrefixHelper(index);

       return x - y;
    }

    else if (symbol == '/') { // return quotient of next 2 symbols in array
       int x = evaluatePrefixHelper(index);
       int y = evaluatePrefixHelper(index);
       
       if (y == 0) { // can't divide by zero. print error and return -1
          cerr << "Division by zero condition!" << endl;
          return -1;
       }
       
       return x / y; 
    }

    else // skip symbol if not valid
       return evaluatePrefixHelper(index);
}

//-----------------------------------------------------------------------------
// outputAsPostfix, toPostfix
// Convert prefix expression to postfix and output

void Prefix::outputAsPostfix(ostream& out) const {
    if (expr[0] == '\0')                      // empty string
        return;

    int index = -1;                           // to walk through expr
    int count = -1;                           // used to build postfix array
    char postfix[MAXSIZE+1];                  // holds postfix expression
    toPostfix(index, postfix, count);
    postfix[++count] = '\0';
    out << postfix;
}

void Prefix::toPostfix(int& index, char postfix[], int& count) const {
    char symbol = expr[++index]; // get next symbol in array
    
    if (symbol == '\0') // end of array reached
       return;

    else if (isdigit(symbol)) // add symbol to postfix array if digit
       postfix[++count] = symbol;

    else if (!isValidSymbol(symbol)) // skip symbol if not valid
       toPostfix(index, postfix, count);

    else { // if symbol is operator, then add next two symbols before current
       toPostfix(index, postfix, count);
       toPostfix(index, postfix, count);
       postfix[++count] = symbol;
    }
}

//-----------------------------------------------------------------------------
// isValidSymbol
// returns true if symbol (parameter) is +, *, -, or /  and false otherwise

bool Prefix::isValidSymbol(const char symbol) {
   if (symbol == '+' || symbol == '*' || symbol == '-' || symbol == '/')
      return true;

   else return false;
}

//-----------------------------------------------------------------------------
// operator<<
// display prefix expression as a string (char array)

ostream& operator<<(ostream& output, const Prefix& expression) {
    output << expression.expr;
    return output;
}