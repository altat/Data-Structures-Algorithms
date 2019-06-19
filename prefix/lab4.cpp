
#include "prefix.h"
#include <iostream>
using namespace std;

int main(){
   // declare file object and open the datafile 
   ifstream infile("data4.txt"); 
   if (!infile)  {
      cout << "File could not be opened." << endl;
      return 1;
   }

   // for each prefix expression, evaluate, print answer, and print as postfix
   cout << "Prefix Expression = Answer" << endl;
   cout << "--------------------------" << endl;
   for (;;) {
      Prefix expr;
      expr.setPrefix(infile);

      // on windows, new line after last line of data; no line on linux
      if (infile.eof()) 
         break;
      cout << expr << " = " << expr.evaluatePrefix();
      cout << "       As postfix:  ";
      expr.outputAsPostfix(cout);
      cout << endl;
   }
   return 0;
}

