#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

//----------------------------------------------------------------------------
// class Transaction
//
// Transaction: stores information about a transaction including command type,
//              id of the client that the transaction is performed on, account  
//              that the transaction is performed on, transaction amount, and
//              the id and account the amount is being moved to if the 
//              transaction command is Move. 
//
// Implementation and assumptions:
//    -- setData assumes transaction data file is formatted correctly and 
//       returns false if the given amount is less than zero or the command is 
//       not D, W, M, or H.
//----------------------------------------------------------------------------

class Transaction {
   friend ostream& operator<< (ostream&, const Transaction&);

public:
   Transaction(char = '^', int = 0, int = -1, int = -1, int = 0, int = -1);
   ~Transaction();

   bool setData(ifstream&);

   char getCommand() const;
   int getClientID() const;
   int getAccount() const;
   int getAmount() const;
   int getToClientID() const;
   int getToAccount() const;

   string getAccountName(int) const;

private:
   char command;
   int clientID;
   int account;
   int amount;
   int toClientID;
   int toAccount;

   bool isValidCommand() const;
   bool isValidAmount() const;
};

#endif // !TRANSACTION_H

