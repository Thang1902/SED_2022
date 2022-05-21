#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "Date.h"
#include "Member.h"
#include "Request.h"

using namespace std;

Request::Request(){}

Request::Request(int request_ID, int house_ID, int owner_ID, int requester_ID, Date start, Date end){
    this->request_ID = request_ID;
    this->house_ID = house_ID;
    this->owner_ID = owner_ID;
    this->requester_ID = requester_ID;    
    this->start = start;
    this->end = end;
}

void Request::RequestInfo(Member requester){    
    cout << "\nRequest ID: " << request_ID << endl;
    cout << "Requester: " << requester.getFullName() << endl;
    cout << "Start date: " << start.viewDate() << endl;
    cout << "End date: " << end.viewDate() << endl;
}

int Request::getReqID(){
    return this->request_ID;
}

int Request::getRequesterID(){
    return this->requester_ID;
}

int Request::getOwnerID(){
    return this->owner_ID;
}

int Request::getHouseID(){
    return this->house_ID;
}

Date Request::getStart(){
    return this->start;
}

Date Request::getEnd(){
    return this->end;
}

