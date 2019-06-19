#include "client.h"

//------------------------------ constructor ---------------------------------
Client::Client() {
   // loop over 10 accounts
   for (int i = 0; i < MAX_CLIENT_ACCOUNTS; i++)
      accounts[i] = nullptr;

   history = nullptr;
}

//------------------------------ constructor ---------------------------------
Client::Client(int id) {
   for (int i = 0; i < MAX_CLIENT_ACCOUNTS; i++)
      accounts[i] = nullptr;

   this->id = id;
   history = nullptr;
}

//------------------------------ destructor ----------------------------------
Client::~Client() {
   // delete each account
   for (int i = 0; i < MAX_CLIENT_ACCOUNTS; i++) {
      if (accounts[i] != nullptr) {
         delete accounts[i];
         accounts[i] = nullptr;
      }
   }

   if (history != nullptr) {
      delete history;
      history = nullptr;
   }
}

//------------------------------ setData -------------------------------------
// sets the member variables for a Client using data from a text file
bool Client::setData(ifstream& infile) {
   infile >> last >> first >> id;

   Account* account;

   // sets balances for all 10 accounts and adds to accounts array
   for (int i = 0; i < MAX_CLIENT_ACCOUNTS; i++) {
      account = new Account;
      infile >> account->initialBalance;

      account->finalBalance = account->initialBalance;
      accounts[i] = account;
   }

   return (last.length() > 0 && first.length() > 0 && isValidID());
}

//------------------------------ addHistory ----------------------------------
// Adds a Transaction to a Client's history Queue. 
void Client::addHistory(Transaction* tran) {
   if (history == nullptr) history = new Queue;

   history->enqueue(tran);
}

//------------------------------ displayHistory ------------------------------
// Displays a Client's Transaction history. Prints the history Queue.
void Client::displayHistory() const {
   if (history == nullptr) return;

   cout << endl << "History of transactions for client " << first << " " << 
      last << ", client ID = " << id << endl;

   cout << "Type      Amount  Detail" << endl;

   cout << "--------- ------- --------------------------------------" << endl;

   cout << *history;
}

//------------------------------ depositMoney --------------------------------
// Adds the amount specified in the Transaction to the specified account.
bool Client::depositMoney(Transaction* tran) {
   int amount = tran->getAmount();
   int account = tran->getAccount();

   if (account < 0 || account > MAX_CLIENT_ACCOUNTS || amount < 0) 
      return false;

   accounts[account]->finalBalance += amount;
   return true;
}

//------------------------------ withdrawMoney -------------------------------
// Withdraws the amount specified in the Transaction to the specified account.
bool Client::withdrawMoney(Transaction* tran) {
   int amount = tran->getAmount();
   int account = tran->getAccount();

   if (account < 0 || account > MAX_CLIENT_ACCOUNTS || amount < 0) 
      return false;

   // Withdraw if sufficient funds in specified account
   if (accounts[account]->finalBalance >= amount) {
      accounts[account]->finalBalance -= amount;
      return true;
   }

   // if not sufficient and MoneyMarket type account, then cover funds
   // using money from other MoneyMarket type account.
   else if (account == MoneyMarket || account == PrimeMoneyMarket) {
      return coverFunds(tran, MoneyMarket, PrimeMoneyMarket);
   }

   // if not sufficient and Bond type account, then cover funds
   // using money from other Bond type account.
   else if (account == LongTermBond || account == ShortTermBond) {
      return coverFunds(tran, LongTermBond, ShortTermBond);
   }

   // otherwise don't perform withdrawal since insufficient funds
   else {
      cout << endl << "Withdrawal not performed on " << 
         tran->getAccountName(account) << " for client " << id << ";" << 
         endl << setw(23) << "insufficient funds" << endl;
      return false;
   }
}

//------------------------------ coverFunds ----------------------------------
// Uses funds from both Money Market/Bond accounts to perform withdrawal
// Only used by withdrawMoney
bool Client::coverFunds(Transaction* tran, int A, int B) {
   int amount = tran->getAmount();
   int account = tran->getAccount();

   // if combined balances from both accounts is enough to cover the withdraw
   if (accounts[A]->finalBalance + accounts[B]->finalBalance >= amount) {

      // find difference needed to withdraw the full amount
      int partialAmount = amount - accounts[account]->finalBalance;
      accounts[account]->finalBalance = 0;

      // withdraw the partial amount from the other account
      int otherAccount = (account == A) ? B : A;
      accounts[otherAccount]->finalBalance -= partialAmount;

      return true;
   }

   // funds cannot be covered so withdrawal not performed
   else {
      cout << endl << "Withdrawal not performed on " << 
         tran->getAccountName(account) << " for client " << id << ";" << 
         endl << setw(23) << "insufficient funds" << endl;
      return false;
   }
}

//------------------------------ getID ---------------------------------------
// returns id member variable
int Client::getID() const {
   return id;
}

//------------------------------ operator< -----------------------------------
// returns whether this' id is less than rhs' id
bool Client::operator<(const Client& rhs) const {
   return (this->id < rhs.id);
}

//------------------------------ operator> -----------------------------------
bool Client::operator>(const Client& rhs) const {
   return (this->id > rhs.id);
}

//------------------------------ operator== ----------------------------------
// return whether this' id is equal to rhs' id
bool Client::operator==(const Client& rhs) const {
   return (this->id == rhs.id);
}

//------------------------------ operator!= ----------------------------------
bool Client::operator!=(const Client& rhs) const {
   return (this->id != rhs.id);
}

//------------------------------ isValidID -----------------------------------
// return whether id member variable is valid
bool Client::isValidID() const {
   return (id > MIN_CLIENT_ID && id < MAX_CLIENT_ID);
}

//------------------------------ operator<< ----------------------------------
// outputs Client information
ostream& operator<< (ostream& output, const Client& rhs) {
   output << endl << rhs.id << "  " << rhs.first << " " << rhs.last << endl 
      << "Initial Balances: ";

   for (int i = 0; i < MAX_CLIENT_ACCOUNTS; i++)
      output << setw(6) << rhs.accounts[i]->initialBalance;

   output << endl << "Final Balances:   ";

   for (int i = 0; i < MAX_CLIENT_ACCOUNTS; i++)
      output << setw(6) << rhs.accounts[i]->finalBalance;

   return output;
}