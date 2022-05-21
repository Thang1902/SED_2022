#include <iostream>
#include <vector>
#include <string>
#include "Date.h"

Date::Date(){}

Date::Date(int day, int month, int year){
    this->day = day;
    this->month = month;
    this->year = year;
}

Date::Date(string date_input){        
    string sday = date_input.substr(0, 2);
    string smonth = date_input.substr(2, 2);
    string syear = date_input.substr(4, 2);
    DateAsString = date_input;
    this->day = stoi(sday);
    this->month = stoi(smonth);
    this->year = stoi(syear);
}

void Date::updateDate(string newdate){
    string sday = newdate.substr(0, 2);
    string smonth = newdate.substr(2, 2);
    string syear = newdate.substr(4, 2);
    DateAsString = newdate;
    this->day = stoi(sday);
    this->month = stoi(smonth);
    this->year = stoi(syear);
}

string Date::getDay(){
    string sday;
    sday = to_string(this->day);
    return sday;
}

string Date::getMonth(){
    string smonth;
    smonth = to_string(this->month);
    return smonth;
}

string Date::getYear(){
    string syear;
    syear = to_string(this->year);
    return syear;
}

string Date::getDateAsString(){    
    return DateAsString;
}

string Date::viewDate(){
    if (year < 10){
        return this->getDay() + "/" + this->getMonth() + "/200" + this->getYear();
    }    
    return this->getDay() + "/" + this->getMonth() + "/20" + this->getYear();
} 

bool Date::operator==(Date cmp){
    if (this->year == cmp.year){
        if (this->month == cmp.month){
            if (this->day == cmp.day){
                return true;
            }
        }
    }
    return false;
} 

bool Date::operator>(Date cmp){
    if (this->year >= cmp.year){
        if (this->month >= cmp.month){
            if (this->day > cmp.day){
                return true;
            }
        }
    }
    return false;
} 
