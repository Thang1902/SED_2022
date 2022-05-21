#pragma once

using namespace std;

class House;
class Request;

class Member{ 
private:
    int member_ID;
    int credit;
    string fname;
    string uname;
    string password;
    string phone;
    double occupier_rate;    
    int house_ID_mem; // id of house of member   
    
    vector <int> request_id_list; // thang requests house a, house, b, house c, etc

public:
    // constructors
    Member();    
    Member(int member_ID, int credit, string fname, string uname, string password,
                string phone, double occupier_rate, int house_ID_mem); // for file io
    Member(int id, string fname, string uname, string password, string phone); // register
    // getters and setters
   
    int getID(); // id of member
    void setID(int id);    

    string getFullName(); // fname
    void setFullName(string name);  

    string getUserName(); // uname
    void setUserName(string name); 

    string getPassword(); // password
    void setPassword(string password); 

    string getPhone(); // phone
    void setPhone(string phone); 

    double getRating(); // rating
    void setRating(double rate);

    int getCpoint(); // credit
    void setCredit(int credit);

    void setHouse(int houseid); // id of house
    int getHouseID();  


    vector <int> getReqList();
    void viewReqList();          

    // methods 
    
    void addRequestToList(int req_id);
    void viewInfo();  
    
};

