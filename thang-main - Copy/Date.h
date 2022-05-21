#pragma once

using namespace std;

class Date{
public: 
    int day;
    int month;
    int year;
    string DateAsString;

    Date();
    Date(string date_input);
    Date(int day, int month, int year);

    string getDay();
    string getMonth();
    string getYear();
    string getDateAsString();

    string viewDate();    
    Date biggerDate(Date cmp);

    bool operator == (Date cmp);
    bool operator > (Date cmp);  
};
