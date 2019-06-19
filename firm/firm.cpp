#include "firm.h"

//------------------------------ constructor ---------------------------------
Firm::Firm() {
   clientTree = new BSTree;
   transactionQueue = new Queue;
}

//------------------------------ destructor ----------------------------------
Firm::~Firm() {
   delete clientTree;
   delete transactionQueue;
}

//------------------------------ buildClientTree -----------------------------
// Adds clients from data file to BSTree
void Firm::buildClientTree(ifstream& infile) {
   Client* clientptr;     // Client to be inserted
   bool successfulRead;   // read good data
   bool success = false;  // successfully inserted

   for (;;) {
      clientptr = new Client;
      successfulRead = clientptr->setData(infile); // fill Client
      
      if (infile.eof()) {
         delete clientptr;
         break;
      }

      // insert good data into the list, otherwise ignore it
      if (successfulRead) success = clientTree->insert(clientptr);
      else delete clientptr;

      if (!success) break;
   }
}

//------------------------------ builTransactionQueue ------------------------
// Adds transactions from data file to Queue
void Firm::buildTransactionQueue(ifstream& infile) {
   Transaction* transaction;    // Transaction to be inserted
   bool successfulRead;         // read good data
   bool success = false;        // successfully insert

   for (;;) {
      transaction = new Transaction;
      successfulRead = (transaction->setData(infile) && 
         validateID(transaction)); // file transaction and check ID
      
      if (infile.eof()) {
         delete transaction;
         break;
      }

      // insert good data into the list, otherwise ignore it
      if (successfulRead) success = transactionQueue->enqueue(transaction);
      else delete transaction;

      if (!success) break;
   }
}

//------------------------------ processTransactions -------------------------
// Removes one Transaction from transactionQueue and processes it
void Firm::processTransactions() {
   Transaction* transactionPtr;

   while (transactionQueue->dequeue(transactionPtr)) {
      char type = transactionPtr->getCommand(); // transaction type
      int id = transactionPtr->getClientID();   // id of client 
      Client target(id); // target Client to perform transaction on

      switch (type) {
      case 'D': deposit(transactionPtr, target);  break;
      case 'W': withdraw(transactionPtr, target); break;
      case 'M': move(transactionPtr, target);     break;
      case 'H': history(transactionPtr, target);  break;
      default:  delete transactionPtr;            break;
      }
   }
}

//------------------------------ displayClientInformation --------------------
// prints a report of each Client's account balances 
void Firm::displayClientInformation() const {
   cout << endl << "REPORT" << endl;
   clientTree->display();
}

//------------------------------ deposit -------------------------------------
// processes a deposit type transaction (deposits money into the target 
// Client account)
void Firm::deposit(Transaction* tran, const Client& target) {
   Client* clientPtr;

   // if target client can be retrieved
   if (clientTree->retrieve(target, clientPtr)) {

      // then deposit money and add to client's transaction history
      if (clientPtr->depositMoney(tran)) {
         clientPtr->addHistory(tran);
      }

      else delete tran;
   }

   else delete tran;
}

//------------------------------ withdraw ------------------------------------
// processes a withdraw type transaction (withdraws money from the target 
// Client account)
void Firm::withdraw(Transaction* tran, const Client& target) {
   Client* clientPtr;

   // if target Client can be retrieved, withdraw money and add to history
   if (clientTree->retrieve(target, clientPtr)) {
      if (clientPtr->withdrawMoney(tran)) {
         clientPtr->addHistory(tran);
      }

      else delete tran;
   }

   else delete tran;
}

//------------------------------ move ----------------------------------------
// processes a Move type transaction (Moves money from the target Client 
// account to the other target account.
void Firm::move(Transaction* tran, const Client& target) {
   Client* clientPtr;

   Client toTarget(tran->getToClientID());
   Client* toClientPtr;

   // if both clients exist in the clientTree
   if (clientTree->retrieve(target, clientPtr) &&
      clientTree->retrieve(toTarget, toClientPtr)) {

      // make copy of transaction so it can be added to both client's history
      int id = tran->getToClientID();
      int acc = tran->getToAccount();
      int amount = tran->getAmount();
      Transaction* copy = new Transaction('D', id, acc, amount);
      
      // if money can be withdrawed from first client
      if (clientPtr->withdrawMoney(tran)) {
         toClientPtr->depositMoney(copy); // then deposit into second client
         clientPtr->addHistory(tran);     // and add to both clients' history
         toClientPtr->addHistory(copy);
      }

      else {
         delete tran;
         delete copy;
      }
   }

   else delete tran;
}


//------------------------------ history -------------------------------------
// processes a history type transaction (prints a client's transaction history)
void Firm::history(Transaction* tran, const Client& target) {
   Client* clientPtr;

   // if Client can be retrieved, display transaction history including tran
   if (clientTree->retrieve(target, clientPtr)) {
      clientPtr->addHistory(tran);
      clientPtr->displayHistory();
   }

   else delete tran;
}

//------------------------------ validateID ----------------------------------
// returns true if the Client IDs in a Transaction are valid
bool Firm::validateID(Transaction* tran) const {
   bool valid;
   int id = tran->getClientID();

   // if Move type transaction, then check two IDs
   if (tran->getCommand() == 'M') {
      int toID = tran->getToClientID();
      valid = (clientTree->find(id) && clientTree->find(toID));

      if (!valid) cout << "Unknown client ID " << id << " or " << toID <<
         " requested" << endl;
   }

   // otherwise check one ID.
   else {
      valid = clientTree->find(id);

      if (!valid) cout << "Unknown client ID " << id << " requested" << endl;
   }

   return valid;
}