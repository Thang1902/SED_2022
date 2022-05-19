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
private:
    int house_ID;
    string location;
    string description;
    int consuming_point;
    double min_rate;
    int owner_ID; // id of owner
    int occupier_ID; // id of occupier
    double house_rate;
    Date start_avai;
    Date end_avai;
    
    //vector <Request*> request_list; // req to that house
    vector <Date> occupied_period; //    

public:
    House();
    House(string location, string description);
    House(string location, string description, Date start, Date end, int consum_point, double minrate);
    House(string location, string description, Date start, Date end, int consum_point);

    //Member getOwner();
    void setID(int id); // test
    void setID();
    int getID();
    int getOwnerID();

    void setOwner(Member add_owner);    

    void setConsumingPoint(int cpoint);
    void setMinRate(double rate);

    void setAvailability(Date st, Date e);

    void setLocation(string location);
    void setDescription(string description);

    string getLocation();
    double getMinrate();
    Date getStartAvai();
    Date getEndAvai();
    int getConsumingP();    

    void viewInfoHouse(Member owner);
    void viewInfoHouseGuest(Member owner);

    bool isSuitableHouse(Member mem, Date start, Date end, string city, double rate, int points);
};
