/**
 * Tests for TurtleProgram
 *
 * @author Yusuf Pisan
 * @date 19 Jan 2019
 */

#include "turtleprogram.h"
#include <cassert>
#include <sstream>

string toString(const TurtleProgram &tp) {
  ostringstream Out;
  operator<<(Out, tp);
  return Out.str();
}

void test0() {
  TurtleProgram Tp1;
  int Length = Tp1.getLength();
  assert(Length == 0 && "Length 0 for empty constructor");
  TurtleProgram Tp2("R", "2000");
  assert(Tp2.getLength() == 2 && "Length 2 for 2-param constructor");
  TurtleProgram Tp3(Tp2);
  assert(Tp2.getLength() == 2 && "Length 2 for copy constructor");
  assert(toString(Tp1) == string("[]") && "[] printed for empty constructor");
  assert(toString(Tp2) == string("[R 2000]") && "[R 2000] printed for 2-param constructor");
  assert(toString(Tp3) == string("[R 2000]") && "[R 2000] printed for copy constructor");
}
void test1() {
  TurtleProgram Tp1;
  TurtleProgram Tp2("R", "2000");
  TurtleProgram Tp3("R", "2000");
  TurtleProgram Tp4;
  assert(Tp1 == Tp4 && "== true for empty Tp1 == Tp4");
  assert(Tp2 == Tp3 && "== true for 2-param TP Tp2 == Tp3");
  TurtleProgram Tp5(Tp3);
  TurtleProgram Tp6(Tp3);
  assert(Tp5 == Tp6 && "== true for copy constructor TP Tp5 == Tp6");
  assert(Tp1 != Tp2 && "!= empty and 2-param Tp1 != Tp2");
  assert(Tp1 != Tp5 && "!= empty and copy constructor Tp1 != Tp5");
  TurtleProgram Tp7 = Tp1;
  TurtleProgram Tp8 = Tp2;
  assert(Tp7 == Tp1 && "= for empty TP using Tp7 == Tp1");
  assert(Tp8 == Tp2 && "= for 2-param TP using Tp8 == Tp2");
}
void test2() {
  TurtleProgram Tp1;
  TurtleProgram Tp2("R", "2000");
  TurtleProgram Tp3 = Tp1 + Tp1;
  assert(Tp3.getLength() == 0 && "Length 0 for + empty Tp3 = Tp1 + Tp1");
  Tp3 = Tp1 + Tp2;
  assert(Tp3.getLength() == 2 && "Length 2 for + empty and 2-param Tp3 = Tp1 + Tp2");
  assert(Tp3 == Tp2 && "+ empty and 2-param gives == Tp3 == Tp2");
  Tp3 = Tp2 + Tp2 + Tp2;
  assert(Tp3.getLength() == 6 && "Length 6 for + 2-param 3 times Tp3 = Tp2 + Tp2 + Tp2");
  assert(toString(Tp3) == string("[R 2000 R 2000 R 2000]") && "Length 6 prints OK toString(Tp3)");
  Tp3 = Tp2;
  Tp3 += Tp2;
  assert(Tp3.getLength() == 4 && "Length 4 for += on 2-param Tp3 += Tp2");
  Tp3 += Tp3;
  assert(Tp3.getLength() == 8 && "Length 8 for += on 2-param x 2 Tp3 += Tp3");
  Tp3 = Tp2 * 3;
  assert(toString(Tp3) == string("[R 2000 R 2000 R 2000]") && "Length 6 from * 3 Tp3 = Tp2 * 3");
  Tp3 = Tp2 * 1;
  assert(Tp3 == Tp2 && "= * 1 gives == Tp3 = Tp2 * 1, Tp3 == Tp2");
  Tp3 *= 3;
  assert(toString(Tp3) == string("[R 2000 R 2000 R 2000]") && "Length 6 from *= 3, Tp3 *= 3");
  Tp3 = Tp2 * 1;
}

void test3() {
  TurtleProgram Tp1("R", "2000");
  assert(Tp1.getIndex(0) == string("R") && "index 0, Tp9 = Tp1 * 1");
  assert(Tp1.getIndex(1) == string("2000") && "index 1");
  TurtleProgram Tp2(Tp1);
  Tp2.setIndex(0, "F");
  assert(Tp1 != Tp2 && "Tp2 modified, != anymore");
  Tp2.setIndex(0, "R");
  assert(Tp1 == Tp2 && "Tp2 modified, == now");
//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Wself-assign-overloaded"
  Tp2 = Tp2;
//#pragma clang diagnostic pop
  assert(toString(Tp2) == string("[R 2000]") && "self assignment OK for 2");
  Tp2 *= 1;
  assert(toString(Tp2) == string("[R 2000]") && "*1 OK for 2");
  Tp2 *= 5;
  Tp2.setIndex(2, "F");
  assert(toString(Tp2) == string("[R 2000 F 2000 R 2000 R 2000 R 2000]") && "*5 modified");
}

void test4() {
  TurtleProgram Tp1("R", "2000");
  Tp1 *= 5;
  TurtleProgram Tp2(Tp1);
  Tp2 *= 20; // 200
  Tp2 = Tp2 * 1000; // 200k
  Tp2 += Tp2; // 400 thousand
  assert(Tp2.getLength() == 400000 && "Length 400 thousand!");
}

void test5() {
   TurtleProgram Tp1;
   TurtleProgram Tp2("R", "2000");
   TurtleProgram Tp3 = Tp1 + Tp1;
   assert(toString(Tp3) == string("[]"));
   Tp3 = Tp1 + Tp2;
   assert(toString(Tp3) == string("[R 2000]"));
   Tp3 = Tp2 + Tp2 + Tp2;
   assert(toString(Tp3) == string("[R 2000 R 2000 R 2000]"));
   Tp3 = Tp2;
   Tp3 += Tp2;
   assert(toString(Tp3) == string("[R 2000 R 2000]"));
   Tp2 = Tp2 + Tp2;
   assert(toString(Tp2) == string("[R 2000 R 2000]"));
   Tp3 += Tp3;
   assert(toString(Tp3) == string("[R 2000 R 2000 R 2000 R 2000]"));
}

void testAll() {
  test1();
  test2();
  test3();
  test4();
  test5();
  cout << "Completed testAll!" << endl;
}


