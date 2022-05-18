#include <iostream>
#include <vector>
#include <string>
#include "Request.h"

using namespace std;

Request::Request(){}

Request::Request(House* requested_house, Member* owner, Member* requester, Date start, Date end){
    this->requested_house = requested_house;
    this->owner = owner;
    this->requester = requester;    
    this->start = start;
    this->end = end;
}

void Request::RequestInfo(){
    cout << "\nRequester: " << requester->getFullName() << endl;
    cout << "Start date: " << start.viewDate() << endl;
    cout << "End date: " << end.viewDate() << endl;
}

