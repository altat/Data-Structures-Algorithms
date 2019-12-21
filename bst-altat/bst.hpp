// Yusuf Pisan pisan@uw.edu
// 15 Jan 2018

// BST class
// Creates a BST to store values
// Uses Node which holds the Data
// Uses templates to store any type of Data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef BST_HPP
#define BST_HPP

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

template<class T>
class BST {
   // display BST tree in a human-readable format
   friend ostream& operator<<(ostream& Out, const BST& Bst) {
      Bst.printSideways(Out, Bst.Root);
      Out << endl;
      Bst.printVertical(Out, Bst.Root);
      return Out;
   }

private:
   // Node for BST
   struct Node {
      T Data;
      struct Node* Left;
      struct Node* Right;
   };

   // refer to data type "struct Node" as Node
   using Node = struct Node;

   // root of the tree
   Node* Root{ nullptr };

   // height of a Node, nullptr is 0, Root is 1, static, no access to 'this'
   static int getHeight(const Node* N) {
      if (N == nullptr) return 0;

      return max(1 + getHeight(N->Left), 1 + getHeight(N->Right));
   }

   /**
    * print tree sideways with root on left
                 6
             2
                 5
         0
                 4
             1
                 3
    */
   static ostream& printSideways(ostream& Out, const Node* Curr, int Level = 0) {
      const static char SP = ' ';
      const static int ReadabilitySpaces = 4;
      if (!Curr)
         return Out;
      printSideways(Out, Curr->Right, ++Level);
      Out << setfill(SP) << setw(Level * ReadabilitySpaces) << SP;
      Out << Curr->Data << endl;
      printSideways(Out, Curr->Left, Level);
      return Out;
   }

   static ostream& centeredPrint(ostream& Out, int Space,
      const string& Str, char FillChar = ' ') {
      auto StrL = static_cast<int>(Str.length());
      int Extra = (Space - StrL) / 2;
      if (Extra > 0) {
         Out << setfill(FillChar) << setw(Extra + StrL) << Str;
         Out << setfill(FillChar) << setw(Space - Extra - StrL) << FillChar;
      }
      else {
         Out << setfill(FillChar) << setw(Space) << Str;
      }
      return Out;
   }

   /**
    * print tree with the root at top
    *
       _____0______
    __1___      __2___
   3     4     5     6
    *
   **/
   static ostream& printTreeLevel(ostream& Out, queue<const Node*>& Q,
      int Width, int Depth, int MaxDepth) {
      const static char SP = ' ';
      const static char UND = '_';
      int Nodes = 0;
      int MaxN = pow(2, Depth - 1);
      int SpaceForEachItem = Width * pow(2, MaxDepth - 1) / MaxN; // NOLINT
      string
         Bigspace = string(static_cast<uint64_t>(SpaceForEachItem / 4), SP);
      while (Nodes++ < MaxN) {
         const Node* Tp = Q.front();
         Node* TpL = nullptr;
         Node* TpR = nullptr;
         Q.pop();
         string Label = "N";
         if (Tp) {
            stringstream Ss;
            Ss << Tp->Data;
            Label = Ss.str();
            TpL = Tp->Left;
            TpR = Tp->Right;
         }
         char Filler = Depth == MaxDepth ? SP : UND;
         if (Depth == MaxDepth) {
            centeredPrint(Out, SpaceForEachItem, Label, Filler);
         }
         else {
            Out << Bigspace;
            centeredPrint(Out, SpaceForEachItem / 2, Label, Filler);
            Out << Bigspace;
            Q.push(TpL);
            Q.push(TpR);
         }
      }
      Out << endl;
      return Out;
   }

   // helper function for displaying tree sideways, works recursively
   static ostream& printVertical(ostream& Out, Node* Curr) {
      const static int WIDTH = 6;  // must be even
      if (!Curr)
         return Out << "[__]";
      // figure out the maximum depth which determines how wide the tree is
      int MaxDepth = getHeight(Curr);
      queue<const Node*> Q;
      Q.push(Curr);
      for (int Depth = 1; Depth <= MaxDepth; ++Depth) {
         printTreeLevel(Out, Q, WIDTH, Depth, MaxDepth);
      }
      return Out;
   }

   // helper function for converting an array to a balanced BST w/minimum 
   // height, works recursively
   // Start and End are Indices used to partition Array
   static Node* arrayToBst(const T Arr[], int Start, int End) {
      // array can't be divided by 2 if Start > End
      if (Start > End) return nullptr;

      // Pick Middle Item as Root
      int Mid = (Start + End) / 2;
      auto N = new Node;
      setNode(Arr[Mid], N);

      // Recurse on smaller array pieces
      N->Left = arrayToBst(Arr, Start, Mid - 1);
      N->Right = arrayToBst(Arr, Mid + 1, End);

      // return Root
      return N;
   }

   // helper function for copy constructor, works recursively
   void copy(Node* N) {
      // nothing to copy if NULL
      if (N != nullptr) {
         // add copies using preorder traversal (root, left, right) so that
         // structure is same
         add(N->Data);
         copy(N->Left);
         copy(N->Right);
      }
   }

   // total number of Nodes in Binary Tree
   // nullptr is 0, Root is 1
   static int countNodes(Node* N) {
      if (N == nullptr) return 0;

      return 1 + countNodes(N->Left) + countNodes(N->Right);
   }

   // helper function for adding an Item to a BST, works recursively
   // returns true if successfully added, returns false otherwise
   // does not add Item if duplicate exists
   static bool addHelper(const T& Item, Node*& Current) {
      // if there is no Node at current location
      if (Current == nullptr) {
         Current = new Node; // then create a new Node
         setNode(Item, Current); // and set its Data
         return true;
      }

      // if Item to add is less than Current's Data, then recurse left
      if (Item < Current->Data) return addHelper(Item, Current->Left);

      // if Item to add is greater than Current's Data, then recurse right
      if (Item > Current->Data) return addHelper(Item, Current->Right);

      return false; // return false if duplicate Item
   }

   // helper function for removing an Item to a BST, works recursively
   // returns true if removed successfully, returns false otherwise
   static bool removeHelper(const T& Item, Node*& Current) {
      // if there is no Node at current location
      if (Current == nullptr) return false; // then BST does not contain Item

      // if Item to remove is less than Current's Data, then recurse left
      if (Item < Current->Data) return removeHelper(Item, Current->Left);

      // if Item to remove is greater than Current's Data, then recurse right
      if (Item > Current->Data) return removeHelper(Item, Current->Right);

      // Item has been found in Current Node
      Node* Successor;

      // if Current has 1 child or 0 children
      if (Current->Left == nullptr || Current->Right == nullptr) {
         Successor = Current;
         // if no left child, then set Current to right
         // if no right child, then set Current to left
         // if 0 children, then Current will be set to nullptr
         Current = (Current->Left == nullptr ? Current->Right : Current->Left);
         delete Successor; // delete Node that contains Item
         return true;
      }

      // else if Current has 2 children, then find Successor (leftmost Node
      // in right subtree)
      Successor = findSuccessor(Current->Right);
      // overwrite Item to be removed w/Successor's Data
      Current->Data = Successor->Data; 
      // remove Successor from right subtree
      return removeHelper(Successor->Data, Current->Right);
   }

   // helper function that finds Successor in removeHelper
   // returns the leftmost Node in subtree
   static Node* findSuccessor(Node* N) {
      Node* Current = N; 

      while (Current != nullptr && Current->Left != nullptr)
         Current = Current->Left; // traverse left until leftmost Node found

      return Current;
   }

   // helper function for checking whether BST contains certain Item
   // return true if BST contains item, returns false otherwise
   static bool containsHelper(const T& Item, Node* Current) {
      // if no Node at current location, then BST does not contain Item
      if (Current == nullptr) return false;

      if (Current->Data == Item) return true; // Item found

      // if Item is less than Current's Data, then recurse left
      if (Item < Current->Data) return containsHelper(Item, Current->Left);

      // if Item is greater than Current's Data, then recurse right
      if (Item > Current->Data) return containsHelper(Item, Current->Right);

      return false;
   }

   // helper function for inOrderTraverse (Left-Root-Right)
   // takes a function that takes a single parameter of type T
   static void inHelper(void Visit(const T& Item), Node* Current) {
      if (Current == nullptr) return; // base case

      inHelper(Visit, Current->Left); // traverse Left
      Visit(Current->Data); // visit Root
      inHelper(Visit, Current->Right); // traverse Right
   }

   // helper function for preOrderTraverse (Root-Left-Right)
   static void preHelper(void Visit(const T& Item), Node* Current) {
      if (Current == nullptr) return;

      Visit(Current->Data);
      preHelper(Visit, Current->Left);
      preHelper(Visit, Current->Right);
   }

   // helper function for postOrderTraverse (Left-Right-Root)
   static void postHelper(void Visit(const T& Item), Node* Current) {
      if (Current == nullptr) return;

      postHelper(Visit, Current->Left);
      postHelper(Visit, Current->Right);
      Visit(Current->Data);
   }

   // helper function for inserting Items from BST to Array in ascending order
   static void bstToArray(T Arr[], Node* N, int& Index) {
      if (N == nullptr) return; // Nothing to add to Array

      // use inorder traversal to add Items from BST to Array
      bstToArray(Arr, N->Left, Index); // recurse left
      Arr[Index++] = N->Data; // add Item to Array then increment Index
      bstToArray(Arr, N->Right, Index); // recurse right
   }

   // helper function for emptying a BST
   static void clearHelper(Node* Current) {
      if (Current == nullptr) return; // nothing to clear

      // use postorder traversal to delete children first and Root last
      clearHelper(Current->Left); // recurse left, recurse right, visit Root
      clearHelper(Current->Right);

      delete Current; // delete Root
      Current = nullptr;
   }

   // helper function for checking for equality
   // returns true if equal, returns false if inequal
   static bool isEqual(Node* Lhs, Node* Rhs) {
      // End of subtree reached. Nothing left to check so return true.
      if (Lhs == nullptr && Rhs == nullptr) return true;

      // if both Nodes exist, then compare their Data for equality AND
      // recurse Left AND recurse Right (check left and right subtrees for
      // equality)
      if (Lhs != nullptr && Rhs != nullptr) {
         return (Lhs->Data == Rhs->Data && isEqual(Lhs->Left, Rhs->Left)
            && isEqual(Lhs->Right, Rhs->Right));
      }

      return false; // One Node is nullptr and the other isn't so inequal
   }

   // setter for Node
   static void setNode(const T Item, Node*& N) {
      N->Data = Item; // set Data
      N->Left = nullptr; // Left and Right are set to nullptr
      N->Right = nullptr;
   }

   // checks if an Array is sorted
   // returns true if sorted, false if unsorted
   static bool isSorted(const T Arr[], int N) {
      if (N <= 1) return true; // true if Array has 1 or less Items

      for (int I = 1; I < N; I++) {
         if (Arr[I - 1] > Arr[I]) return false; // unsorted Item found
      }

      return true; 
   }

public:
   // constructor, empty tree
   BST() = default;

   // constructor, tree with root
   explicit BST(const T& RootItem) {
      Root = new Node;
      setNode(RootItem, Root);
   }

   // given an array of length n
   // create a tree to have all items in that array
   // with the minimum height (i.e. rebalance)
   // Assignment specification
   // NOLINTNEXTLINE
   BST(const T Arr[], int N) {
      // if the array is not sorted
      if (!isSorted(Arr, N)) {
         auto A = new T[N]; // create a new array
         for (int I = 0; I < N; I++)
            A[I] = Arr[I]; // copy Items to new array

         sort(A, A + N); // sort new array
         Root = arrayToBst(A, 0, N - 1); // create balanced BST
         delete[] A;
      }

      // else create balanced BST
      else Root = arrayToBst(Arr, 0, N - 1);
   }

   // copy constructor
   BST(const BST<T>& Bst) {
      Root = nullptr;
      copy(Bst.Root);
   }

   // destructor
   virtual ~BST() {
      clear();
   }

   // true if no nodes in BST
   bool isEmpty() const {
      return Root == nullptr;
   }

   // 0 if empty, 1 if only root, otherwise
   // height of root is max height of subtrees + 1
   int getHeight() const {
      return getHeight(Root);
   }

   // Number of nodes in BST
   int numberOfNodes() const {
      return countNodes(Root);
   }

   // add a new item, return true if successful
   bool add(const T& Item) {
      return addHelper(Item, Root);
   }

   // remove item, return true if successful
   bool remove(const T& Item) {
      return removeHelper(Item, Root);
   }

   // true if item is in BST
   bool contains(const T& Item) const {
      return containsHelper(Item, Root);
   }

   // inorder traversal: left-root-right
   // takes a function that takes a single parameter of type T
   void inOrderTraverse(void Visit(const T& Item)) const {
      inHelper(Visit, Root);
   }

   // preorder traversal: root-left-right
   void preOrderTraverse(void Visit(const T& Item)) const {
      preHelper(Visit, Root);
   }

   // postorder traversal: left-right-root
   void postOrderTraverse(void Visit(const T& Item)) const {
      postHelper(Visit, Root);
   }

   // create dynamic array, copy all the items to the array
   // and then read the array to re-create this tree from scratch
   // so that resulting tree is balanced
   void rebalance() {
      int Size = numberOfNodes(); // count Nodes in BST
      auto Arr = new T[Size]; // create Array big enough to fit all Items

      int Index = 0;
      bstToArray(Arr, Root, Index); // add Items from BST to Array

      this->clear(); // empty 'this'
      Root = arrayToBst(Arr, 0, Size - 1); // convert Array to balanced BST
      delete[] Arr;
   }

   // delete all nodes in tree
   void clear() {
      clearHelper(Root);
      Root = nullptr;
   }

   // trees are equal if they have the same structure
   // AND the same item values at all the nodes
   bool operator==(const BST<T>& Other) const {
      // check if 'this' and Other are same reference
      if (this == &Other) return true; 
      return isEqual(Root, Other.Root);
   }

   // not == to each other
   bool operator!=(const BST<T>& Other) const {
      return !(*this == Other);
   }
};

#endif  