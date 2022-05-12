#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Date{
public: 
    int day;
    int month;
    int year;

    Date();
    Date(string date_input);
    Date(int day, int month, int year);

    string getDay();
    string getMonth();
    string getYear();

    string viewDate();
    Date biggerDate(Date cmp);

    bool operator == (Date cmp);
    bool operator > (Date cmp);

    


};