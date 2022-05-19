//C++ program to demonstrate read/write of class
//objects in C++.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
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
    House h12, h22, h32;  

    vector <House> hlistin;    
    vector <House> hlistout;    
    

    // hlistin.push_back(h1);
    // hlistin.push_back(h2);
    // hlistin.push_back(h3);
    // hlistin.push_back(h4);


    ofstream f;
    f.open("house12.dat", ios::out | ios::binary);
    
    f << 3;
    f.write(reinterpret_cast<char*> (&h1),sizeof(House));
    f.write(reinterpret_cast<char*> (&h2),sizeof(House));
    f.write(reinterpret_cast<char*> (&h3),sizeof(House));
   
    f.close();

    // is.close();
    // // size_t size = hlistin.size(); // size of vector
      
    // // f.write(reinterpret_cast<char*>(&size), sizeof(size)); // write to file

    // // for (size_t i = 0; i < hlistin.size(); i++){
    // //     size = sizeof(hlistin[i]);
    // //     f.write(reinterpret_cast<char*>(&size), sizeof size);

    // //     // const char *p = hlistin[i].data();
    // //     // f.write(p, listin[i].size());
    // // }    
    // ifstream h;
    // cout << h.tellg() << endl;
    // h.open("house1.dat", ios::in | ios::binary);
    // cout << h.tellg() << endl;
    // h.read(reinterpret_cast<char*> (&h12), sizeof(h12));
    // cout << h.tellg() << endl;
    // h.read(reinterpret_cast<char*> (&h22), sizeof(h22));
    // cout << h.tellg() << endl;
    // h.read(reinterpret_cast<char*> (&h32), sizeof(h32));
    // cout << h.tellg() << endl;
    // h.close();
     
    int num_h;
    ifstream ff;
    ff.open("house12.dat", ios::in | ios::binary);

    cout << "-------------------\n";

    ff >> num_h;
    cout << num_h << endl;

    for (int i=0; i<num_h; i++){    
        House temp;
        ff.read(reinterpret_cast<char*> (&temp), sizeof(House));
        temp.viewInfoHouse();
    }
    ff.close();
    // }
    // if (f.is_open()){
    //     cout << "open";
    // }
    

    // for (House house : hlistout){
    //     house.viewInfoHouse();
    // }
     

    
    
    

    

    
}

