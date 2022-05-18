//C++ program to demonstrate read/write of class
//objects in C++.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "App.cpp"
#include "House.cpp"
#include "Date.cpp"
#include "Review.cpp"
#include "Request.cpp"

using namespace std;

int main(){    

    
    Member m1("thang1", "0000");
    m1.setCredit(100000);
    m1.setRating(10);
    Member m2("thang2", "0001");
    m2.setCredit(100000);
    m2.setRating(10);
    Member m3("thang3", "0002");
    Member m4("thang4", "0003");

    // CREATE DATES
    
    Date def("010100");
    Date d1("120522");
    Date d2("170522");
    Date d3("220622");
    Date d4("280622");
    Date d5("130522");

    // TEST VARIABLES

    int cpoint = 200;
    int cpoint2 = 300;
    double minr = 5.5;
    double minr2 = 6.5;
        
    // create houses
    House h1("HCM", "A 3-story house", d1, d2, 200, 5.5);
    h1.setID(001);
    House h2("Ha Noi", "A 3-bedroom aparment", d3, d4, 150, 4.9);
    h2.setID(002);
    House h3("Da Nang", "A sea-view villa", d1, d3, 500, 3.8);
    h3.setID(003);
    House h4("HCM", "Boutique house", d2, d4, 360, 8.9);
    h4.setID(004);

    // create connection between house and owner
    m1.setHouse(&h1);
    h1.setOwner(&m1);
    m2.setHouse(&h2);
    h2.setOwner(&m2);
    m3.setHouse(&h3);
    h3.setOwner(&m3);
    m4.setHouse(&h4);
    h4.setOwner(&m4); 

    Member m12;   

    vector <House> hlistin;    
    vector <House> hlistout;    
    

    hlistin.push_back(h1);
    hlistin.push_back(h2);
    hlistin.push_back(h3);
    hlistin.push_back(h4);

    ofstream f;
    f.open("house.dat", ios::out | ios::binary);
    size_t size = hlistin.size(); // size of vector
    f.write(reinterpret_cast<char*>(&size), sizeof(size)); // write to file

    for (size_t i = 0; i < hlistin.size(); i++){
        size = sizeof(hlistin[i]);
        f.write(reinterpret_cast<char*>(&size), sizeof size);

        // const char *p = hlistin[i].data();
        // f.write(p, listin[i].size());
    }


    

    // is.read(reinterpret_cast<char*> (&h12), sizeof(h12));
    // is.read(reinterpret_cast<char*> (&h32), sizeof(h32));
    // is.read(reinterpret_cast<char*> (&h22), sizeof(h22));
    // h12.viewInfoHouse();
    // h22.viewInfoHouse();
    // h32.viewInfoHouse();
    // House temp;
    // House* temp_ptr = &temp;
   
    
    
    
    

    

    
}

