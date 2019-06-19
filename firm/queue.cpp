#include "queue.h"

//------------------------------ constructor ---------------------------------
Queue::Queue() {
   front = rear = NULL;
}

//------------------------------ destructor ----------------------------------
Queue::~Queue() {
   clear();
}

//------------------------------ copy constructor ----------------------------
Queue::Queue(const Queue& q) {
   Node *current = q.front;

   while (current != nullptr) {
      Transaction* t = new Transaction(*current->data);
      enqueue(t);
      current = current->next;
   }
}

//------------------------------ clear ---------------------------------------
// empties the queue
void Queue::clear() {
   if (isEmpty()) return;

   Transaction* tran;

   while (dequeue(tran)) {
      delete tran;
      tran = nullptr;
   }

   front = rear = nullptr;
}

//------------------------------ isEmpty -------------------------------------
// check to see if queue is empty
bool Queue::isEmpty() const {
   return (front == nullptr);
}

//------------------------------ enqueue -------------------------------------
// insert item into rear of queue
bool Queue::enqueue(Transaction* dataptr) {                    

   Node* nodeptr = new Node;                      
   if (nodeptr == nullptr) {
      delete dataptr;
      return false;
   }
   nodeptr->data = dataptr;
   nodeptr->next = nullptr;

   // link at front if empty, otherwise at the rear
   if (isEmpty())
      front = nodeptr;                            
   else
      rear->next = nodeptr;                       
   rear = nodeptr;                                // either way, rear is set
   return true;
}

//---------------------------------- dequeue ---------------------------------
// remove item from front of queue
bool Queue::dequeue(Transaction*& dataptr) {                    
   if (isEmpty())
      return false;
   
   dataptr = front->data;                  
   Node* nodeptr = front;
   front = front->next;              
   if (isEmpty())
      rear = nullptr;                   // if it's the last node in list
   delete nodeptr;
   nodeptr = nullptr;
   return true;
}

//---------------------------------- peek ------------------------------------
// return item at front of queue
bool Queue::peek(Transaction*& dataptr) const {                    
   if (isEmpty())
      return false;
   
   dataptr = front->data;
   return true;
}

//---------------------------------- operator<< ------------------------------
// prints the queue
ostream& operator<<(ostream& output, const Queue& queue) {
   Queue::Node* current = queue.front;

   while (current != nullptr) {
      output << *current->data;
      current = current->next;
   }

   return output;
}