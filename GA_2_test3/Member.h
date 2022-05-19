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

class Member{ // thang
private:

    int member_ID;
    int credit;
    string fname;
    string uname;
    string phone;
    double occupier_rate;    
    int house_ID_mem; // id of house of member
    
    vector <double> occupier_rate_list;
    vector <int> request_id_list; // thang requests house a, house, b, house c, etc

public:
    // constructors
    Member();
    Member(string fname, string phone);

    // getters and setters

    int getID();
    void setID(int id);
    string getFullName();
    void setFullName(string name);    

    double getRating();
    void setRating(double rate);

    int getCpoint();
    void setCredit(int credit);
    
    //House getHouse(House house);
    void setHouse(House house);
    int getHouseID();

    // methods 

    double cal_occupier_rate();
    //void rateOccupier(Member* occupier_rate, double rate);

    //Request* RequestAHouse(House* house, Member* owner, Date start, Date end);
    void addRequestToList(int req_id);
    //void viewAllReq();

    void viewInfo();
    

    
};

