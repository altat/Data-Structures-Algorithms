#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "queue.h"

using namespace std;

const int MAX_CLIENT_ACCOUNTS = 10;
const int MIN_CLIENT_ID = 1000;
const int MAX_CLIENT_ID = 9999;
const int MoneyMarket = 0;
const int PrimeMoneyMarket = 1;
const int LongTermBond = 2;
const int ShortTermBond = 3;

//----------------------------------------------------------------------------
// class Client
//
// Client: stores information about a client including last name, first name,
//         unique 4 digit id, balances for 10 accounts, and transaction 
//         history for each account. 
//
// Implementation and assumptions:
//    -- Account is a struct made of two ints
//    -- Transaction history is stored in a Queue
//    -- Uses Queue's enqueue and operator<<
//    -- setData assumes the client data file is formatted correctly and will
//       return false if the id is less than or greater than 4 digits.
//    -- withdraw money will use money from money market and bond accounts
//       if insufficient funds in one of the afformentioned account types.
//----------------------------------------------------------------------------

class Client {
   friend ostream& operator<< (ostream&, const Client&);

public:
   Client();
   Client(int);
   ~Client();

   bool setData(ifstream&);
   void addHistory(Transaction*);
   void displayHistory() const;
   bool depositMoney(Transaction*);
   bool withdrawMoney(Transaction*);

   int getID() const;

   bool operator<(const Client&) const;
   bool operator>(const Client&) const;
   bool operator==(const Client&) const;
   bool operator!=(const Client&) const;

private:
   string last;
   string first;
   int id;

   struct Account {
      int initialBalance = 0;
      int finalBalance = 0;
   };

   Account* accounts[MAX_CLIENT_ACCOUNTS]; 
   Queue* history;

   bool coverFunds(Transaction*, int, int);
   bool isValidID() const;
};

#endif // !CLIENT_H
