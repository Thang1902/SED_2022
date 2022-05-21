#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Member.h"

using namespace std;

Member::Member(){}

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

Member::Member(int id, string fname, string uname, string password, string phone){
    member_ID = id;
    this->fname = fname;
    this->phone = phone;
    this->password = password;
    credit = 500;
    this->uname = uname;
    occupier_rate = 10;
    house_ID_mem = 0;
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

// House Member::getHouse(House house){
//     return house;
// }

void Member::viewInfo(){
    cout << "ID: " << member_ID << endl;
    cout << "Full name: " << fname << endl;
    cout << "Phone: " << phone << endl;
    cout << "Credit point: " << credit << endl;  
    cout << "--------------------------\n";  
}
void Member::addRequestToList(int req_id){
    request_id_list.push_back(req_id);
}

void Member::viewReqList(){
    cout << "size of req list: " << request_id_list.size() << endl;
    for (int i : request_id_list){
        cout << "Request id: " << i << endl;
    }
}






