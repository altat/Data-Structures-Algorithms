#include "BSTree.h"

//------------------------------ constructor ---------------------------------
BSTree::BSTree() {
   root = nullptr;
}

//------------------------------ destructor ----------------------------------
BSTree::~BSTree() {
   makeEmpty();
}

//------------------------------ insert --------------------------------------
// inserts a Client into the BSTree using recursion. 
// returns whether inserted successfully
bool BSTree::insert(Client* clientptr) {
   // create Node to be inserted and set its data
   Node* nodeptr = new Node;
   if (nodeptr == nullptr) return false; // stop if out of memory
   nodeptr->data = clientptr;
   nodeptr->left = nullptr;
   nodeptr->right = nullptr;
   return insertHelper(root, nodeptr);
}

bool BSTree::insertHelper(Node*& current, Node* nodeptr) {
   // if empty spot, then insert
   if (current == nullptr) {
      current = nodeptr;
      return true;
   }

   // if node to be inserted has lesser data than current node
   if (*nodeptr->data < *current->data)
      return insertHelper(current->left, nodeptr); // go to left subtree

   // if Client's id is greater than current Node's Client
   if (*nodeptr->data > *current->data)
      return insertHelper(current->right, nodeptr); // try right subtree

   // Client with same id is already in tree
   delete nodeptr->data; // delete duplicate client
   delete nodeptr;
   return true; // return true since Client already inserted
}

//------------------------------ retrieve ------------------------------------
// returns whether target Client is in tree. If true, then sets second param
// to found Client
bool BSTree::retrieve(const Client& target, Client*& client) const {
   client = nullptr;
   return retrieveHelper(target, client, root);
}

bool BSTree::retrieveHelper(const Client& target, Client*& client, 
   Node* current) const {

   // if empty/end of tree reached, then not found
   if (current == nullptr) return false;

   // target found
   if (*current->data == target) {
      client = current->data;
      return true;
   }

   if (*current->data > target) 
      return retrieveHelper(target, client, current->left);

   if (*current->data < target)
      return retrieveHelper(target, client, current->right);

   return false;
}

//------------------------------ find ----------------------------------------
// returns whether Client with same id as param exists in tree
bool BSTree::find(int id) const {
   if (id < MIN_CLIENT_ID || id > MAX_CLIENT_ID) return false;

   return findHelper(id, root);
}

bool BSTree::findHelper(int id, Node* current) const {
   // end of tree reached, therefore not found
   if (current == nullptr) return false;

   // id found, therefore exists
   if (id == current->data->getID()) return true;

   if (id < current->data->getID())
      return findHelper(id, current->left);

   if (id > current->data->getID())
      return findHelper(id, current->right);

   return false;
}

//------------------------------ display -------------------------------------
// Displays each element (Client) in this tree inorder
void BSTree::display() const {
   displayHelper(root);
   //cout << endl;
}

void BSTree::displayHelper(Node* current) const {
   // stop when end of tree reached
   if (current == nullptr) return; 
   
   displayHelper(current->left); // display from least to greatest
   cout << *current->data << endl;
   displayHelper(current->right);
}

//------------------------------ makeEmpty -----------------------------------
// empties a tree
void BSTree::makeEmpty() {
   makeEmptyHelper(root);
   root = nullptr;
}

void BSTree::makeEmptyHelper(Node* current) {
   // end of tree reached
   if (current == nullptr) return;

   // empty subtrees before root
   makeEmptyHelper(current->left);
   makeEmptyHelper(current->right);

   delete current->data;
   current->data = nullptr;

   delete current;
   current = nullptr;
}

//------------------------------ isEmpty -------------------------------------
// returns whether tree is empty
bool BSTree::isEmpty() const {
   return root == nullptr;
}