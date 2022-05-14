#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "House.h"


using namespace std;

class House;
class Request;
class Date;

class Member{
protected:
    int credit;
    string fname;
    string uname;
    string phone;
    House *member_house;    
    // use a vector to keep track of rate
    vector <double> occupier_rate_list;
    double occupier_rate;
    vector <Request*> request_list;

    friend class House;
public:
    Member();
    Member(string fname, string phone);

    string getFullName();

    

    void viewInfo();
    House* getHouse();
    void setHouse(House *house);

    double cal_occupier_rate();
    void rateOccupier(Member* occupier_rate, double rate);

    
};

