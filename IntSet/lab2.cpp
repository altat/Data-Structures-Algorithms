// To check consistent spelling, your program must compile with this 
// main with no changes to this code. This program terminates normally.
// Do NOT put an endl in operator<<.  
// Be sure to name your files using lowercase. Windows is not case sensitive,
// but unix/linux is case sensitive.

#include "intset.h"
#include <iostream>
using namespace std;

int main() {
   IntSet A(9), B(15,3), C(10,5,8), D(12,5,10,12,-500), E, X(D), Y;

   // sets A and B acquire desired values
   // A = { 3 7 9}
   // B = { 3 5 9 12 15}
   //cout << "Enter ints for set A:  " << endl;
   //cin >> A;
   //cout << "Enter ints for set B:  " << endl;
   //cin >> B;
   // As a shortcut when testing, you can use insert to avoid typing each time
   A.insert(3);
   A.insert(7);
   B.insert(5);
   B.insert(9);
   B.insert(12);

   cout << "A = " << A << endl;               // outputs: A = { 3 7 9}
   cout << "B = " << B << endl << endl;       // outputs: B = { 3 5 9 12 15}

   cout << "Compute  C = A + B" << endl;
   C = A + B;                                 // C is replaced by A+B
   cout << "C = " << C << endl << endl;       // outputs: C = { 3 5 7 9 12 15}

   cout << "Ask if  A == C" << endl;
   cout <<  ( (A == C)? "A == C" : "A is not == C" ) << endl << endl;

   cout << "Ask if  A != C" << endl;
   cout <<  ( (A != C)? "A is not == C" : "A == C" ) << endl << endl;

   cout << "Compute B - A = " << B - A << endl;            // B - A = { 5 12 15}
   cout << "Compute A - B = " << A - B << endl;            // A - B = { 7} 
   cout << "Compute  D = (A * B) + D" << endl;
   cout << "Before: D = " << D;                            // D = { 5 10 12}
   D = (A * B) + D;
   cout << "    After: " << "D = " << D << endl << endl;   // D = { 3 5 9 10 12}

   cout << "Test assignment operators" << endl;
   X = C = D = D;
   Y += A *= B;
   cout << "X = " << X << "    Y = " << Y << endl << endl;

   // miscellaneous stuff
   cout << (D.isInSet(0) ? "0 in set" : "0 not in set" ) << endl;
   cout << (D.isInSet(-1000) ? "-1000 in set" : "-1000 not in set" ) << endl;
   cout << (A.isEmpty() ? "A empty" : "A not empty" ) << endl;
   bool success;
   success = D.insert(-20000);           // handle value out of range
   success = D.remove(20000);            // handle value out of range
   success = D.remove(-5000);            // handle value out of range
   success = D.insert(0);                // put 0 in the set
   success = D.insert(20000);            // handle as you'd like, resize or not


   IntSet a(5, 3, 2), b(8, 5, 3);
   a = b;
   cout << a << endl;
   cout << b << endl;

   return 0;
}

