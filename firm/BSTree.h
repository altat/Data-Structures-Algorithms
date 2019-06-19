#ifndef BSTREE_H
#define BSTREE_H

#include "client.h"

using namespace std;

//----------------------------------------------------------------------------
// class BSTree 
//
// ADT BSTree: collection of zero or more items with the restriction that
//             all insertions after root are placed in the left subtree if 
//             they are less than the elements in root and subsequent nodes. 
//             If they are greater than the elements in root and subsequent 
//             nodes, then they are inserted in the right subtree. 
//
// Implementation and assumptions:
//    -- Node is a struct made of a Client* and two Nodes*
//    -- Uses Client's overloaded operator<, operator>, ==, and <<.
//    -- The insert allocates memory for a Node, ptr to the data is passed in.
//    -- insert will not insert duplicate Clients (Client with same id).
//    -- retrieve's second parameter will be null if target not found.
//----------------------------------------------------------------------------

class BSTree {
public:
   BSTree();  // constructor
   ~BSTree(); // destructor

   // insert item, assume object passed in is valid, return whether successful
   bool insert(Client*);                         

   // retrieve item, return whether item exists, 2nd param is target if found
   bool retrieve(const Client&, Client*&) const; 

   // find Client by unique 4 digit id, return whether Client exists.
   bool find(int) const;                         

   void display() const; // prints BSTree inorder.
   void makeEmpty();     // clears out BSTree
   bool isEmpty() const; // return whether BSTree empty

private:
   struct Node {
      Client* data;
      Node* left;  // pointer to left subtree
      Node* right; // pointer to right subtree
   };

   Node* root;     // pointer to first element in tree

   bool insertHelper(Node*&, Node*);
   bool retrieveHelper(const Client&, Client*&, Node*) const;
   bool findHelper(int, Node*) const;
   void displayHelper(Node*) const;
   void makeEmptyHelper(Node*);
};
#endif // !BSTREE_H
