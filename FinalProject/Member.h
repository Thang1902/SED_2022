#pragma once

using namespace std;

// forward declaration
class House;
class Request;

class Member{ 
private:
    int member_ID; // unique ID for this member obj
    int credit;
    string fname;
    string uname;
    string password;
    string phone;
    double occupier_rate;    
    int house_ID_mem; // ID of house of member   
    
    vector <int> request_id_list; // vector of request ID

public:
    // constructors
    Member();    
    Member(int member_ID, int credit, string fname, string uname, string password,
                string phone, double occupier_rate, int house_ID_mem); // for file io
    Member(int id, string fname, string uname, string password, string phone); // register

    // getters and setters   
    int getID();
    void setID(int id); 
    string getFullName();
    void setFullName(string name);  
    string getUserName(); 
    void setUserName(string name); 
    string getPassword(); 
    void setPassword(string password); 
    string getPhone(); 
    void setPhone(string phone); 
    double getRating(); 
    void setRating(double rate);
    int getCpoint(); 
    void setCredit(int credit);
    void setHouse(int houseid);
    int getHouseID();  
    vector <int> getReqList();
            
    // methods 
    void viewReqList(); 
    void addRequestToList(int req_id);
    void viewInfo(); 
};

