//Name: Nathaniel Ling
//SID: 110372208
//Email: nling@myseneca.ca
//Section: BTP200 NAA
//Prof: Cornel Barna
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds {
   bool debug = false;  // made global in utils.h
   int getTime() {  
      int mins = -1;
      if (debug) {
         Time t(0);
         cout << "Enter current time: ";
         do {
            cin.clear();
            cin >> t;   // needs extraction operator overloaded for Time
            if (!cin) {
               cout << "Invalid time, try again (HH:MM): ";
               cin.clear();
            }
            else {
               mins = int(t);
            }
            cin.ignore(1000, '\n');
         } while (mins < 0);
      }
      else {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         mins = lt.tm_hour * 60 + lt.tm_min;
      }
      return mins;
   }
   int getInt(const char* prompt) {
       char read[10];
       int num;
       if (prompt != nullptr) {
           cout << prompt;
       }
       bool valid = false;
       while (!valid) {
           cin.getline(read, 10);
           if (!isdigit(read[0])) {
               cin.clear();
               cout << "Bad integer value, try again: ";
           }
           else {
               unsigned a = 0;
               for (unsigned i = 0; i < strlen(read); i++) {
                   if (isdigit(read[i])) {
                       a++;
                   }
               }
               if (a != strlen(read)) {
                   cin.clear();
                   cout << "Enter only an integer, try again: ";
               }
               else {
                   num = atoi(read);
                   valid = true;
               }
           }
       }
       return num;
   }
   int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError) {
       char read[10];
       int num = 0;
       if (prompt != nullptr) {
           cout << prompt;
       }
       bool valid = false;
       while (!valid) {
           cin.getline(read, 10);
           if (isdigit(read[0]) || read[0] == '-') {
               unsigned a = 0;
               for (unsigned i = 0; i < strlen(read); i++) {
                   if (isdigit(read[i]) || read[0] == '-') {
                       a++;
                   }
               }
               if (a != strlen(read)) {
                   cin.clear();
                   cout << "Enter only an integer, try again: ";
               }
               else {
                   num = atoi(read);
                   if (num > max || num < min) {
                       cout << errorMessage;
                       if (showRangeAtError) {
                           cout << "[" << min << " <= value <= " << max << "]: ";
                       }
                   }
                   else {
                       valid = true;
                   }
               }
           }
           else {
               cin.clear();
                   cout << "Bad integer value, try again: ";
               }
           }
       return num;
   }
   char* getcstr(const char* prompt, std::istream& istr, char delimiter) {
       char read[300];
       char* cstr;
       if (prompt != nullptr) {
           cout << prompt;
       }
       istr.getline(read, 300, delimiter);
       cstr = new char[strlen(read) + 1];
       strcpy(cstr, read);
       return cstr;
   }
}