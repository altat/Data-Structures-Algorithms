//-----------------------------------------------------------------------------
// Modified By: Tanvir Tatla
// Date: 4/7/19
//
// lab1 reads student data from a file and inserts that data into an array 
// alphabetically (checks last name first and then first name). 
// Display student and class data
// Data includes list of students' grade, last name, and first name. Also 
// displays a histogram of grades and calculates average grade. For example:
// 
// List of names sorted:
//  65  duck donald
//  60  frog freddie
//  95  mouse minnie
//
// Histogram of grades:
//    0-->   9:
//   10-->  19:
//   20-->  29:
//   30-->  39:
//   40-->  49:
//   50-->  59:
//   60-->  69: **
//   70-->  79: 
//   80-->  89:
//   90-->  99: *
//  100--> 100:
//
// Average grade: 73
//
// Assumptions, implementation details:  
//    -- file called data1.txt exists
//    -- Format of data is correct and complete.
//    -- An empty file will result an empty name list, empty histogram, and 
//       average grade of 0. Incomplete data and subsequent lines are omitted.
//    -- All names are no more in length than MAXLENGTH.
//    -- grades are correctly sized as integers.
//    -- grades below 0 or above 100 are ignored
//    -- Data beyond MAXSIZE number of names is not stored in the list.

#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int const MAXSIZE = 100;            // maximum number of records in total
int const MAXLENGTH = 31;           // maximum string length 
int const MAXGRADE = 100;           // highest possible grade
int const LOWGRADE = 0;             // lowest possible grade
int const GROUP = 10;               // group amount
int const HISTOGRAMSIZE = (MAXGRADE - LOWGRADE) / GROUP + 1; //grouped by GROUP

struct StudentType {               // information of one student
   int grade;                       // the grade of the student
   char last[MAXLENGTH];            // last name (MAXLENGTH-1 at most)
   char first[MAXLENGTH];           // first name (MAXLENGTH-1 at most)
};

// prototypes go here
bool sortInput(ifstream&, StudentType[], int&);
void displayList(StudentType[], int);
void setHistogram(int[], StudentType[], int);
void displayHistogram(int[]);
int findAverage(StudentType[], int);

//-----------------------------------------------------------------------------
int main() {   
   StudentType students[MAXSIZE];   // list of MAXSIZE number of students
   int size = 0;                    // total number of students
   int histogram[HISTOGRAMSIZE];    // grades grouped by GROUP
   int average = 0;                 // average exam score, truncated

   // creates file object and opens the data file
   ifstream infile("data1.txt");
   if (!infile) {
      cout << "File could not be opened." << endl;
      return 1;
   }

   // read and sort input by last then first name
   bool successfulRead = sortInput(infile, students, size);

   // display list, histogram, and class average 
   if (successfulRead) {
      displayList(students, size);
      setHistogram(histogram, students, size);
      displayHistogram(histogram);
      average = findAverage(students, size);
      cout << "Average grade: " << average << endl << endl;
   }
   return 0;
}

// ----------------------------------------------------------------------------
// functions go here

// ----------------------------------------------------------------------------
// sortInput 
// reads file (first parameter), Insertion sorts data into array (second 
// parameter) by alphabetical order of last and first names. Stops inserting 
// once it encounters improperly formatted data. 
// Increments size (third parameter) by 1 for every valid student.
// Assumes file has been opened.
bool sortInput(ifstream& infile, StudentType students[], int& size) {
   StudentType temp; // temporary Student data

   // loops until improperly formatted data is read. Also sets student data.
   while (size < MAXSIZE && infile >> temp.last >> temp.first >> temp.grade) {
      
      // if temp student's grade is a possible grade
      if (temp.grade <= MAXGRADE && temp.grade >= LOWGRADE) {
         int i = size; // index starts at end of the filled part of the array
         
         // loop from the end of the filled part of the array down to beginning
         for (i; i > 0; i--) {
            
            // compare temp student's last name to current student's last name
            int lastComparison = strcmp(temp.last, students[i - 1].last);

            // if temp student's last name comes before current's last name OR 
            // temp and current's last name are the same but temp's first name
            // comes before current's first name
            if (lastComparison < 0 || (lastComparison == 0 &&
               strcmp(temp.first, students[i - 1].first) < 0)) 
            {
               students[i] = students[i-1]; // copy current student's data 
                                            // (shift data to the right)
            }

            else break; // found right place to insert new data
         }

         students[i] = temp; // insert new data into correct sorted position
         size++;
      }
   }

   return true;
}

// ----------------------------------------------------------------------------
// displayList 
// print the list of students in given array for size number of items
void displayList(StudentType students[], int size) {
   cout << "List of names sorted:" << endl;

   // loop over filled in part of students array
   for (int i = 0; i < size; i++) {
      // print grade, last name, first name
      cout << setw(3) << students[i].grade << " " << students[i].last << " "
         << students[i].first << endl;
   }

   cout << endl;
}

// ----------------------------------------------------------------------------
// setHistogram
// Calculates bar size of histogram of grades
void setHistogram(int histogram[], StudentType students[], int size) {
   int i = 0;

   // sets each value in histogram array to zero
   for (i; i < HISTOGRAMSIZE; i++) {
      histogram[i] = 0;
   }

   // loop over students
   for (i = 0; i < size; i++) {
      // grade range (6 represents 60-69 range)
      int range = students[i].grade / 10; // example: 65 / 10 = 6
      histogram[range]++;
   }
}

// ----------------------------------------------------------------------------
// displayHistogram
// prints Histogram of grades
// assumes setHistogram has been called
void displayHistogram(int histogram[]) {
   cout << "Histogram of grades:" << endl;

   // loop over histogram array
   for (int i = 0; i < HISTOGRAMSIZE; i++) {
      // i = 0, 1, 2, 3, 4...  minRange = 0, 10, 20, 30, 40...
      int minRange = i * 10;

      // i = 0, 1, 2, 3, 4... maxRange = 9, 19, 29, 39, 49...
      int maxRange = (i + 1) * 10 - 1;

      // print the starting range
      cout << setw(3) << minRange << "--> " << setw(3);

      // print the ending range
      if (maxRange < MAXGRADE)
         cout << maxRange;
      else
         cout << MAXGRADE; // end range can't be greater than MAXGRADE

      cout << ": ";

      // loop over histogram bar size for current range
      for (int j = 0; j < histogram[i]; j++)
         cout << "*"; // print stars

      cout << endl;
   }

   cout << endl;
}

// ----------------------------------------------------------------------------
// findAverage
// Calculates class average grade by adding each student's grade from array 
// (first parameter) and dividing by size (second parameter)
// This function returns 0 if size is less than or equal to zero.
int findAverage(StudentType students[], int size) {
   int total = 0;

   // loop over student data
   for (int i = 0; i < size; i++) {
      total += students[i].grade; // add each student's grade to total
   }

   if (size > 0) return total / size; // calulate average if not divide by 0
   else return 0;
}

// You must put a separator line between every function
// Then comes the name of the function on a separate comment line
// Then comes the function comment. Clearly comment every function.
// Use bubble.cpp as a guide.

// Do not use separator lines elsewhere.