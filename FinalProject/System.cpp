#include <iostream>
#include <vector>
#include <iomanip>
#include <iterator>
#include <map>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include "Date.h"
#include "Member.h"
#include "Request.h"
#include "House.h"
#include "System.h"
#include "Main.h"

using namespace std;

System::System(){}

void System::importMember(){ // method to import data of members from file
    fstream member_infle; 
    member_infle.open("member.txt", ios::in);    
    if (!member_infle){
        cerr << "Cannot open file!";
        exit(1);
    }
    string memline;
    int member_count = 0;
    while(member_infle.peek()!=EOF)
	{
		getline(member_infle, memline);        
		member_count++; // count how many lines are in the record
	}
    // put file pointer back to beginning of file
    member_infle.clear();
    member_infle.seekg(0);

    // each member consists of 9 lines of data -> how many members
    member_count = member_count/9;    
    
    for (int i = 0; i < member_count; i++){  // create all member objs        
        // containers
        int inmember_ID;
        int incredit;
        string infname;
        string inuname;
        string inpassword;
        string inphone;
        double inoccupier_rate;    
        int inhouse_ID_mem;   
        vector <int> req_list_id_in; // container vector of req id   
        int size;

        // take data from file (1 line at a time)        
        member_infle >> inmember_ID;               
        member_infle >> incredit;          
        member_infle.clear();  
        member_infle.ignore(1000, '\n'); // flush stream 
        getline(member_infle, infname); // full name can have white space        
        member_infle >> inuname;
        member_infle >> inpassword;
        member_infle >> inphone;       
        member_infle >> inoccupier_rate;       
        member_infle >> inhouse_ID_mem;
        member_infle >> size;      
                
        // take vector of req id from file
        for (int i = 0 ; i < size; i++){             
            int ele;            
            member_infle >> ele;            
            req_list_id_in.push_back(ele);
        }      
        cout << endl; 

        // create new member obj based on data from file
        Member* memin = new Member(inmember_ID, incredit, infname, inuname,inpassword, inphone, inoccupier_rate, inhouse_ID_mem);  
        for (int i : req_list_id_in){ // add request list to member's request list
            memin->addRequestToList(i);
        }                
        
        member_list.insert({memin->getID(), *memin}); // add member to member list
        login_list.insert({memin->getUserName(), *memin}); // add login info to login list
    }
    member_infle.close(); 
}

void System::importHouse(){ // method to import data of houses from file
    fstream house_infile; 
    house_infile.open("house.txt", ios::in);   
    if (!house_infile){
        cerr << "Cannot open file!";
        exit(1);
    }
    string houseline;
    int house_count = 0;
    while(house_infile.peek()!=EOF)
	{
		getline(house_infile, houseline);              
		house_count++;        
	}
    // put file pointer back to beginning of file
    house_infile.clear();
    house_infile.seekg(0);    
    house_count = house_count/9; // count how many houses       
    for (int i = 0; i < house_count; i++){ 
        // containers
        int in_houseID = 0;
        int in_ownerID = 0;        
        string in_location;
        string in_description;
        int in_consuming_point = 0;        
        double in_min_rate = 0;    
        double in_house_rate = 0;
        string in_start_avai;   
        string in_end_avai;           
        
        // take data from file (1 line at a time)
        house_infile >> in_houseID;             
        house_infile >> in_ownerID;      
        house_infile.clear();  
        house_infile.ignore(1000, '\n'); // flush stream
        getline(house_infile, in_location); // location and string can have white space
        getline(house_infile, in_description);                      
        house_infile >> in_consuming_point;        
        house_infile >> in_min_rate;         
        house_infile >> in_house_rate;
        house_infile >> in_start_avai;
        house_infile >> in_end_avai; 

        // create new house obj based on data from file
        House* housein = new House(in_houseID, in_ownerID, in_location, in_description,
                             in_consuming_point, in_min_rate, in_house_rate, Date(in_start_avai), Date(in_end_avai));
        house_list.insert({housein->getID(), *housein}); // add house to member list 
    }
    house_infile.close();
}

void System::importRequest(){ // method to import data of requests from file
    fstream request_infile;
    request_infile.open("request.txt", ios::in);
    if (!request_infile){
        cerr << "Cannot open file!";
        exit(1);
    }
    string reqline;
    int req_count = 0;
    while(request_infile.peek()!=EOF)
	{
		getline(request_infile, reqline);
		req_count++;
	}
    request_infile.clear(); 
    request_infile.seekg(0); // put file pointer back to beginning of file
    req_count = req_count/6; // count how many requests    
    for (int i = 0; i < req_count; i++){ 
        // containers
        int in_request_ID;
        int in_owner_ID;
        int in_requester_ID;
        int in_house_ID;        
        string in_start; 
        string in_end;           
        
        // take data from file (1 line at a time)
        request_infile >> in_request_ID;       
        request_infile >> in_owner_ID;
        request_infile >> in_requester_ID;  
        request_infile >> in_house_ID;  
        request_infile >> in_start; 
        request_infile >> in_end;     
       
        // create new request obj based on data from file
        Request* requestin = new Request(in_request_ID, in_owner_ID, in_requester_ID, in_house_ID, Date(in_start), Date(in_end));  
              
        // add request to request list
        request_list.insert({requestin->getReqID(), *requestin});      
    }
    request_infile.close();
}

void System::exportMember(){ // method to export data of requests to file
    fstream member_outfile;
    member_outfile.open("member.txt", ios::out);    
    for (auto& mem : member_list){       
        member_outfile << mem.second.getID() << endl;
        member_outfile << mem.second.getCpoint() << endl;
        member_outfile << mem.second.getFullName() << endl;
        member_outfile << mem.second.getUserName() << endl;
        member_outfile << mem.second.getPassword() << endl;
        member_outfile << mem.second.getPhone() << endl;
        member_outfile << mem.second.getRating() << endl;
        member_outfile << mem.second.getHouseID() << endl;
        member_outfile << mem.second.getReqList().size() << " "; // size of request list
        for(int i : mem.second.getReqList()){ 
            member_outfile << i << " "; // write all request id on the same line
        }
        member_outfile << endl;
    }    
    member_outfile.close();
}

void System::exportHouse(){ // method to export data of requests to file
    fstream house_outfile;
    house_outfile.open("house.txt", ios::out);
    for (auto& house : house_list){
        house_outfile << house.second.getID() << endl;        
        house_outfile << house.second.getOwnerID() << endl;     
        house_outfile << house.second.getLocation() << endl;        
        house_outfile << house.second.getDescription() << endl;        
        house_outfile << house.second.getConsumingP() << endl;        
        house_outfile << house.second.getMinrate() << endl; 
        house_outfile << house.second.getHouseRating() << endl;   
        house_outfile << house.second.getStartAvai().getDateAsString() << endl;        
        house_outfile << house.second.getEndAvai().getDateAsString() << endl;        
    }
    house_outfile.close();
}

void System::exportRequest(){ // method to export data of requests to file
    fstream req_outfile;
    req_outfile.open("request.txt", ios::out);
    for (auto& req : request_list){
        req_outfile << req.second.getReqID() << endl;
        req_outfile << req.second.getHouseID() << endl;
        req_outfile << req.second.getOwnerID() << endl;
        req_outfile << req.second.getRequesterID() << endl;       
        req_outfile << req.second.getStart().getDateAsString() << endl;
        req_outfile << req.second.getEnd().getDateAsString() << endl;
    }
    req_outfile.close();
}

int System::generateMemberID(){ // method to generate unique ID for member when registering
        vector <int> idlist; // in-scope vector of all member IDs                
        for (mem_itr = member_list.begin(); mem_itr != member_list.end(); mem_itr++)
            idlist.push_back(mem_itr->second.getID()); // copy all member IDs
        int random_id;
        srand(time(0));
        random_id = (rand() % 10000); // generate random ID 0 - 9999

        while (find(idlist.begin(),idlist.end(), random_id) != idlist.end()){ // if ID already exists          
            srand(time(0));
            random_id = (rand() % 10000); // generate another number
        }   
        return random_id;   
}

int System::generateHouseID(){ // method to generate unique ID for house when listing
    vector <int> idlist;        
    for (house_itr = house_list.begin(); house_itr != house_list.end(); house_itr++)
        idlist.push_back(house_itr->second.getID());
    int random_id;
    srand(time(0));
    random_id = (rand() % 10000) + 10000;
    while (find(idlist.begin(),idlist.end(), random_id) != idlist.end()){            
        srand(time(0));
        random_id = (rand() % 10000) + 10000;
    }   
    return random_id;    
}

int System::generateRequestID(){ // method to generate unique ID for request when requesting
    vector <int> idlist;        
    for (req_itr = request_list.begin(); req_itr != request_list.end(); req_itr++)
        idlist.push_back(req_itr->second.getReqID());
    int random_id;
    srand(time(0));
    random_id = (rand() % 10000) + 20000;
    while (find(idlist.begin(),idlist.end(), random_id) != idlist.end()){            
        srand(time(0));
        random_id = (rand() % 10000) + 20000;
    } 
    return random_id;      
}

void System::addMember(Member mem, int ID){ // method to add a member to member list
    member_list.insert({ID, mem});
}

bool System::viewHouses(int mode){ // method to view all houses
    if (house_list.size() == 0){ // no house
            cout << "\n\t\t\t\tTheres is no house in the system right now!.\n";
            return false;
        }
    if (mode == guest){ // for guest        
        for (house_itr = house_list.begin(); house_itr != house_list.end(); house_itr++){                
            int owner = house_itr->second.getOwnerID();
            mem_itr = member_list.find(owner);
            house_itr->second.viewInfoHouseGuest(mem_itr->second);            
        }
    }
    if (mode == admin){ // for admin
        for (house_itr = house_list.begin(); house_itr != house_list.end(); house_itr++){                               
            int owner = house_itr->second.getOwnerID();
            mem_itr = member_list.find(owner);
            house_itr->second.viewInfoHouse(mem_itr->second);            
        }
    }
    return true;
} 
void System::viewAllMembers(){ // method to view all members
    for (mem_itr = member_list.begin(); mem_itr != member_list.end(); mem_itr++){ 
        cout << "\n\t\t\t\t-------------------";                         
        cout << "\n\t\t\t\tMember info:\n";
        mem_itr->second.viewInfo();                
    }
}   
bool System::addHouse(Member& mem_house){ // method for a member to list a house   
    vector <int> houseid; // in-scope vector containing all houses id
    for (house_itr = house_list.begin(); house_itr != house_list.end(); house_itr++){
        houseid.push_back(house_itr->second.getID()); // copy all house ID
    }
    if (find(houseid.begin(),houseid.end(), mem_house.getHouseID()) != houseid.end()){ // if member already has/listed a house
        cout << "\n\t\t\t\tYou have already listed your house (each member can only have 1 house).\n";
        return false;
    } 

    // house obj creation
    string location_inp;
    string description_inp;
    string start_str;
    string end_str;      
    
    cout << "\n\t\t\t\tPlease enter location:\n";
    getline(cin, location_inp);
    cout << "\n\t\t\t\tPlease enter description:\n";
    getline(cin, description_inp);
    cout << "\n\t\t\t\tPlease enter start date:\n";      
    getline(cin, start_str);
    getDateInput(start_str);
    cout << "\n\t\t\t\tPlease enter end date:\n";
    getline(cin, end_str);
    getDateInput(end_str, start_str);        
    int cpoint_inp = inputNumber("consuming point per day");        
    cout << "\n\t\t\t\tEnter 0 if not specified):\n";
    double minr_inp = inputRating(); 
    House* temp = new House(generateHouseID(), location_inp, description_inp, Date(start_str), Date(end_str), 
                                cpoint_inp, minr_inp); // create house obj  
    int add_house_ID = temp->getID();
    temp->viewInfoHouse(mem_house); // allow user to view info of house       
    temp->setOwner(mem_house); // set id of owner for house object
    mem_house.setHouse(add_house_ID); // set house id for owner
    house_list.insert(pair<int, House>(add_house_ID, *temp)); // add house to house list
    return true;
}   
void System::searchHouse(Member mem){ // method for a member to search for a house
    string city_inp; // take in user inputs
    string start_str;
    string end_str;
    cout << "\n\t\t\t\tPlease enter location:\n\t\t\t\t";
    getline(cin, city_inp);        
    cout << "\n\t\t\t\tPlease enter start date:\n\t\t\t\t";
    getline(cin, start_str);
    getDateInput(start_str);
    cout << "\n\t\t\t\tPlease enter end date:\n\t\t\t\t";
    getline(cin, end_str);
    getDateInput(end_str, start_str);
    for (house_itr = house_list.begin(); house_itr != house_list.end(); house_itr++){ // traverse through house list           
        if (house_itr->second.isSuitableHouse(mem, Date(start_str), Date(end_str), city_inp, mem.getRating(), mem.getCpoint())
                    && mem.getID() != house_itr->second.getOwnerID()){ // if house is suitable
            suitable_house_ID_list.push_back(house_itr->second.getID()); // add house id to a suitable house id vector
        }
    }
    cout << "\n\t\t\t\tList of available houses:\n";
    for (int id : suitable_house_ID_list){ // show houses in the suitable house id vector           
        house_list[id].viewInfoHouse(member_list[house_list[id].getOwnerID()]);        
    }
    if (suitable_house_ID_list.empty()){ // no suitable house found (vector empty)
        cout << "\n\t\t\t\tNo houses available";
    }    
}

void System::RequestToOccupy(Member requester){ // method for a member to request a house
    // show member a list of suitable houses for them
    string city_inp;
    string start_str;
    string end_str;        
    cout << "\n\t\t\t\tPlease enter location:\n\t\t\t\t";
    getline(cin, city_inp);        
    cout << "\n\t\t\t\tPlease enter start date:\n\t\t\t\t";
    getline(cin, start_str);
    getDateInput(start_str);
    cout << "\n\t\t\t\tPlease enter end date:\n\t\t\t\t";
    getline(cin, end_str);
    getDateInput(end_str, start_str);
    Date start = Date(start_str);
    Date end = Date(end_str);
    for (house_itr = house_list.begin(); house_itr != house_list.end(); house_itr++){            
        if (house_itr->second.isSuitableHouse(requester, Date(start_str), Date(end_str), city_inp, requester.getRating(), requester.getCpoint())
                    && requester.getID() != house_itr->second.getOwnerID()){
            suitable_house_ID_list.push_back(house_itr->second.getID());
        }
    }
    cout << "\n\t\t\t\tList of available houses:\n";
    for (int id : suitable_house_ID_list){            
        house_list[id].viewInfoHouse(member_list[house_list[id].getOwnerID()]);        
    }
    if (suitable_house_ID_list.empty()){
        cout << "\n\t\t\t\tNo houses available.\n";
        return;
    }
    
    // ask user which house they want to request
    int requested_house_id = inputNumber("ID of the house you want to request");   
    bool is_id_in_suitable; 
    while(!is_id_in_suitable){ // if ID of house not in suitable house id vector
        for (int id : suitable_house_ID_list){ // find id of requested house            
            if (requested_house_id == id){
                is_id_in_suitable = true;
                break;
            }
        }          
        int requested_house_id = inputNumber("ID again"); // prompt user to input again
    } 

    // create new request obj if conditions met             
    Request* temp = new Request(generateRequestID(), requested_house_id, house_list[requested_house_id].getOwnerID(), requester.getID(), start, end); // create new req object     
    int reqID = temp->getReqID();
    requester.addRequestToList(reqID); //  add req id to owner's req list
    request_list.insert({reqID, *temp});// add req id to req list of system
    cout << "\n\t\t\t\tHouse requested successfully, details:\n"; 
    req_itr = request_list.find(reqID);
    req_itr->second.RequestInfo(requester); // display request info
}

void System::viewRequestList(Member owner){ // method for member to view request list
    cout << "\n\t\t\t\tNumber of requests: " << request_list.size() << endl;
    for (req_itr = request_list.begin(); req_itr != request_list.end(); req_itr++){ // traverse through system's request list
        if (req_itr->second.getOwnerID() == owner.getID()){ // find all requests that belong to the member
            int requester_id = req_itr->second.getRequesterID(); // find ID of the requester (the member who requested that house)
            Member requester_temp;
            for (mem_itr = member_list.begin(); mem_itr != member_list.end(); mem_itr++){
                if (mem_itr->second.getID() == requester_id){
                    requester_temp = mem_itr->second; // get requester
                }
            }
            req_itr->second.RequestInfo(requester_temp); // print request info (+name of requester)
        }
    }
}

int System::authenticateMemberLogin(){ //  method to implement log-in feature for member
    string checkusername;
    string checkpassword;
    int mem_id = -1;
    for (int uattempts = 0; uattempts < 3; uattempts++){ // each member has 3 username attempts
        cout << "\n\t\t\t\tYou have " << 3 - uattempts << " username attempts." << endl;                 
        cout << "\n\t\t\t\tUsername: ";
        getline(cin, checkusername);  
                          
        if (login_list.find(checkusername) == login_list.end()){ // if username doesnt exist
            cout << "\n\t\t\t\tCannot find username" << endl;
            continue;
        }
        else{ // if username correct/exists
            for (int pattempts = 0; pattempts < 3; pattempts++){ //each member has 3 password attempts
                cout << "\n\t\t\t\tFound username" << endl;
                cout << "\n\t\t\t\tYou have " << 3 - pattempts << " password attempts." << endl;
                cout << "\n\t\t\t\tPassword: ";
                getline(cin, checkpassword); 
                if (login_list[checkusername].getPassword().compare(checkpassword) == 0){ // check password
                    mem_id =login_list[checkusername].getID();
                    cout << "\n\t\t\t\tCorrect password!\n";
                    return mem_id;
                }
            }
        }                 
        cout << "\n\t\t\t\tIncorrect username or password, please enter again!\n";
    }
    return -1;
}
System::~System(){ // destructor for system obj (this gets called automatically when program ends)
    for (mem_itr = member_list.begin(); mem_itr != member_list.end(); mem_itr++){ 
        mem_itr->second.~Member(); // delete all member objs in heap
    }
    for (house_itr = house_list.begin(); house_itr != house_list.end(); house_itr++){
        house_itr->second.~House(); // delete all house objs in heap
    }
    for (req_itr = request_list.begin(); req_itr != request_list.end(); req_itr++){
        req_itr->second.~Request(); // delete all request objs in heap
    }
}