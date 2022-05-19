#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Request.h"

using namespace std;

int GenerateReqID(){
    int id;
    srand(time(0));
    id = (rand() % 100000);

    return id;
}

Request::Request(){}

Request::Request(int house_ID, int owner_ID, int requester_ID, Date start, Date end){
    int id = GenerateReqID();
    request_ID = id;
    this->house_ID = house_ID;
    this->owner_ID = owner_ID;
    this->requester_ID = requester_ID;    
    this->start = start;
    this->end = end;
}

void Request::RequestInfo(Member requester){
    cout << "\nRequester: " << requester.getFullName() << endl;
    cout << "Start date: " << start.viewDate() << endl;
    cout << "End date: " << end.viewDate() << endl;
}

int Request::getReqID(){
    return this->request_ID;
}

