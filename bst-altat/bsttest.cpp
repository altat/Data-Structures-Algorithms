/**
 * Testing BST - Binary Search Tree functions
 *
 * This file has series of tests for BST
 * Each test is independent and uses assert statements
 * Test functions are of the form
 *
 *      test_netidXX()
 *
 * where netid is UW netid and XX is the test number starting from 01
 *
 * Test functions can only use the public functions from BST
 * testBSTAll() is called from main in main.cpp
 * testBSTAll calls all other functions
 * @author Multiple
 * @date ongoing
 */

#include "bst.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>




using namespace std;

/**
 * Trying to avoid global variables,
 * by creating a singleton class with our visitor functions
 * stringstream SS contains the output from visitor
 */
class TreeVisitor {
public:
  // never create an instance of TreeVisitor object
  // we'll just use the static functions
  TreeVisitor() = delete;
  // insert output to SS rather than cout, so we can test it
  static stringstream SS;

  static string getSS() {
    return SS.str();
  }

  static void resetSS() {
    SS.str(string());
  }
  // instead of cout, insert item into a string stream
  static void visitor(const string &Item) {
    SS << Item;
  }

  // instead of cout, insert item into a string stream
  static void visitor(const int &Item) {
    SS << Item;
  }
};

// initialize the static variable
//  warning: initialization of 'SS' with static storage duration
//  may throw an exception that cannot be caught [cert-err58-cpp]
//  Not sure how to do it without making code harder to read
//  NOLINTNEXTLINE
stringstream TreeVisitor::SS;

/**
 * Test functions by Yusuf Pisan
 */

// Testing ==
void testPisan01() {
  cout << "Starting testPisan01" << endl;
  cout << "* Testing == and !=" << endl;
  BST<string> B1;
  BST<string> B2;
  BST<string> B3;
  // == and != for empty trees
  assert(B1 == B2 && (!(B1 != B2)));
  B1.add("c");
  B2.add("c");
  B3.add("b");
  // == and !- for 1-Node trees B1, B2, B3
  assert(B1 == B2 && (!(B1 != B2)));
  assert(B1 != B3 && (!(B1 == B3)));
  cout << "Ending testPisan01" << endl;
}

// Testing == in detail
void testPisan02() {
  cout << "Starting testPisan02" << endl;
  cout << "* Testing == and != with more detail" << endl;
  BST<string> B1;
  BST<string> B2;
  BST<string> B3;
  for (auto &S : vector<string>{"c", "a", "f", "g", "x"})
    B1.add(S);

  for (auto &S : vector<string>{"c", "f", "a", "g", "x"})
    B2.add(S);

  B3.add("b");

  // == for 5-Node trees B1, B2
  assert(B1 == B2 && (!(B1 != B2)));

  BST<string> B4(B3);
  // copy constructor for 1-Node trees B3, B4
  assert(B3 == B4 && (!(B3 != B4)));

  BST<string> B5(B1);
  // copy constructor for 5-Node trees B1, B5
  assert(B1 == B5 && (!(B5 != B1)));

  BST<string> B7("b");
  // 1-param constructor for 1-Node trees B3, B7
  assert(B3 == B7 && (!(B3 != B7)));

  cout << "Ending testPisan02" << endl;
}

// Testing traversal
void testPisan03() {
  cout << "Starting testPisan03" << endl;
  cout << "* Testing traversal" << endl;
  BST<string> B1;
  BST<string> B2;
  BST<string> B3;
  for (auto &S : vector<string>{"c", "a", "f", "g", "x"})
    B1.add(S);
  for (auto &S : vector<string>{"c", "f", "a", "g", "x"})
    B2.add(S);

  B3.add("b");

  TreeVisitor::resetSS();
  B1.inOrderTraverse(TreeVisitor::visitor);
  string Result = "acfgx";
  assert(TreeVisitor::getSS() == Result);

  TreeVisitor::resetSS();
  B1.preOrderTraverse(TreeVisitor::visitor);
  Result = "cafgx";
  assert(TreeVisitor::getSS() == Result);

  TreeVisitor::resetSS();
  B1.postOrderTraverse(TreeVisitor::visitor);
  Result = "axgfc";
  assert(TreeVisitor::getSS() == Result);

  cout << "Visual check B1:" << endl;
  cout << B1 << endl;
  cout << "Ending testPisan03" << endl;
}

/**
 * Test functions by Sample Sample
 */

// Testing samplefunctionality
void testSample01() {
  cout << "Starting testSample01" << endl;
  // assert(true);
  cout << "Ending testSample01" << endl;
}

// testing constructors and clear
void testTatla01() {
   cout << "Starting testTatla01" << endl;
   cout << "* Testing constructors" << endl;
   BST<int> B1(3); //single param constructor tests
   B1.add(5);

   TreeVisitor::resetSS();
   B1.inOrderTraverse(TreeVisitor::visitor);
   string Result = "35";
   assert(TreeVisitor::getSS() == Result);

   cout << "Testing Array Constructor" << endl;
   int Arr[7] = { 1,2,3,4,5,6,7 };
   BST<int> B2(Arr, 7);
   BST<int> B3; // B3 is what B2 should look like
   assert(B3.isEmpty());
   for (auto& S : vector<int>{ 4,2,1,3,6,5,7 }) 
      B3.add(S);

   assert(B2 == B3); // check if double param (Array) constructor works
   cout << "Testing Copy Constructor" << endl;
   BST<int> B4(B2);
   assert(B2 == B4 && B3 == B4);

   cout << "* Testing clear" << endl;
   B2.clear();
   assert(B2 != B4); // check if clear affects copy
   assert(B2.isEmpty());
   assert(!B4.isEmpty());

   cout << "Visual check B2:" << endl;
   cout << B2 << endl;
   TreeVisitor::resetSS();
   B2.inOrderTraverse(TreeVisitor::visitor);
   Result = "";
   assert(TreeVisitor::getSS() == Result);
   cout << "Ending testTatla01" << endl;
}

void testTatla02() {
   cout << "Starting testTatla02" << endl;
   cout << "* Testing getHeight and numberOfNodes" << endl;

   int Arr[15] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
   BST<int> B1(Arr, 15);

   cout << "Visual check B1:" << endl;
   cout << B1 << endl;

   assert(B1.getHeight() == 4);
   assert(B1.numberOfNodes() == 15);

   cout << "* Testing remove" << endl;
   B1.remove(15); // remove Node with 0 children

   TreeVisitor::resetSS();
   B1.preOrderTraverse(TreeVisitor::visitor);
   string Result = "8421365712109111413";
   assert(TreeVisitor::getSS() == Result);

   B1.remove(14); // remove Node with 1 child

   TreeVisitor::resetSS();
   B1.preOrderTraverse(TreeVisitor::visitor);
   Result = "84213657121091113";
   assert(TreeVisitor::getSS() == Result);

   B1.remove(8); // remove Node with 2 children (in this case, 8 is Root)

   TreeVisitor::resetSS();
   B1.preOrderTraverse(TreeVisitor::visitor);
   Result = "9421365712101113";
   assert(TreeVisitor::getSS() == Result);

   B1.remove(1); B1.remove(3); B1.remove(2); B1.remove(4);
   cout << "Visual check B1 after remove 15,14,8,1,3,2,4:" << endl 
      << B1 << endl;

   TreeVisitor::resetSS();
   B1.preOrderTraverse(TreeVisitor::visitor);
   Result = "965712101113";
   assert(TreeVisitor::getSS() == Result);

   cout << "* Testing add duplicates" << endl;
   assert(!B1.remove(29)); // remove nonexistent Items
   assert(!B1.remove(8));
   assert(!B1.add(9)); // adding Items that already exist
   assert(!B1.add(12));
   cout << "Ending testTatla02" << endl;
}

void testTatla03() {
   cout << "Starting testTatla03" << endl;
   cout << "* Testing contains" << endl;

   int Arr[15] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
   BST<int> B1(Arr, 15);

   assert(B1.contains(4));
   assert(B1.contains(8));
   assert(B1.contains(13));
   assert(!B1.contains(69));
   assert(!B1.contains(0));

   cout << "* Testing rebalance" << endl;
   B1.remove(1); B1.remove(2); B1.remove(3); B1.remove(4); B1.remove(5);
   B1.remove(6); B1.remove(7); B1.remove(12);

   BST<int> B2; // B2 is what B1 should look like after rebalance
   for (auto& S : vector<int>{ 11,9,8,10,14,13,15 })
      B2.add(S);

   assert(B1.getHeight() == 4);
   assert(B1 != B2);
   cout << "Visual check B1 before rebalance:" << endl << B1 << endl;

   B1.rebalance();
   assert(B1.getHeight() == 3);
   assert(B1 == B2);
   cout << "Visual check B1 after rebalance:" << endl << B1 << endl;

   BST<int> B3;
   BST<int> B4; // B4 is what B3 should look like after rebalance

   for (auto& S : vector<int>{ 1,2,3,4,5 })
      B3.add(S);

   for (auto& S : vector<int>{ 3,1,2,4,5 })
      B4.add(S);

   assert(B3.getHeight() == 5);
   assert(B3 != B4);
   cout << "Visual check B2 before rebalance:" << endl << B3 << endl;
   B3.rebalance();
   assert(B3.getHeight() == 3);
   assert(B3 == B4);
   cout << "Visual check B2 after rebalance:" << endl << B3 << endl;

   cout << "Ending testTatla03" << endl;
}

// Calling all test functions
void testBSTAll() {
  testPisan01();
  testPisan02();
  testPisan03();
  testSample01();
  testTatla01();
  testTatla02();
  testTatla03();
}