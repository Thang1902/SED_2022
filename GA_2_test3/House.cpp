#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <vector>
#include <string>
#include "Member.h"
#include "House.h"
#include "Date.h"

int GenerateID(){
    int id;
    srand(time(0));
    id = (rand() % 100000);

    return id;
}

using namespace std;

House::House(){}

House::House(string location, string description){
    this->location = location;
    this->description = description;

};

House::House(string location, string description, Date start, Date end, int consum_point, double minrate){
    int id = GenerateID();
    this->ID = id;
    this->location = location;
    this->description = description;
    this->start_avai = start;
    this->end_avai = end;
    this->consuming_point = consum_point;
    this->min_rate = minrate;
    this->house_rate = 0;
}

House::House(string location, string description, Date start, Date end, int consum_point){
    int id = GenerateID();
    this->ID = id;
    this->location = location;
    this->description = description;
    this->start_avai = start;
    this->end_avai = end;
    this->consuming_point = consum_point;
    this->min_rate = 0;
    this->house_rate = 0;
}

void House::setID(int id){
    this->ID = id;
}

void House::setID(){
    int id = GenerateID();
    this->ID = id;
}

int House::getID(){
    return this->ID;
}

void House::setOwner(Member *add_owner){
    this->owner = add_owner;    
}

void House::viewInfoHouse(){
    cout << "\nID: " << ID << endl;
    cout << "Location: " << location << endl;
    cout << "Description: " << description << endl;    
    cout << "Owner: " << owner->getFullName() << endl;
    cout << "Availability: " << start_avai.viewDate() << " to " << end_avai.viewDate() << endl;
    cout << "House rating score: " << house_rate << endl;
    cout << "Consuming point per day: " << consuming_point << endl;
    cout << "Minimum rating : " << min_rate << endl;
    cout << "-----------------------\n";
    cout << "fetching data\n";
}

void House::viewInfoHouseGuest(){
    cout << "\nID: " << ID << endl;
    cout << "Location: " << location << endl;
    cout << "Description: " << description << endl;    
    cout << "Owner: " << owner->getFullName() << endl;
    cout << "Availability: " << start_avai.viewDate() << " to " << end_avai.viewDate() << endl;    
    cout << "Consuming point per day: " << consuming_point << endl;
    cout << "Minimum rating : " << min_rate << endl;
    cout << "-----------------------\n";   
}

Member* House::getOwner(){
    return owner;
}

string House::getLocation(){
    return this->location;
}

double House::getMinrate(){
    return this->min_rate;
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

void House::setAvailability(Date st, Date e){
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

bool House::isSuitableHouse(Member* mem, Date start, Date end, string city, double rate, int points){    
    // cout << "start date of house:" <<cmphouse->start_avai.viewDate() << endl;
    // cout << "end date of house:" <<cmphouse->end_avai.viewDate() << endl;
    // cout << "start required: " << start.viewDate() << endl;
    // cout << "end required: " << end.viewDate() << endl;
    // cout << "city: " << cmphouse->location << endl;
    // cout << "city required: " << city << endl;
    // cout << "After comparison: "  << end.biggerDate(cmphouse->end_avai).viewDate();
    if (start > start_avai){   
        //cout << "START";    
        if (end_avai > end){ 
            //cout << "END";                               
            if (city == location){   
                //cout << "CITY";                 
                if (rate >= min_rate){
                    //cout << "RATING";    
                    if (points > (stoi(end.getDay()) - stoi(start.getDay())) * consuming_point){
                        //cout << "CREDIT";    
                        return true;
                    }
                }
            }
        }
    }
    cout << "FALSE\n";        
    return false;  
}

