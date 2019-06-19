#ifndef FIRM_H
#define FIRM_H

#include <fstream>
#include "BSTree.h"
#include "queue.h"
#include "client.h"
#include "transaction.h"

using namespace std;

//----------------------------------------------------------------------------
// class Firm
//
// Firm: stores a BSTree of all clients and a Queue of transactions to be 
//       processed.       
//
// Implementation and assumptions:
//    -- Assumes client and transaction data files are formatted correctly
//    -- Requires BSTree to store Clients and Queue to store Transactions
//----------------------------------------------------------------------------

class Firm {
public:
   Firm();
   ~Firm();

   void buildClientTree(ifstream&);
   void buildTransactionQueue(ifstream&);
   void processTransactions();
   void displayClientInformation() const;

private:
   BSTree* clientTree;
   Queue* transactionQueue;

   void deposit(Transaction*, const Client&);
   void withdraw(Transaction*, const Client&);
   void move(Transaction*, const Client&);
   void history(Transaction*, const Client&);
   bool validateID(Transaction*) const;
};
#endif // !FIRM_H

