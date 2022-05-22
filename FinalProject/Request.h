#pragma once

using namespace std;

// forward declaration
class Member;

class Request{
private:
    int request_ID; // unique ID for this request obj
    int owner_ID; // ID of the owner of the house requested
    int requester_ID; // ID of the one requesting
    int house_ID; // ID of the house being requested
    Date start; // duration
    Date end;
public:
    // constructors
    Request();    
    Request(int request_ID, int house_ID, int owner_ID, int requester_ID, Date start, Date end); // for file io and requesters

    // getters 
    int getReqID(); 
    int getRequesterID(); 
    int getOwnerID();
    int getHouseID(); 
    Date getStart();
    Date getEnd(); 

    // methods
    void RequestInfo(Member requester);
};
