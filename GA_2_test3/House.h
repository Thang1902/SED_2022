#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Date.h"


using namespace std;

class Member;
class Date;
class Request;

class House{
public:
    string location;
    string description;
    int consuming_point;
    double min_rate;
    Member *owner;
    Member *occupier;
    // vector to keep track
    vector <Request*> request_list;
    double house_rate;

    Date start_avai;
    Date end_avai;


public:
    House();
    House(string location, string description);

    Member* getOwner();
    void setOwner(Member *add_owner);

    void setConsumingPoint(int cpoint);
    void setMinRate(double rate);

    void setAvailability(Date st, Date e);

    void viewInfoHouse();
    void viewInfoHouseGuess();
};
