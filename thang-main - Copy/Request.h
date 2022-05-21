#pragma once

using namespace std;

class Member;

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
    Request(int request_ID, int house_ID, int owner_ID, int requester_ID, Date start, Date end);

    int getReqID(); // id
    int getRequesterID(); // requester id
    int getOwnerID(); // owner id
    int getHouseID(); // house id
    Date getStart(); // start date
    Date getEnd();  // end date

    void RequestInfo(Member requester);
};
