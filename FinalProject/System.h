#pragma once

using namespace std;

class House;
class Request;
class Member;
class Date;

class System{
public:    
    // map to store IDs of members, houses and requests 
    map <int, Member> member_list;
    map <int, House> house_list;
    map <int, Request> request_list;
    map <string, Member> login_list;

    // iterators of maps
    map <int, Member>::iterator mem_itr;
    map <int, House>::iterator house_itr;
    map <int, Request>::iterator req_itr;
    
    vector <int> suitable_house_ID_list; // vector to display suitable houses

    System(); // constructor

    // data handling
    void importMember();
    void importHouse();
    void importRequest();
    void exportMember();
    void exportHouse();
    void exportRequest(); 

    // methods to use in program
    int generateMemberID();
    int generateHouseID();
    int generateRequestID();
    void addMember(Member mem, int ID);
    bool viewHouses(int mode);
    void viewAllMembers();
    bool addHouse(Member& mem_house);
    void searchHouse(Member mem);
    void RequestToOccupy(Member requester);
    void viewRequestList(Member owner);
    int authenticateMemberLogin();
    ~System(); // destructor 
};