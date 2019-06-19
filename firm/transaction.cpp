#include "transaction.h"

//------------------------------ constructor ---------------------------------
Transaction::Transaction(char c, int id, int acc, int a, int toId, int toAcc) {
   command = c;
   clientID = id;
   account = acc;
   amount = a;
   toClientID = toId;
   toAccount = toAcc;
}

//------------------------------ destructor ----------------------------------
Transaction::~Transaction() {

}

//------------------------------ setData -------------------------------------
// sets data for Transaction
bool Transaction::setData(ifstream& infile) {
   infile >> command >> clientID;

   // if History type transaction, then stop
   if (command == 'H') return true;

   infile >> amount;

   account = clientID % 10;
   clientID /= 10;

   if (command == 'M') {
      infile >> toClientID;
      toAccount = toClientID % 10;
      toClientID /= 10;
   }

   return (isValidCommand() && isValidAmount());
}

//------------------------------ getCommand ----------------------------------
char Transaction::getCommand() const {
   return command;
}

//------------------------------ getClientID ---------------------------------
int Transaction::getClientID() const {
   return clientID;
}

//------------------------------ getAccount ----------------------------------
int Transaction::getAccount() const {
   return account;
}

//------------------------------ getAmount -----------------------------------
int Transaction::getAmount() const {
   return amount;
}

//------------------------------ getToClientID -------------------------------
int Transaction::getToClientID() const {
   return toClientID;
}

//------------------------------ getToAccount --------------------------------
int Transaction::getToAccount() const {
   return toAccount;
}

//------------------------------ getAccountName ------------------------------
string Transaction::getAccountName(int account) const {
   string accountName;

   switch (account) {
   case 0: accountName = "Money Market fund";       break;
   case 1: accountName = "Prime Money Market fund"; break;
   case 2: accountName = "Long-Term Bond fund";     break;
   case 3: accountName = "Short-Term Bond fund";    break;
   case 4: accountName = "500 Index fund";          break;
   case 5: accountName = "Capital Value fund";      break;
   case 6: accountName = "Growth Equity fund";      break;
   case 7: accountName = "Growth Index fund";       break;
   case 8: accountName = "Value Fund fund";         break;
   case 9: accountName = "Value Stock fund";        break;
   default:accountName = "Invalid Account fund";    break;
   }

   return accountName;
}

//------------------------------ isValidCommand ------------------------------
// returns whether command member variable is valid
bool Transaction::isValidCommand() const {
   // valid if D, W, M, or H
   if (command == 'D' || command == 'W' || command == 'M' || command == 'H')
      return true;

   // default value in transaction.h is ^
   else if (command == '^') return false;

   else {
      cout << "Unknown transaction type '" << command << "' requested" << endl;
      return false;
   }
}

//------------------------------ isValidAmount -------------------------------
// returns whether amount is valid (greater than zero)
bool Transaction::isValidAmount() const {
   if (amount < 0) {
      cout << "Invalid amount " << amount << " requested" << endl;
      return false;
   }

   return true;
}

//------------------------------ operator<< ----------------------------------
// outputs Transaction information
ostream& operator<< (ostream& output, const Transaction& rhs) {
   string type;
   string preposition;
   string account;
   string accountName = rhs.getAccountName(rhs.account);

   switch (rhs.command)
   {
   case 'D': type = "deposit";  preposition = " into ";    break;
   case 'W': type = "withdraw"; preposition = " from ";    break;
   case 'M': type = "move";     preposition = " from ";    break;
   case 'H': output << "history" << endl;                  return output;
   }

   output << left << setw(10) << type << "$" << right << setw(6) << rhs.amount
      << preposition << accountName << endl;

   if (rhs.command == 'M') {
      string toAccountName = rhs.getAccountName(rhs.toAccount);
      output << setw(21) << " to " << toAccountName << " for client " <<
         rhs.toClientID << endl;
   }

   return output;
}