#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <vector>
#include <string>

#include "Member.h"
#include "Date.h"
#include "House.h"

using namespace std;

House::House(){}

House::House(int id, string location, string description, Date start, Date end, int consum_point, double minrate){ // for requester   
    this->house_ID = id;
    this->location = location;
    this->description = description;
    this->start_avai = start;
    this->end_avai = end;
    this->consuming_point = consum_point;
    this->min_rate = minrate;
    this->house_rate = 10.0; // house given default rating score
}

House::House(int house_ID, int owner_ID, string location, string description, int consuming_point,
                double min_rate, double house_rate, Date start_avai, Date end_avai){ // constructor for file io
    this->house_ID = house_ID;
    this->owner_ID = owner_ID;    
    this->location = location;
    this->description = description;
    this->consuming_point = consuming_point;
    this->min_rate = min_rate;
    this->house_rate = house_rate;
    this->start_avai = start_avai;
    this->end_avai = end_avai;  
}

void House::setID(int id){
    this->house_ID = id;
}

int House::getID(){
    return this->house_ID;
}

int House::getOwnerID(){
    return this->owner_ID;
}

void House::setOwner(Member& owner){
    this->owner_ID = owner.getID();  
}

void House::viewInfoHouse(Member owner){ // view info house for member and admin
    cout << "\n\t\t\t\tID: " << house_ID << endl;
    cout << "\t\t\t\tLocation: " << location << endl;
    cout << "\t\t\t\tDescription: " << description << endl;    
    cout << "\t\t\t\tOwner: " << owner.getFullName() << endl;
    cout << "\t\t\t\tAvailability: " << start_avai.viewDate() << " to " << end_avai.viewDate() << endl;
    cout << "\t\t\t\tHouse rating score: " << house_rate << endl;
    cout << "\t\t\t\tConsuming point per day: " << consuming_point << endl;
    cout << "\t\t\t\tMinimum rating : " << min_rate << endl;
    cout << "\t\t\t\t-----------------------\n";    
}

void House::viewInfoHouseGuest(Member owner){ // view info house for guest
    cout << "\n\t\t\t\tID: " << house_ID << endl;
    cout << "\t\t\t\tLocation: " << location << endl;
    cout << "\t\t\t\tDescription: " << description << endl;    
    cout << "\t\t\t\tOwner: " << owner.getFullName() << endl;      
    cout << "\n\t\t\t\t-----------------------\n";   
}

string House::getLocation(){
    return this->location;
}

string House::getDescription(){
    return this->description;
}

double House::getMinrate(){
    return this->min_rate;
}

double House::getHouseRating(){
    return this->house_rate;
}

int House::getConsumingP(){
    return this->consuming_point;
}

Date House::getStartAvai(){
    return this->start_avai;
}

Date House::getEndAvai(){
    return this->end_avai;
}

void House::setAvailability(Date st, Date e){ // set availability of house
    this->start_avai = st;
    this->end_avai = e;
}

void House::setConsumingPoint(int cpoint){
    this->consuming_point = cpoint;
}

void House::setMinRate(double rate){
    this->min_rate = rate;
}

void House::setLocation(string location){
    this->location = location;
}

void House::setDescription(string description){
    this->description = description;
}

bool House::isSuitableHouse(Member mem, Date start, Date end, string city, double rate, int points){  
    if (start > start_avai){ // if start date not later
        if (end_avai > end){ // if end date not sooner                                           
            if (city == location){ // same location                             
                if (rate >= min_rate){ // suffcient rating                       
                    if (points > (stoi(end.getDay()) - stoi(start.getDay())) * consuming_point){ // suffcient credit point                          
                        return true; // the house is suitable
                    }
                }
            }
        }
    }            
    return false;  
}

