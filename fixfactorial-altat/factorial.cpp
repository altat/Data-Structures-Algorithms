/**
 * Defines various versions of factorial
 *
 * @file factorial.cpp
 *
 * @author Yusuf Pisan
 * @date 24 Sep 2019
 */

#include <cmath>
#include <iostream>

// Only for class code, OK to use namespace
using namespace std;

// Calculate factorial using recursive function
int factorialRecursive(int number) {
  return number <= 1 ? 1 : factorialRecursive(number - 1) * number;
}

// Calculate factorial using iterative function
int factorialIterative(int number) {
  if (number <= 1) {
    return 1;
  }

  int Ans = number;

  while (number > 1) {
    number--;
    Ans *= number;
  }

  return Ans;
}

// Generic factorial function
int factorial(int number) {
  return factorialIterative(number);
}

// Writes the result of factorial to given ostream or cout
void factorialWrite(int number, ostream& os = cout) {
  os << factorial(number);
}
