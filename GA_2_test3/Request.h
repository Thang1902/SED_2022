#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Member.h"

using namespace std;

class Request{
private:
    Member* owner;
    Member* requester;
    House* requested_house;
    Date start;
    Date end;
public:
    Request();
    Request(House* requested_house, Member* owner, Member* requester, Date start, Date end); // for requester

    void RequestInfo();
};