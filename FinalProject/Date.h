#pragma once

using namespace std;

class Date{
public: 
    int day;
    int month;
    int year;
    string DateAsString; // Date obj as a string

    // constructors
    Date();
    Date(string date_input);
    Date(int day, int month, int year);

    // getters
    string getDay();
    string getMonth();
    string getYear();
    string getDateAsString();

    // methods
    string viewDate();   
    void updateDate(string newdate);

    // operator overloading for comparison between 2 Date objs
    bool operator == (Date cmp);
    bool operator > (Date cmp);  
};
