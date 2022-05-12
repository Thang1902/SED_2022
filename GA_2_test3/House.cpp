#include <iostream>
#include <vector>
#include <string>
#include "House.h"
#include "Date.h"

using namespace std;

House::House(){}

House::House(string location, string description){
    this->location = location;
    this->description = description;
    this->min_rate = 0;
    this->house_rate = 0;
}

void House::setOwner(Member *add_owner){
    this->owner = add_owner;    
}

void House::viewInfoHouse(){
    cout << "Location: " << location << endl;
    cout << "Description: " << description << endl;    
    cout << "Owner: " << owner->getFullName() << endl;
    cout << "Availability: " << start_avai.viewDate() << " to " << end_avai.viewDate() << endl;
    cout << "House rating score: " << house_rate << endl;
    cout << "Consuming point per day: " << consuming_point << endl;
    cout << "Minimum rating : " << min_rate << endl;
}

void House::viewInfoHouseGuess(){
    cout << "Location: " << location << endl;
    cout << "Description: " << description << endl;    
    cout << "Owner: " << owner->getFullName() << endl;    
    cout << "Consuming point per day: " << consuming_point << endl;
    cout << "Minimum rating : " << min_rate << endl;
}

Member* House::getOwner(){
    return owner;
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
