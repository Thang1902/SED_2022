#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Member.h"

using namespace std;

class Request{
private:
    int request_ID;
    int owner_ID;
    int requester_ID;
    int house_ID;
    Date start;
    Date end;
public:
    Request();
    Request(int house_ID, int owner_ID, int requester_ID, Date start, Date end); // for requester

    int getReqID();

    void RequestInfo(Member requester);
};