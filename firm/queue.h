#ifndef QUEUE_H
#define QUEUE_H

#include "transaction.h"
#include <iostream>

using namespace std;

//----------------------------------------------------------------------------
// class Queue 
//
// ADT Queue: collection of zero or more items (list) with the restriction that
//            all insertions happen at one end, called the rear of the queue, 
//            and all removals occur at the other end, the front
//            (also known as FIFO -- First In, First Out)
//
// Implementation and assumptions:
//    -- Node (linked list implementation) is a struct made of just
//       a Transaction* and a Node*
//    -- The push allocates memory for a Node, ptr to the data is passed in.
//----------------------------------------------------------------------------

class Queue {
   friend ostream &operator<<(ostream&, const Queue&);

public:
   Queue();                                   // default constructor
   ~Queue();                                  // destructor
   Queue(const Queue&);                       // copy constructor
   void clear();                              // clear out queue
   bool isEmpty() const;                      // is the queue empty?


   // insert item, assume object passed in is valid, return whether successful
   bool enqueue(Transaction*);                  

   // remove item, parameter is removed item, return whether item is removed 
   bool dequeue(Transaction*&);                  

   // retrieve item, parameter is item at top, return whether item exists
   bool peek(Transaction*&) const;

private:
   struct Node {
      Transaction* data;
      Node* next;
   };

   Node* front;                               // pointer to front of queue
   Node* rear;                                // pointer to rear of queue
};

#endif

