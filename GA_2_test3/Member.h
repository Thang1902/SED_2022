#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "House.h"
#include "Request.h"


using namespace std;

class House;
class Request;
class Date;

class Member{
private:

    int credit;
    string fname;
    string uname;
    string phone;
    double occupier_rate;
    House *member_house;    
    
    vector <double> occupier_rate_list;    
    vector <Request*> request_list;   

public:
    // constructors
    Member();
    Member(string fname, string phone);

    // getters and setters
    string getFullName();
    void setFullName(string name);    

    double getRating();
    void setRating(double rate);

    int getCpoint();
    void setCredit(int credit);
    
    House* getHouse();
    void setHouse(House *house);

    // methods 

    double cal_occupier_rate();
    void rateOccupier(Member* occupier_rate, double rate);

    Request* RequestAHouse(House* house, Member* owner, Date start, Date end);
    void addRequestToList(Request* req);
    void viewAllReq();

    void viewInfo();

    
};

