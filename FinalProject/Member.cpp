#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Member.h"

using namespace std;

Member::Member(){}

//constructor for file io
Member::Member(int member_ID, int credit, string fname, string uname, string password, string phone, double occupier_rate, int house_ID_mem){
    this->member_ID = member_ID;
    this->fname = fname;
    this->phone = phone;
    this->credit = credit;
    this->uname = uname;
    this->password = password;
    this->occupier_rate = occupier_rate;
    this->house_ID_mem = house_ID_mem;
}

// constructor when a non-member registers
Member::Member(int id, string fname, string uname, string password, string phone){
    member_ID = id;
    this->fname = fname;
    this->phone = phone;
    this->password = password;
    credit = 500; // initial 500 credit points given
    this->uname = uname;
    occupier_rate = 10; // default occupier rating given (10)
    house_ID_mem = 0; // no house yet
}

int Member::getID(){
    return member_ID;
}

void Member::setID(int id){
    member_ID = id;
}

int Member::getCpoint(){
    return this->credit;
}

void Member::setCredit(int credit){
    this->credit = credit;
}

double Member::getRating(){
    return this->occupier_rate;
}

void Member::setRating(double rate){
    this->occupier_rate = rate;
}
string Member::getUserName(){
    return this->uname;
}

void Member::setUserName(string name){
    this->uname = uname;
}

string Member::getPassword(){
    return this->password;
}

void Member::setPassword(string password){
    this->password = password;
}

string Member::getFullName(){
    return this->fname;
}

void Member::setFullName(string name){
    this->fname = name;
}

string Member::getPhone(){
    return phone;
}

void Member::setPhone(string phone){
    this->phone = phone;
}

void Member::setHouse(int houseid){
    this->house_ID_mem = houseid;    
}

int Member::getHouseID(){
    return this->house_ID_mem;
}

vector <int> Member::getReqList(){
    return this->request_id_list;
}

void Member::viewInfo(){
    cout << "\n\t\t\t\tID: " << member_ID << endl;
    cout << "\t\t\t\tFull name: " << fname << endl;
    cout << "\t\t\t\tUsername: " << uname << endl;
    cout << "\t\t\t\tPhone: " << phone << endl;
    cout << "\t\t\t\tYour occupier rating: " << occupier_rate << endl;
    cout << "\t\t\t\tID of your house: " << house_ID_mem << endl;
    cout << "\t\t\t\tCredit point: " << credit << endl;  
    cout << "\t\t\t\t--------------------------\n";  
}

void Member::addRequestToList(int req_id){
    request_id_list.push_back(req_id);
}

void Member::viewReqList(){    
    for (int i : request_id_list){
        cout << "\n\t\t\t\tRequest ID: " << i << endl;
    }
}






