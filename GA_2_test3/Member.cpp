#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Member.h"



using namespace std;

int GenerateMemberID(){
    int id;
    srand(time(0));
    id = (rand() % 100000);

    return id;
}

Member::Member(){}

Member::Member(string fname, string phone){
    int id = GenerateMemberID();
    this->member_ID = id;
    this->fname = fname;
    this->phone = phone;
    credit = 5000;    
    vector <double> occupier_rate_list;
}

int Member::getID(){
    return this->member_ID;
}

void Member::setID(int id){
    this->member_ID = id;
}

void Member::setCredit(int credit){
    this->credit = credit;
}

void Member::setRating(double rate){
    this->occupier_rate = rate;
}

void Member::viewInfo(){
    cout << "ID: " << member_ID << endl;
    cout << "Full name: " << fname << endl;
    cout << "Phone: " << phone << endl;
    cout << "Credit point: " << credit << endl;  
    cout << "--------------------------\n";  
}

int Member::getCpoint(){
    return this->credit;
}

double Member::getRating(){
    return this->occupier_rate;
}

string Member::getFullName(){
    return this->fname;
}

void Member::setFullName(string name){
    this->fname = name;
}

void Member::setHouse(House house){
    this->house_ID_mem = house.getID();    
}

// House Member::getHouse(House house){
//     return house;
// }

double Member::cal_occupier_rate(){
    double temp = 0;
    for (double rating : occupier_rate_list){
        temp += rating;
    }
    return temp/occupier_rate_list.size();
}

// void Member::rateOccupier(Member* occupier_rate, double rate){
//     occupier_rate->occupier_rate_list.push_back(rate);
// }

// Request* Member::RequestAHouse(House* house, Member* owner, Date start, Date end){
//     Request* temp = new Request(house, owner, this, start, end);
//     return temp;
// }

void Member::addRequestToList(int req_id){
    request_id_list.push_back(req_id);
}

// void Member::viewAllReq(){
//     cout << "Showing all requests to your house:\n";
//     for (Request* req : request_list){
//         req->RequestInfo();
//     }
// }

int Member::getHouseID(){
    return this->house_ID_mem;
}




