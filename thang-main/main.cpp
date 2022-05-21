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

using namespace std;

// check if string is all digit 0-9
bool isDigit(string str){    
    if (str.size() > 10){return false;}
    for (char c : str){
        if (!isdigit(c)){return false;}
    }  
    return true; 
}

int inputNumber(string prompt){
    cout << "Please enter " << prompt << " :";
    string temp; 
    getline(cin, temp);
    while (temp.size() == 0 || !isDigit(temp)){
        cout << "Invalid input, please enter again: ";
        getline(cin, temp);              
    }
    int num = stoi(temp);
    return num;
}

int inputNumber(string str, int maxsize){
    int temp = inputNumber(str);
    while(temp <0 || temp>maxsize) {
        temp = inputNumber(str + " less than " + to_string(maxsize+1));
    }
    return temp;
}

double inputRating(){ 
    double num;
    int minus_count = 0;    
    int decimal_count = 0;    
    bool isDouble = false;
    string temp;    

    while (!isDouble){
        cout << "Enter rating from -10 to 10: " ;
        getline(cin, temp);
        while (temp.size() == 0){
            cout << "Input empty, enter again";
            getline(cin, temp);
        }
        minus_count = 0;    
        decimal_count = 0;
        isDouble = true;
        for (char c : temp){
            if (c == '-'){minus_count++;} 
            if (c == '.'){decimal_count++;}
            if (minus_count > 1 || decimal_count>1){                
                isDouble = false;            
                break; // break for
            }           
        } 
        if (!(minus_count == 0 || (minus_count == 1 && temp[0] == '-')) 
                && (decimal_count == 0 || decimal_count == 1) ) {                  
            isDouble = false;            
        }
        else {
            string temp_no_sign = temp;            
            if (minus_count == 1){
                temp_no_sign.erase(0, 1);                
            }
            if (decimal_count == 1){
                temp_no_sign.erase(temp_no_sign.find('.'),1);                
            }
            if (!isDigit(temp_no_sign)){                
                isDouble = false;                
            }
            if (isDouble == true) {
                num = stod(temp);
                cout << "num: " << num << endl;
                if (-10 <= num && num <= 10){
                    cout << "in range!" << endl;
                    return num;
                }
                else{isDouble = false;}
            }            
        }        
    }
    return num;
}

string inputPhone(){
    cout << "Enter phone: " ;
    string temp; // 12 thang
    getline(cin, temp);
    while (!isDigit(temp) || temp.size() != 10){
        cout << "Invalid phone number, please enter again: ";
        getline(cin, temp);              
    }    
    return temp;    
}

string inputString(string prompt){ // a-z, A-Z, 0-9
    cout << "Please enter " << prompt << ": ";
    string str; // 12 thang
    bool hasSpace = false;
    getline(cin, str);
    while (str.size() == 0){
        cout << prompt << " cannot be empty\n";
        getline(cin, str);
    }
    for (char c : str){
        if (isspace(c)){hasSpace = true;}
    }
    while (hasSpace){
        cout << "Invalid string, please enter again (no space): ";
        getline(cin, str);
        hasSpace = false;
        for (char c : str){
            if (isspace(c)){hasSpace = true;}
        }
        if (hasSpace == false) break;
    }    
    return str; 
}

void welcomeScreen(){ // display main menu 
        cout << "EEET2482/COSC2082 ASSIGNMENT \n";
        cout << "VACATION HOUSE EXCHANGE APPLICATION \n\n";
        cout << "Instructor: Mr. Linh Tran \n";
        cout << "Group: Group Name \n";
        cout << "s3872105, Nguyen Ngoc Thang \n";
        cout << "sXXXXXXX, Student Name \n";
        cout << "sXXXXXXX, Student Name \n\n";
        cout << "Use the app as 1. Guest   2. Member   3. Admin \n";           
}

void GuessScreen(){ // display screen for guess
    cout << "You are a guest\n";    
    cout << "1. Register to become a member\n";
    cout << "2. View all houses (with limited visibility)\n";
    cout << "3. Go back to main menu\n";
    cout << "4. Exit the program\n";
    cout << "What would you like to do?\n";    
}

void MemberScreen(Member mem){ // display screen for member
    cout << "Welcome back, " << mem.getFullName() << endl;        
    cout << "1. View your information\n";
    cout << "2. List your house available (with/without minimumm rating required)\n";    
    cout << "3. Search for a house\n";
    cout << "4. Request to occupy a house\n";
    cout << "5. View all requests to your listed house\n";
    cout << "6. Accept a request to your listed house\n";
    cout << "7. Go back to main menu\n";
    cout << "8. Exit the program\n";
    cout << "What would you like to do?\n";    
}

void AdminScreen(){          
    cout << "1. View all houses\n";
    cout << "2. View all members\n";
    cout << "3. Go back to main menu\n";
    cout << "4. Exit the program\n";    
}

void BackorExit(bool& run_prog, bool& run_subprog, int prog, int subprog, int exit){ // function for going back to main menu or exit prog    
    cout << "PRESS "<< prog << " TO RETURN TO MAIN MENU\n";
    cout << "PRESS "<< subprog << " TO GO BACK \n";
    cout << "PRESS "<< exit << " TO EXIT \n";
    int temp = inputNumber("your choice", exit);
    if (temp == run_prog){ //main menu
        run_prog = true;
        run_subprog = false;
        
    }

    if (temp == subprog){ // sub menu
        run_prog = true;
        run_subprog = true;
    }

    if (temp == exit){
        run_prog = false;
        run_subprog = false;
    }

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
        cout << "Invalid date, plese enter again: ";
        getline(cin, inp);         
    }     
    return inp;
}

string getDateInput(string& inp, string sstart){ 
    Date start(sstart);    
    Date end(getDateInput(inp));
    while (start > end){        
        cout << "Start date cannot be later than end date: ";
        getline(cin, inp);
        end.updateDate(inp);         
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
    map <string, Member> login_list;

    vector <int> suitable_house_ID_list; // vector to display


    // iterators of maps
    map <int, Member>::iterator mem_itr;
    map <int, House>::iterator house_itr;
    map <int, Request>::iterator req_itr;    

    System(){};

    int generateMemberID(){
        vector <int> idlist;  
        // vector <int>::iterator it;      
        for (mem_itr = member_list.begin(); mem_itr != member_list.end(); mem_itr++)
            idlist.push_back(mem_itr->second.getID());
        int random_id;
        srand(time(0));
        random_id = (rand() % 5);

        while (find(idlist.begin(),idlist.end(), random_id) != idlist.end()){            
            srand(time(0));
            random_id = (rand() % 5);
        }   
        return random_id;   
    }

    int generateHouseID(){
        vector <int> idlist;        
        for (house_itr = house_list.begin(); house_itr != house_list.end(); house_itr++)
            idlist.push_back(house_itr->second.getID());
        int random_id;
        srand(time(0));
        random_id = (rand() % 5);

        while (find(idlist.begin(),idlist.end(), random_id) != idlist.end()){            
            srand(time(0));
            random_id = (rand() % 5);
        }   
        return random_id;    
    }

    int generateRequestID(){
        vector <int> idlist;        
        for (req_itr = request_list.begin(); req_itr != request_list.end(); req_itr++)
            idlist.push_back(req_itr->second.getReqID());
        int random_id;
        srand(time(0));
        random_id = (rand() % 5);

        while (find(idlist.begin(),idlist.end(), random_id) != idlist.end()){            
            srand(time(0));
            random_id = (rand() % 5);
        } 
        return random_id;      
    }

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
        
        cout << "Please enter location:\n";
        getline(cin, location_inp);
        cout << "Please enter description:\n";
        getline(cin, description_inp);
        cout << "Please enter start date:\n";      
        getline(cin, start_str);
        getDateInput(start_str);
        cout << "Please enter end date:\n";
        getline(cin, end_str);
        getDateInput(end_str, start_str);        
        int cpoint_inp = inputNumber("consuming point per day");        
        cout << "Enter 0 if not specified):\n";
        double minr_inp = inputRating(); // TO
        House* temp = new House(generateHouseID(), location_inp, description_inp, Date(start_str), Date(end_str), 
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
        getDateInput(end_str, start_str);

        for (house_itr = house_list.begin(); house_itr != house_list.end(); house_itr++){            
            if (house_itr->second.isSuitableHouse(mem, Date(start_str), Date(end_str), city_inp, mem.getRating(), mem.getCpoint())
                        && mem.getID() != house_itr->second.getOwnerID()){
                suitable_house_ID_list.push_back(house_itr->second.getID());
            }
        }

        cout << "\nList of available houses:\n";
        for (int id : suitable_house_ID_list){            
            house_list[id].viewInfoHouse(member_list[house_list[id].getOwnerID()]);        
        }
        if (suitable_house_ID_list.empty()){
            cout << "No houses available";
        }
        cout << "list length: " << suitable_house_ID_list.size();
    }    

    void RequestToOccupy(Member requester){
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
        getDateInput(end_str, start_str);

        Date start = Date(start_str);
        Date end = Date(end_str);

        for (house_itr = house_list.begin(); house_itr != house_list.end(); house_itr++){            
            if (house_itr->second.isSuitableHouse(requester, Date(start_str), Date(end_str), city_inp, requester.getRating(), requester.getCpoint())
                        && requester.getID() != house_itr->second.getOwnerID()){
                suitable_house_ID_list.push_back(house_itr->second.getID());
            }
        }

        cout << "\nList of available houses:\n";
        for (int id : suitable_house_ID_list){            
            house_list[id].viewInfoHouse(member_list[house_list[id].getOwnerID()]);        
        }
        if (suitable_house_ID_list.empty()){
            cout << "No houses available.\n";
            return;
        }
        
        int requested_house_id = inputNumber("ID of the house you want to request");   
        bool is_id_in_suitable; 
        while(!is_id_in_suitable){
            for (int id : suitable_house_ID_list){ // find id of requested house            
                if (requested_house_id == id){
                    is_id_in_suitable = true;
                    break;
                }
            }          
            int requested_house_id = inputNumber("ID again");
        } 
                     
        Request* temp = new Request(generateRequestID(), requested_house_id, house_list[requested_house_id].getOwnerID(), requester.getID(), start, end); // create new req object     
        int reqID = temp->getReqID();
        requester.addRequestToList(reqID); //  add req to owner's req list
        request_list.insert({reqID, *temp});// add req to req list of system
        cout << "House requested successfully, details:\n"; 
        req_itr = request_list.find(reqID);
        req_itr->second.RequestInfo(requester);
    }

    void viewRequestList(Member owner){
        cout << "request list length: " << request_list.size() << endl;
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

    int authenticateMemberLogin(){
        string checkusername;
        string checkpassword;
        int mem_id = -1;
        for (int uattempts = 0; uattempts < 3; uattempts++){
            cout << "You have " << 3 - uattempts << " username attempts." << endl;                 
            cout << "Username: ";
            getline(cin, checkusername);  
                              
            if (login_list.find(checkusername) == login_list.end()){ //
                cout << "Cannot find username" << endl;
                continue;
            }
            else{
                for (int pattempts = 0; pattempts < 3; pattempts++){
                    cout << "Found username" << endl;
                    cout << "You have " << 3 - pattempts << " password attempts." << endl;
                    cout << "Password: ";
                    getline(cin, checkpassword); 

                    if (login_list[checkusername].getPassword().compare(checkpassword) == 0){
                        mem_id =login_list[checkusername].getID();
                        cout << "Correct password!\n";
                        return mem_id;
                    }
                }
            } 
                    
            cout << "Incorrect username or password, please enter again!\n";
        }
        return -1;
    }

    ~System(){
        for (mem_itr = member_list.begin(); mem_itr != member_list.end(); mem_itr++){ 
            mem_itr->second.~Member();
        }

        for (house_itr = house_list.begin(); house_itr != house_list.end(); house_itr++){
            house_itr->second.~House();
        }

        for (req_itr = request_list.begin(); req_itr != request_list.end(); req_itr++){
            req_itr->second.~Request();
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
        
        system.member_list.insert({memin->getID(), *memin}); // add member to member list
        system.login_list.insert({memin->getUserName(), *memin}); // add login info to member list
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
    int mode = inputNumber("your choice", admin);    // what mode to use      
    
    switch (mode)
    {
    case guest:{
        runProgGuest = true;
        enum guest_mode {mem_reg = 1, view_all = 2, back = 3, exit = 4};
        while (runProgGuest){
            GuessScreen();
            int guess_inp = inputNumber("your choice", exit);           
            
            switch (guess_inp)
            {
            case mem_reg:{ // new member registration
                cout << "Register to become member\n";
                string fname;                
                cout << "Enter your full name: ";
                getline(cin, fname);           
                string phone = inputPhone();                 
                string uname = inputString("your username");      
                string password = inputString("your password");                
                Member* new_mem = new Member(system.generateMemberID(), fname, uname, password, phone);                           
                system.member_list.insert({new_mem->getID(), *new_mem}); 
                system.login_list.insert({new_mem->getUserName(), *new_mem});  
                cout << "\nYou are now a member. Here is your information\n";
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
                cout << "No such choice, choose again!";
                runProgGuest = true;                
            }
        }
        
        break;
    }

    case member:{   
        int mem;
        enum member_mode {view_info = 1, list_house = 2, search = 3, req_to_occupy = 4, 
                            view_req = 5, accept_req = 6, back = 7, exit = 8};  
        cout << "Please enter log in information:\n";
        int mem_id = system.authenticateMemberLogin();      
        if (mem_id == -1){
            cout << "Too many fail attempts, exited the program" << endl;
            runProg = false;
            break;            
        }              
        
        runProgMember = true;
        while (runProgMember){
            MemberScreen(system.member_list.find(mem_id)->second);            
            int member_inp = inputNumber("your choice", exit);          
            switch (member_inp){

                case view_info:{
                    system.member_list.find(mem_id)->second.viewInfo();
                    BackorExit(runProg, runProgMember, 1, 2, 3);  
                    break;
                }
    
                case list_house:{                    
                    system.addHouse(system.member_list.find(mem_id)->second);                                      
                    BackorExit(runProg, runProgMember, 1, 2, 3); 
                    break;
                }   
                
                case search:{
                    system.searchHouse(system.member_list.find(mem_id)->second);
                    break;
                }
    
                case req_to_occupy:{
                    system.RequestToOccupy(system.member_list.find(mem_id)->second);                                        
                    BackorExit(runProg, runProgMember, 1, 2, 3);
                    break;
                }
    
                case view_req:{ // TEST LATER
                    system.viewRequestList(system.member_list.find(mem_id)->second);
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
                    cout << "No such choice, choose again!";
                    runProgMember = true;
                }
            }
        }
        
        break;
    }

    case admin:{
        enum admin_mode {view_all_houses = 1, view_all_members = 2, back = 3, exit = 4}; 
        // USERNAME: sedtest
        // PASSWORD: HD100
        string adminusername;
        string adminpassword;        
        runProgAdmin = false;

        for (int uattempts = 0; uattempts < 3 && runProgAdmin == false; uattempts++){
            cout << "You have " << 3 - uattempts << " username attempts." << endl;                 
            cout << "Username: ";
            getline(cin, adminusername);  
                              
            if (adminusername.compare("sedtest") != 0){ //
                cout << "Wrong admin username" << endl;
                continue;
            }
            else{
                cout << "Correct username" << endl;
                for (int pattempts = 0; pattempts < 3 && runProgAdmin == false; pattempts++){
                    
                    cout << "You have " << 3 - pattempts << " password attempts." << endl;
                    cout << "Password: ";
                    getline(cin, adminpassword); 

                    if (adminpassword.compare("HD100") == 0){                        
                        cout << "Correct password!\n";
                        runProgAdmin = true;                                                                      
                    }
                }
                //admin right, pw wrong
                break; 
            }                  
        }      
        if(runProgAdmin == false){
            cout << "Too many fail attempts. Exit program";
            runProg = false;
        }   
                  
        while (runProgAdmin){
            
            AdminScreen();
            int adminmode = inputNumber("your choice", exit);                        

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
                    cout << "No such choice, choose again!";
                    runProgAdmin = true;                   
            }
        
        }        
        break;
    }
    default:
        cout << "No such choice, choose again!";
        runProg = true;        
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
    
    




