#include <iostream>
#include <vector>
#include <string>


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

Date Date::biggerDate(Date cmp){    
    if (this->year > cmp.year){
        return *this;
    }
    else if (this->year < cmp.year){
        return cmp;
    }
    else{
        if (this->month > cmp.month){
            return *this;
        }
        else if (this->month < cmp.month){
            return cmp;
        }
        else {
            if (this->day > cmp.day){
                return *this;
            }
            else if (this->day < cmp.day){
                return cmp;
            }
            else{
                return *this;
            }
        }
    } 
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
