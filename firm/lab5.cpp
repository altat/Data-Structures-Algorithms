#include <iostream>
#include "firm.h"

using namespace std;

int main() {
   ifstream clientFile("lab5data.txt");
   if (!clientFile) {
      cout << "File could not be opened." << endl;
      return 1;
   }

   ifstream commandFile("lab5command.txt");
   if (!commandFile) {
      cout << "File could not be opened." << endl;
      return 1;
   }

   Firm LOSE;

   LOSE.buildClientTree(clientFile);
   LOSE.buildTransactionQueue(commandFile);
   LOSE.processTransactions();
   LOSE.displayClientInformation();

   return 0;
}