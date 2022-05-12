#include <iostream>
#include <vector>
#include <string>
#include "Member.h"

using namespace std;

Member::Member(){}

Member::Member(string fname, string phone){
    this->fname = fname;
    this->phone = phone;
    credit = 500;    
    vector <double> occupier_rate_list;
}

void Member::viewInfo(){
    cout << "Full name: " << fname << endl;
    cout << "Phone: " << phone << endl;
    cout << "Credit point: " << credit << endl;
}

string Member::getFullName(){
    return this->fname;
}

void Member::setHouse(House *house){
    this->member_house = house;    
}

House* Member::getHouse(){
    return member_house;
}

double Member::cal_occupier_rate(){
    double temp = 0;
    for (double rating : occupier_rate_list){
        temp += rating;
    }
    return temp/occupier_rate_list.size();
}

void Member::rateOccupier(Member* occupier_rate, double rate){
    occupier_rate->occupier_rate_list.push_back(rate);
}

