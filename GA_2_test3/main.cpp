#include <iostream>
#include <vector>
#include <iomanip>
#include <iterator>
#include <map>
#include <string>
#include <fstream>
#include "Date.h"
#include "Request.h"
#include "Member.h"
#include "App.cpp"
#include "House.h"
#include "Review.h"

// ver 170522

using namespace std;

template <typename T>
T getUserInput(T& userinp){// template to validate user numeric input  
    string line;    
    while (getline(cin, line)){                        
        std::stringstream ss(line);
        if (ss >> userinp)
        {
            if (ss.eof())
            {   // Success                
                ss >> userinp;
                break;
            }
        }
        cout << "Error, enter again:" << endl;        
    }
    // cin.clear();
    // cin.ignore(1000, '\n');
    return userinp;
}

// check if string is all digit
bool isDigit(string str){
    for (char c : str){
        if (!isdigit(c)){return false;}
    }  
    return true; 
}

// validate date
bool checkDate(int day, int month, int year) 
{  
  if (!(1<= month && month<=12)) //check months
     return false;
  if (! (1<= day && day<=31) ) // check days
     return false;
  // check months with 31 days
  if ((day==31) && (month==2 || month==4 || month==6 || month==9 || month==11))
     return false;
  if ((day==30) && (month==2)) // check february
     return false;
  // check february in leap years
  if ((month==2) && (day==29) && (year%4!=0)) 
     return false;
  if ((month==2) && (day==29) && (year%400==0))
     return true;
  if ((month==2) && (day==29) && (year%100==0))
     return false;
  if ((month==2) && (day==29) && (year%4==0))
     return true; 
  return true; // all others are true
}

// validate date input as string from user input
bool validateDateInput(string str){
    if (str.length() != 6 || !isDigit(str)){
        return false;
    }
    string sday = str.substr(0, 2);
    string smonth = str.substr(2, 2);
    string syear = str.substr(4, 2);
    int day = stoi(sday);
    int month = stoi(smonth);
    int year = stoi(syear);
    if (checkDate(day, month, year)){
        return true;
    };
    return false;
}

// validate and return correct date
string getDateInput(string& inp){ 
    while (inp.length() != 6 || !isDigit(inp) || !validateDateInput(inp)){
        cout << "Invalid, plese enter again: ";
        getline(cin, inp);         
    }     
    return inp;
}

enum AppMode {guest = 1, member = 2, admin = 3};

class System{
public:
    
    // map to store id of members, houses and requests 
    map <int, Member> member_list;
    map <int, House> house_list;
    map <int, Request> request_list;

    vector <House> suitable_house_list; // vector to display

    // iterators of maps
    map <int, Member>::iterator mem_itr;
    map <int, House>::iterator house_itr;
    map <int, Request>::iterator req_itr;

    System(){};

    void addMember(Member mem, int ID){
        member_list.insert(pair<int, Member>(ID, mem));
    }

    void viewHouses(int mode){
        if (mode == guest){
            for (house_itr = house_list.begin(); house_itr != house_list.end(); house_itr++){                
                int owner = house_itr->second.getOwnerID();
                mem_itr = member_list.find(owner);
                house_itr->second.viewInfoHouseGuest(mem_itr->second);
            }
        }

        if (mode == admin){
            for (house_itr = house_list.begin(); house_itr != house_list.end(); house_itr++){                               
                int owner = house_itr->second.getOwnerID();
                mem_itr = member_list.find(owner);
                house_itr->second.viewInfoHouse(mem_itr->second);
            }
        }
    } 

    void viewAllMembers(){
        for (mem_itr = member_list.begin(); mem_itr != member_list.end(); mem_itr++){ 
            cout << "-------------------\n\n";                           
            int houseid = mem_itr->second.getHouseID();
            //cout << "House id detected: " << houseid << "\n";
            cout << "Member info:\n";
            mem_itr->second.viewInfo();
            mem_itr->second.viewReqList();
            // cout << "House info(if applicable):";
            // house_itr = house_list.find(houseid);
            // house_itr->second.viewInfoHouse(mem_itr->second);
        }
    }   

    void addHouse(Member& mem_house){
        string location_inp;
        string description_inp;
        string start_str;
        string end_str;
        int cpoint_inp;
        double minr_inp;
        cout << "Please enter location:\n";
        getline(cin, location_inp);
        cout << "Please enter description:\n";
        getline(cin, description_inp);
        cout << "Please enter start date:\n";      
        getline(cin, start_str);
        getDateInput(start_str);
        cout << "Please enter end date:\n";
        getline(cin, end_str);
        getDateInput(end_str);
        cout << "Please enter consuming point per day:\n";
        cin >> cpoint_inp;
        cout << "Please enter minimum rating (enter 0 if not specified):\n";
        cin >> minr_inp;
        House* temp = new House(location_inp, description_inp, Date(start_str), Date(end_str), 
                                    cpoint_inp, minr_inp); // create house 
        int add_house_ID = temp->getID();
        temp->viewInfoHouse(mem_house);        
        temp->setOwner(mem_house); // set owner of house
        mem_house.setHouse(add_house_ID); // set house of owner
        house_list.insert(pair<int, House>(add_house_ID, *temp));
    }   

    void searchHouse(Member mem){
        string city_inp;
        string start_str;
        string end_str;

        cout << "Please enter location:\n";
        getline(cin, city_inp);        
        cout << "Please enter start date:\n";
        getline(cin, start_str);
        getDateInput(start_str);
        cout << "Please enter end date:\n";
        getline(cin, end_str);
        getDateInput(end_str);

        for (house_itr = house_list.begin(); house_itr != house_list.end(); house_itr++){
            cout << "Comparing\n";
            if (house_itr->second.isSuitableHouse(mem, Date(start_str), Date(end_str), 
                            city_inp, mem.getRating(), mem.getCpoint())){
                suitable_house_list.push_back(house_itr->second);
            }
        }

        cout << "List of available houses:\n";
        for (House house : suitable_house_list){
            int owner = house.getOwnerID();
            mem_itr = member_list.find(owner); // iterator of owner
            house.viewInfoHouse(mem_itr->second);        
        }
    }    

    void RequestToOccupy(Member requester){
        string city_inp;
        string start_str;
        string end_str;
        int id;

        cout << "Please enter location:\n";
        getline(cin, city_inp);        
        cout << "Please enter start date:\n";
        getline(cin, start_str);
        getDateInput(start_str);
        cout << "Please enter end date:\n";
        getline(cin, end_str);
        getDateInput(end_str);

        Date start = Date(start_str);
        Date end = Date(end_str);

        for (house_itr = house_list.begin(); house_itr != house_list.end(); house_itr++){
            cout << "Comparing\n";
            if (house_itr->second.isSuitableHouse(requester, Date(start_str), Date(end_str), 
                            city_inp, requester.getRating(), requester.getCpoint())){
                suitable_house_list.push_back(house_itr->second);
            }
        }

        cout << "List of available houses:\n";
        for (House house : suitable_house_list){
            int owner = house.getOwnerID();
            mem_itr = member_list.find(owner); // iterator of owner
            house.viewInfoHouse(mem_itr->second);        
        }
        cout << "Please enter the ID of the house you want to request:\n";
        cin >> id;
        int requested_house_id;
        int owner_id;
        for (House house : suitable_house_list){ // find requested house
            if (house.getID() == id){
                requested_house_id = house.getID();
                owner_id = house.getID();
            }
        }        
        Request* temp = new Request(requested_house_id, owner_id, requester.getID(), start, end); // create new req object     
        int reqID = temp->getReqID();
        requester.addRequestToList(reqID); //  add req to owner's req list
        request_list.insert({reqID, *temp});// add req to req list of system
        cout << "House requested successfully, details:\n"; 
        req_itr = request_list.find(reqID);
        req_itr->second.RequestInfo(requester);
    }

    void viewRequestList(Member owner){
        cout << "map length: " << request_list.size() << endl;
        for (req_itr = request_list.begin(); req_itr != request_list.end(); req_itr++){ 
            if (req_itr->second.getOwnerID() == owner.getID()){
                int requester_id = req_itr->second.getRequesterID();
                Member requester_temp;
                for (mem_itr = member_list.begin(); mem_itr != member_list.end(); mem_itr++){
                    if (mem_itr->second.getID() == requester_id){
                        requester_temp = mem_itr->second;
                    }
                }
                req_itr->second.RequestInfo(requester_temp);
            }
        }
    }
};  

int main(){
    System system;    

    /*
    RETRIEVE MEMBER DATA
    */
    fstream member_infle; // read from member.dat 
    member_infle.open("member.txt", ios::in);    
    while (!member_infle){
        cerr << "Cannot open file!";
    }
    string memline;
    int member_count = 0;
    while(member_infle.peek()!=EOF)
	{
		getline(member_infle, memline);        
		member_count++;
	}
    // put file pointer back to beginning of file
    member_infle.clear();
    member_infle.seekg(0);
    member_count = member_count/9;    
    for (int i = 0; i < member_count; i++){         
        // container
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

        // take data from file (1 line)        
        member_infle >> inmember_ID;               
        member_infle >> incredit; 
        // flush stream to use getline next 
        member_infle.clear();  
        member_infle.ignore(1000, '\n');
        getline(member_infle, infname); // full name can have white space        
        member_infle >> inuname;
        member_infle >> inpassword;
        member_infle >> inphone;       
        member_infle >> inoccupier_rate;       
        member_infle >> inhouse_ID_mem;
        member_infle >> size;      
                
        // take vector of int from file
        for (int i = 0 ; i < size; i++){             
            int ele;            
            member_infle >> ele;            
            req_list_id_in.push_back(ele);
        }      
        cout << endl; 

        // create new member obj based on parameters from file
        Member* memin = new Member(inmember_ID, incredit, infname, inuname,inpassword, inphone, inoccupier_rate, inhouse_ID_mem);  
        for (int i : req_list_id_in){
            memin->addRequestToList(i);
        }                
        // add member to member list
        system.member_list.insert({memin->getID(), *memin}); 
    }
    member_infle.close();    
    
    /*
    RETRIEVE HOUSE DATA
    */
    fstream house_infile; // read from house.dat 
    house_infile.open("house.txt", ios::in);   
    if (!house_infile){
        cerr << "Cannot open file!";
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
    house_count = house_count/9;       
    for (int i = 0; i < house_count; i++){ 
        // container
        int in_houseID = 0;
        int in_ownerID = 0;
        //int in_occupierID;
        string in_location;
        string in_description;
        int in_consuming_point = 0;        
        double in_min_rate = 0;    
        double in_house_rate = 0;
        string in_start_avai;   
        string in_end_avai;           
        
        // take data from file (1 line)
        house_infile >> in_houseID;             
        house_infile >> in_ownerID;         
        //house_infile >> in_occupierID;  
        // flush stream to use getline next 
        house_infile.clear();  
        house_infile.ignore(1000, '\n');
        getline(house_infile, in_location);
        getline(house_infile, in_description);                      
        house_infile >> in_consuming_point;        
        house_infile >> in_min_rate;         
        house_infile >> in_house_rate;
        house_infile >> in_start_avai;
        house_infile >> in_end_avai;         
        // create new house obj based on parameters from file
        House* housein = new House(in_houseID, in_ownerID, in_location, in_description,
                             in_consuming_point, in_min_rate, in_house_rate, Date(in_start_avai), Date(in_end_avai));
        
        // add house to member list
        system.house_list.insert({housein->getID(), *housein});    
    }
    house_infile.close();
    cout << "Number of houses: " << system.house_list.size() << endl;
    /*
    RETRIEVE REQUEST DATA
    */
    fstream request_infile;
    request_infile.open("request.dat", ios::in);
    // while (!request_infile){
    //     cerr << "Cannot open file!";
    // }
    string reqline;
    int req_count = 0;
    while(request_infile.peek()!=EOF)
	{
		getline(request_infile, reqline);
		req_count++;
	}
    request_infile.clear(); // flush stream
    request_infile.seekg(0); // put file pointer back to beginning of file
    req_count = req_count/6;    
    for (int i = 0; i < req_count; i++){ 
        // container
        int in_request_ID;
        int in_owner_ID;
        int in_requester_ID;
        int in_house_ID;        
        string in_start; // date
        string in_end;           
        
        // take data from file (1 line)
        request_infile >> in_request_ID;       
        request_infile >> in_owner_ID;
        request_infile >> in_requester_ID;  
        request_infile >> in_house_ID;  
        request_infile >> in_start; 
        request_infile >> in_end;     
       
        // create new request obj based on parameters from file
        Request* requestin = new Request(in_request_ID, in_owner_ID, in_requester_ID, in_house_ID, Date(in_start), Date(in_end));  
              
        // add house to member list
        system.request_list.insert({requestin->getReqID(), *requestin});      
    }
    request_infile.close();
    // cout << "size of memberlist: " << system.member_list.size() << endl;
    // cout << "size of houselist: " << system.house_list.size() << endl;
    // cout << "size of reqlist: " << system.request_list.size() << endl;
        
    // int i = getUserInput(i);
    // cout << "res of i is: " << i << endl;
    // string date;
    // cout << "Please enter date: ";
    // getline(cin, date);
    // getDateInput(date);    

    // program control
    bool runProg = true;  
    bool runProgGuest = false;
    bool runProgMember = false;
    bool runProgAdmin = false;
    enum mode {guest = 1, member = 2, admin = 3};

    // run the program
    while (runProg)
    {
    welcomeScreen();
    int mode = getUserInput(mode);    // what mode to use
    cin.clear();
    cin.ignore(1000, '\n');
    

    switch (mode)
    {
    case guest:{
        runProgGuest = true;
        enum guest_mode {mem_reg = 1, view_all = 2, back = 3, exit = 4};
        while (runProgGuest){
            GuessScreen();
            int guess_inp = getUserInput(guess_inp);
            // cin >> guess_inp; // what to do as guess  
            // getUserInput(guess_inp);          
            cin.clear();
            cin.ignore(1000, '\n'); // flush stream
            

            switch (guess_inp)
            {
            case mem_reg:{ // new member registration
                cout << "Register to become member\n";
                string fname;
                string phone;
                string uname;
                string password;
                cout << "Enter your full name: ";
                getline(cin, fname);            
                cout << "Enter your phone: ";    
                getline(cin, phone);  
                cout << "Enter your username: ";
                getline(cin, uname);            
                cout << "Enter your password: ";    
                getline(cin, password);  
                Member* new_mem = new Member(fname, uname, password, phone);                
                system.member_list.insert(pair<int, Member>(new_mem->getID(), *new_mem));   
                cout << "You are now a member. Here is your information\n";
                new_mem->viewInfo();
                cout << "\nPlease go back to main menu if you want to log in\n";
                BackorExit(runProg, runProgGuest, 1, 2, 3);           
                break;
            }
            case view_all:{ // list all houses
                cout << "---------------------\n";
                cout << "List of all houses:\n";
                system.viewHouses(guest);
                BackorExit(runProg, runProgGuest, 1, 2, 3);  
                break;
            }
            case back:{ // go back to main menu
                runProg = true;
                runProgGuest = false;
                break;
            }
            case exit:{ // exit
                runProg = false;
                runProgGuest = false;
                break;
            }
            default:
                break;
            }
        }
        
        break;
    }

    case member:{   
        int mem;
        enum member_mode {view_info = 1, list_house = 2, search = 3, req_to_occupy = 4, 
                            view_req = 5, accept_req = 6, back = 7, exit = 8};   

        // string checkusername;
        // string checkpassword;        
        // int mem_id = 0;
        // cout << "Please enter log in information:\n";        
        // while (true){                 
        //     cout << "Username: ";
        //     getline(cin, checkusername);
        //     cout << "Password: ";
        //     getline(cin, checkpassword);            
        //     for (system.mem_itr = system.member_list.begin(); system.mem_itr != system.member_list.end(); system.mem_itr++){
        //         cout << "username comparing: " << system.mem_itr->second.getUserName() << endl;
        //         cout << "password comparing: " << system.mem_itr->second.getPassword() << endl;
        //         cout << system.mem_itr->second.getUserName().compare(checkusername) << endl;
        //         cout << system.mem_itr->second.getPassword().compare(checkpassword) << endl;
        //         if ((system.mem_itr->second.getUserName().compare(checkusername)) && 
        //             (system.mem_itr->second.getPassword().compare(checkpassword))){
        //             cout << "Log in succesfully!\n";
        //             mem_id = system.mem_itr->second.getID();
        //             break;                    
        //         }                
        //     }
        //     cout << "Incorrect username or password, please enter again!\n";
        // }
        

        cout << "\nEnter member ID: ";
        cin >> mem;        
              
        /*
            IMPLEMENT LOG IN
        */
        runProgMember = true;
        while (runProgMember){
            MemberScreen(system.member_list.find(mem)->second);
            // int member_inp; 
            // cout << "Enter your choice: " ;
            // cin >> member_inp;
            int member_inp = getUserInput(member_inp);            
            cin.clear();
            cin.ignore(1000, '\n');
                  
             // flush stream
    
            switch (member_inp){

                case view_info:{
                    system.member_list.find(mem)->second.viewInfo();
                    BackorExit(runProg, runProgMember, 1, 2, 3);  
                    break;
                }
    
                case list_house:{                    
                    system.addHouse(system.member_list.find(mem)->second);                                      
                    BackorExit(runProg, runProgMember, 1, 2, 3); 
                    break;
                }   
                
                case search:{
                    system.searchHouse(system.member_list.find(mem)->second);
                    break;
                }
    
                case req_to_occupy:{
                    system.RequestToOccupy(system.member_list.find(mem)->second);
                    cout << "Request successfully";                    
                    BackorExit(runProg, runProgMember, 1, 2, 3);
                    break;
                }
    
                case view_req:{ // TEST LATER
                    system.viewRequestList(system.member_list.find(mem)->second);
                    BackorExit(runProg, runProgMember, 1, 2, 3);
                    break;
                }
    
                case accept_req:{ // ??
                    
                    break;
                }
    
                case back:{
                    runProg = true;
                    runProgMember = false;
                    break;
                }
    
                case exit:{
                    runProg = false;
                    runProgMember = false;
                    break;
    
                default:
                    break;
                }
            }
        }
        
        break;
    }

    case admin:{
        enum admin_mode {view_all_houses = 1, view_all_members = 2, back = 3, exit = 4}; 
        runProgAdmin = true;  
        while (runProgAdmin){
            
            cout << "1 to view all houses, 2 to view all members\n3 to go back, 4 to exit\n";
            int adminmode = getUserInput(adminmode);            

            switch (adminmode){
                case view_all_houses:{
                    system.viewHouses(admin);
                    BackorExit(runProg, runProgAdmin, 1, 2, 3);
                    break;
                }

                case view_all_members:{
                    system.viewAllMembers();
                    BackorExit(runProg, runProgAdmin, 1, 2, 3);
                    break;
                }

                case back:{
                    runProg = true;
                    runProgAdmin = false;
                    break;
                }

                case exit:{
                    runProg = false;
                    runProgAdmin = false;
                    break;
                }
                default:
                    break;
            }
        
        }        
        break;
    }
    default:
        break;
    } 

    
    }
    //cout << "write to file!" << endl;
    fstream member_outfile;
    member_outfile.open("member.txt", ios::out);
    //out << "file opened!";
    for (auto& mem : system.member_list){       
        member_outfile << mem.second.getID() << endl;
        member_outfile << mem.second.getCpoint() << endl;
        member_outfile << mem.second.getFullName() << endl;
        member_outfile << mem.second.getUserName() << endl;
        member_outfile << mem.second.getPassword() << endl;
        member_outfile << mem.second.getPhone() << endl;
        member_outfile << mem.second.getRating() << endl;
        member_outfile << mem.second.getHouseID() << endl;
        member_outfile << mem.second.getReqList().size() << " ";
        for(int i : mem.second.getReqList()){
            member_outfile << i << " ";
        }
        member_outfile << endl;
    }
    // cout << "wrote to file";
    // member_outfile << "test!";
    member_outfile.close();
    
    fstream house_outfile;
    house_outfile.open("house.txt", ios::out);
    for (auto& house : system.house_list){
        house_outfile << house.second.getID() << endl;        
        house_outfile << house.second.getOwnerID() << endl;        
        // house_outfile << house.second.getOccupierID() << endl;
        // cout << house.second.getOccupierID() << endl;
        house_outfile << house.second.getLocation() << endl;        
        house_outfile << house.second.getDescription() << endl;        
        house_outfile << house.second.getConsumingP() << endl;        
        house_outfile << house.second.getMinrate() << endl; 
        house_outfile << house.second.getHouseRating() << endl;   
        house_outfile << house.second.getStartAvai().getDateAsString() << endl;        
        house_outfile << house.second.getEndAvai().getDateAsString() << endl;        
    }
    house_outfile.close();

    fstream req_outfile;
    req_outfile.open("request.dat", ios::out);
    for (auto& req : system.request_list){
        req_outfile << req.second.getReqID() << endl;
        req_outfile << req.second.getHouseID() << endl;
        req_outfile << req.second.getOwnerID() << endl;
        req_outfile << req.second.getRequesterID() << endl;       
        req_outfile << req.second.getStart().getDateAsString() << endl;
        req_outfile << req.second.getEnd().getDateAsString() << endl;
    }
    req_outfile.close();
}
    
    




