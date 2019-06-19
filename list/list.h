/////////////////////////  list.h file  //////////////////////////////
// Author: Tanvir Tatla
// Simple linked list, uses Node as linked list node

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <fstream>
using namespace std;

//--------------------------  class List  ------------------------------------
// ADT List: finite, ordered collection of zero or more items.
//           The ordering is determined by operator< of T class.
//          
// Assumptions/Implementation:  
//   -- Control of <, printing, etc. of T information is in the T class.  
//   -- There is no dummy head node, head points to first node.  
//      If the list is empty, head is NULL.
//   -- The insert allocates memory for a Node, ptr to the data is passed in.
//      Allocating memory and setting data is the responsibility of the caller.
//   -- remove removes a target from a list and assigns it to the second 
//      parameter. It is the caller's responsibility to ensure the target 
//      exists or else the second parameter will be unreliable. 
//   -- retrieve searches for a target and assigns it to the second parameter.
//      It is the caller's responsibility to ensure the target exists or else 
//      the second parameter will be unreliable.
//   -- merge will not do anything if both parameters have the same address
//      as 'this'
//
//----------------------------------------------------------------------------

template <typename T>
class List {

   // output operator for class List, print data, 
   // responsibility for output is left to object stored in the list
   friend ostream& operator<<(ostream& output, const List<T>& thelist) {
      typename List<T>::Node* current = thelist.head;
      while (current != NULL) { 
         output << *current->data;
         current = current->next;
      }
      return output;
}

public:
   List();                                // default constructor
   ~List();                               // destructor
   List(const List&);                     // copy constructor
   bool insert(T*);                       // insert one Node into list
   bool isEmpty() const;                  // is list empty?
   void buildList(ifstream&);             // build a list from datafile
   void makeEmpty();                      // empties a list
   bool retrieve(const T&, T*&);          // finds a target
   bool remove(const T&, T*&);            // removes a target
   void merge(List<T>&, List<T>&);        // merges two lists into one
   void intersect(const List<T>&, const List<T>&); //intersects two lists

   List<T>& operator=(const List<T>&);    // deep copies a list

   bool operator==(const List<T>&) const; // compares two lists to see if equal
   bool operator!=(const List<T>&) const; // compares 2 lists to see if unequal

   void doSomethingTotallyWeird();


private:
   struct Node {            // the node in a linked list
      T* data;              // pointer to actual data, operations in T
      Node* next;
   };

   Node* head;              // pointer to first node in list
};


//----------------------------------------------------------------------------
// Constructor 
template <typename T>
List<T>::List() {
   head = NULL;
}

//----------------------------------------------------------------------------
// Copy Constructor 
template <typename T>
List<T>::List(const List& aList) {
   head = NULL;
   *this = aList;
}

//----------------------------------------------------------------------------
// Destructor 
template <typename T>
List<T>::~List() {
   makeEmpty();
}

//----------------------------------------------------------------------------
// isEmpty 
// check to see if List is empty as defined by a NULL head
template <typename T>
bool List<T>::isEmpty() const {
   return head == NULL;
}

//----------------------------------------------------------------------------
// insert 
// insert an item into list; operator< of the T class
// has the responsibility for the sorting criteria
template <typename T>
bool List<T>::insert(T* dataptr) {                    

   Node* ptr = new Node;
   if (ptr == NULL) return false;                 // out of memory, bail
   ptr->data = dataptr;                           // link the node to data

   // if the list is empty or if the node should be inserted before 
   // the first node of the list
   if (isEmpty() || *ptr->data < *head->data) {
      ptr->next = head;                           
      head = ptr;
   }
     
   // then check the rest of the list until we find where it belongs 
   else {
      Node* current = head->next;          // to walk list
      Node* previous = head;               // to walk list, lags behind

      // walk until end of the list or found position to insert
      while (current != NULL && *current->data < *ptr->data) {
            previous = current;                  // walk to next node
            current = current->next;
      }

      // insert new node, link it in
      ptr->next = current; 
      previous->next = ptr; 
   }
   return true;
}

//----------------------------------------------------------------------------
// buildList 
// continually insert new items into the list
template <typename T>
void List<T>::buildList(ifstream& infile) {
   T* ptr;
   bool successfulRead;                            // read good data
   bool success;                                   // successfully insert
   for (;;) {
      ptr = new T;
      successfulRead = ptr->setData(infile);       // fill the T object
      if (infile.eof()) {
         delete ptr;
         break;
      }

      // insert good data into the list, otherwise ignore it
      if (successfulRead) {
         success = insert(ptr);
      }
      else {
         delete ptr;
      }
      if (!success) break;
   }
}

//----------------------------------------------------------------------------
// makeEmpty
// empty out the list, deallocate all memory for all Nodes and each Object
template <typename T>
void List<T>::makeEmpty() {
   // current is to walk through the list and temp is for deleting
   Node *current, *temp;
   current = head;

   // while end of list has not been reached
   while (current != NULL) {
      temp = current;
      current = current->next;
      delete temp->data; // delete data
      delete temp; // delete node
   }

   head = NULL;
}

//----------------------------------------------------------------------------
// retrieve 
// similar to remove, but not removed from list.  If there are duplicates in 
// the list, the first one encountered is retrieved.  Second parameter is 
// unreliable if return value is false. 
template <typename T>
bool List<T>::retrieve(const T& target, T*& dataptr) {
   Node *current = head;

   // while end of this list has not been reached
   while (current != NULL) {
      // if target has been found
      if (*current->data == target) {
         dataptr = current->data; // assign dataptr param
         return true;
      }

      current = current->next; // move to next item if target not found
   }

   return false; // unsuccessful
}

//----------------------------------------------------------------------------
// remove 
// remove first parameter, the object, from the list and set the second 
// (pass by reference) parameter to the Object*from the list if it is  found. 
// The return value is whether the removal was successful. Second parameter is 
// unreliable if false is returned.
template <typename T>
bool List<T>::remove(const T& target, T*& dataptr) {
   // current is to walk through list, prev is node before current
   Node *current = head, *prev = NULL;

   // while end of this list has not been reached
   while (current != NULL) {

      // if target found
      if (*current->data == target) {
         dataptr = current->data; // assign data to second param

         // if current is still head 
         if (prev == NULL)
            head = current->next; // make list's head next item

         // otherwise unlink/remove current from list
         else
            prev->next = current->next; //make prev's next equal current's next

         delete current; // delete current node
         current = NULL;

         return true; // success
      }

      prev = current;
      current = current->next; // move to next item in list if target not found
   }

   return false; // unsuccessful
}

//----------------------------------------------------------------------------
// merge 
// takes 2 sorted lists and merge into one long sorted list (No new memory is 
// allocated. At termination of function, the two parameter lists are empty 
// unless one is also the current object.  Duplicates are allowed in a merged 
// list.)  Doesn't do anything if both parameters are this.
template <typename T>
void List<T>::merge(List<T>& A, List<T>& B) {
   // currentA is to walk through A, currentB for B, mergeHead represents the 
   // head of the merged list, temp is for assigning everything after mergeHead
   Node *currentA = A.head, *currentB = B.head, *mergeHead = NULL,*temp = NULL;

   for (;;) {
      // stop merging when end of both parameter list is reached
      if (currentA == NULL && currentB == NULL)
         break;

      // if both parameters are this, then no need to merge
      else if (this == &A && this == &B)
         break;

      // if both parameters have the same reference, then merge one and break
      else if (&A == &B) {
         mergeHead = currentA;
         break;
      }

      // if first parameter is empty
      else if (currentA == NULL) {
         // if merged list is empty then assign second list's head 
         if (mergeHead == NULL)
            mergeHead = currentB;

         // otherwise assign rest of second list to end of merged list
         else
            temp->next = currentB;

         // end merge
         break;
      }

      // same thing as above except for the other parameter
      else if (currentB == NULL) {
         if (mergeHead == NULL)
            mergeHead = currentA;

         else
            temp->next = currentA;

         break;
      }

      // else if first parameter's current data is less than second list
      else if (*currentA->data < *currentB->data) {
         // check if merged list is empty
         if (mergeHead == NULL) {
            mergeHead = currentA; // first list's head becomes merged head
            temp = mergeHead;
         }

         // otherwise assign currentA to end of merged list
         else {
            temp->next = currentA;
            temp = temp->next;
         }

         // move to next item in first list
         currentA = currentA->next;
      }

      // same thing as above except for other parameter
      else {
         if (mergeHead == NULL) {
            mergeHead = currentB;
            temp = mergeHead;
         }

         else {
            temp->next = currentB;
            temp = temp->next;
         }

         currentB = currentB->next;
      }
   }

   // if this and A are not the same reference
   if (this != &A)
      A.head = NULL; // empty A

   // if this and B are not the same reference
   if (this != &B)
      B.head = NULL; // empty B

   // if this and A and B are not the same reference
   if (this != &A && this != &B) {
      makeEmpty(); // empty this
      head = mergeHead; // assign mergeHead to this list's head
   }
}

//----------------------------------------------------------------------------
// intersect 
// takes 2 sorted lists and finds the items in common in both lists (New 
// memory is allocated; at termination of the function, the two parameter 
// lists are unchanged unless one is also the current object.)  
template <typename T>
void List<T>::intersect(const List<T>& A, const List<T>& B) {
   // currentA is to walk through A, currentB for B, intersectHead represents 
   // the head of the intersected list
   Node *currentA = A.head, *currentB = B.head, *intersectHead = NULL,
      // temp is for assigning everything after intersectHead
      *temp = NULL;

   for (;;) {
      // if the end of either list is reached, then nothing left to intersect
      if (currentA == NULL || currentB == NULL)
         break; // intersect is done

      // if the current data at both lists are the same, then place into 
      // intersected list
      else if (*currentA->data == *currentB->data) {
         T *dataPtr = new T(*currentA->data); // make a deep copy of the data

         // if the intersected list is empty
         if (intersectHead == NULL) {
            intersectHead = new Node; 
            intersectHead->data = dataPtr; // set intersected list's head
            intersectHead->next = NULL;
            temp = intersectHead;
         }

         // otherwise add the data to the end of the intersected list
         else {
            temp->next = new Node;
            temp = temp->next;
            temp->data = dataPtr;
            temp->next = NULL;
         }

         // go to next item in both parameters
         currentA = currentA->next;
         currentB = currentB->next;
      }

      // if first list's current data is less than second list's data
      else if (*currentA->data < *currentB->data)
         currentA = currentA->next; // go to next item in first list

      // if second list's current data is less than first list's data
      else
         currentB = currentB->next; // go to next item in second list until 
                                    // greater than or equal to first list
   }

   // empty this list
   makeEmpty();
   head = intersectHead; // make this list's head the intersected list's head
   if (!isEmpty())
      temp->next = NULL;
}

//----------------------------------------------------------------------------
// operator=
// to assign one list to another, deep copy (all new memory) 
template <typename T>
List<T>& List<T>::operator=(const List<T>& rhs) {
   // make sure this isn't the same as right hand side
   if (this != &rhs) {
      if (!isEmpty()) // if not the same, then empty list if not empty
         makeEmpty();

      // current to walk through rhs, temp to assign everything after head
      Node *current = rhs.head, *temp = NULL;

      // while end of rhs is not reached
      while (current != NULL) {
         T* dataptr = new T(*current->data); // make deep copy of rhs data

         // if this list is empty, then assign head
         if (isEmpty()) {
            head = new Node;
            head->data = dataptr;
            head->next = NULL;
            temp = head;
         }
         
         // otherwise add a node after last item
         else {
            temp->next = new Node;
            temp = temp->next;
            temp->data = dataptr;
            temp->next = NULL;
         }

         current = current->next; // move to next item in rhs
      }
   }

   return *this;
}

//----------------------------------------------------------------------------
// operator==
// compare two lists, == is true if the lists hold identical Objects as 
// defined by Object’s operator==
template <typename T>
bool List<T>::operator==(const List<T>& rhs) const {
   // if this and rhs are the same reference, then they are same
   if (this == &rhs)
      return true;

   // left is to walk through this list and right is for rhs
   Node *left = head, *right = rhs.head;

   // while end of this and rhs is not reached
   while (left != NULL && right != NULL) {
      if (*left->data != *right->data) // if the current data at this and rhs
         return false;                 // are not equal, then return false

      left = left->next; // move to next item in both lists
      right = right->next;
   }

   // if the end of one list was reached, but not the other
   if (left != NULL || right != NULL)
      return false; // then this and rhs are not equal

   return true; // they are equal if this point has been reached
}

//----------------------------------------------------------------------------
// operator!=
// compares two lists, != is true if the lists hold different Objects
template <typename T>
bool List<T>::operator!=(const List<T>& rhs) const {
   return !(*this == rhs);
}

template <typename T>
void List<T>::doSomethingTotallyWeird() {
   if (isEmpty()) return;
   int i = 0;
   Node *current = head;
   while (current != NULL && i < 2) {
         i++;
         current = current->next;
   }
   if (current == NULL) return;
   Node *p = head, *p2 = head->next;
   while (current != NULL) {
      p->next = new Node;
      p = p->next;
      p->data = current->data;
      current = current->next;
   }
   p->next = p2;
}

#endif

