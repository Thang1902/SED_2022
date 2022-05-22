#pragma once
     
#define MAX_LOGIN_ATTEMPTS 3

using namespace std;

enum mode {guest = 1, member = 2, admin = 3}; // mode control of program

// user input validation fucntions declaration
bool isDigit(string str);
int inputNumber(string prompt);
int inputNumber(string str, int maxsize);
double inputRating();
string inputPhone();
string inputString(string prompt);
void welcomeScreen();
void GuessScreen();
void MemberScreen(Member mem);
void AdminScreen();
void BackorExit(bool& run_prog, bool& run_subprog, int prog, int subprog, int exit);
bool checkDate(int day, int month, int year);
bool validateDateInput(string str);
string getDateInput(string& inp);
string getDateInput(string& inp, string sstart);

