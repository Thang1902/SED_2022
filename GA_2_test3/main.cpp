#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <string>
#include "App.cpp"
#include "House.cpp"
#include "Date.cpp"
#include "Review.cpp"
#include "Request.cpp"

// ver 170522

using namespace std;

enum mode {guest = 1, member = 2, admin = 3};

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
                cout << "map length: " << house_list.size() << "\n";              
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
            cout << "Member info:\n";
            mem_itr->second.viewInfo();
            cout << "House info(if applicable):";
            house_itr = house_list.find(houseid);
            house_itr->second.viewInfoHouse(mem_itr->second);
        }
    }   

    void addHouse(Member mem_house){
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
        cout << "Please enter end date:\n";
        getline(cin, end_str);
        cout << "Please enter consuming point per day:\n";
        cin >> cpoint_inp;
        cout << "Please enter minimum rating:\n";
        cin >> minr_inp;
        House* temp = new House(location_inp, description_inp, Date(start_str), Date(end_str), 
                                    cpoint_inp, minr_inp); // create house 
        int add_house_ID = temp->getID();
        temp->setOwner(mem_house); // set owner of house
        mem_house.setHouse(*temp); // set house of owner
        house_list.insert(pair<int, House>(add_house_ID, *temp));
    }

    void addHouseNoRating(Member mem_house){
        string location_inp;
        string description_inp;
        string start_str;
        string end_str;
        int cpoint_inp;        
        cout << "Please enter location:\n";
        getline(cin, location_inp);
        cout << "Please enter description:\n";
        getline(cin, description_inp);
        cout << "Please enter start date:\n";
        getline(cin, start_str);
        cout << "Please enter end date:\n";
        getline(cin, end_str);
        cout << "Please enter consuming point per day:\n";
        cin >> cpoint_inp;        
        House* temp = new House(location_inp, description_inp, Date(start_str), Date(end_str), 
                                    cpoint_inp);
        int add_house_ID = temp->getID();
        temp->setOwner(mem_house); // set owner of house
        mem_house.setHouse(*temp); // set house of owner
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
        cout << "Please enter end date:\n";
        getline(cin, end_str);

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
        cout << "Please enter end date:\n";
        getline(cin, end_str);

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
        request_list.insert(pair<int, Request>(reqID, *temp));// add req to req list of system
        cout << "House requested successfully, details:\n"; 
        req_itr = request_list.find(reqID);
        req_itr->second.RequestInfo(requester);
    }


};  

int main(){
    System system;
    // load data 
    // while (file){
        // fetch data
        // Member* temp = new Member(data from file); // defined at compile time
        // system.member_list.push_back(temp);
    // } 

    // load members

    // create members
    Member m1("thang1", "0000");
    m1.setID(1);
    m1.setCredit(100000);
    m1.setRating(10);
    Member m2("thang2", "0001");
    m2.setID(2);
    m2.setCredit(100000);
    m2.setRating(10);
    Member m3("thang3", "0002");
    m3.setID(3);
    Member m4("thang4", "0003");
    m4.setID(4);

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
    h1.setID(1);    
    House h2("Ha Noi", "A 3-bedroom aparment", d3, d4, 150, 4.9);
    h2.setID(2);    
    House h3("Da Nang", "A sea-view villa", d1, d3, 500, 3.8);
    h3.setID(3);    
    House h4("HCM", "Boutique house", d2, d4, 360, 8.9);
    h4.setID(4);
    

    // create connection between house and owner
    m1.setHouse(h1);
    h1.setOwner(m1);
    m2.setHouse(h2);
    h2.setOwner(m2);
    m3.setHouse(h3);
    h3.setOwner(m3);
    m4.setHouse(h4);
    h4.setOwner(m4);    
    
    Date test1("100522");
    Date test2("180522");    

    /*
    TEST
    */
    // insert members to map
    system.member_list.insert({m1.getID(), m1});    
    system.member_list.insert({m2.getID(), m2});    
    system.member_list.insert({m3.getID(), m3});    
    system.member_list.insert({m4.getID(), m4});       

    // insert house to map
    system.house_list.insert(pair<int, House>(h1.getID(), h1));
    system.house_list.insert(pair<int, House>(h2.getID(), h2));
    system.house_list.insert(pair<int, House>(h3.getID(), h3));
    system.house_list.insert(pair<int, House>(h4.getID(), h4));

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
    int mode; // what mode to use 
    cin >> mode;
    cin.clear();
    cin.ignore(1000, '\n');

    switch (mode)
    {
    case guest:{
        runProgGuest = true;
        enum guest_mode {mem_reg = 1, view_all = 2, back = 3, exit = 4};
        while (runProgGuest){
            GuessScreen();
            int guess_inp; // what to do as guess
            cin >> guess_inp;
            cin.clear();
            cin.ignore(1000, '\n'); // flush stream

            switch (guess_inp)
            {
            case mem_reg:{ // new member registration
                cout << "Register to become member\n";
                string fname;
                string phone;
                cout << "Enter name: ";
                getline(cin, fname);            
                cout << "Enter phone: ";    
                getline(cin, phone);    
                Member* new_mem = new Member(fname, phone);                
                system.member_list.insert(pair<int, Member>(new_mem->getID(), *new_mem));                  
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

        enum member_mode {view_info = 1, list_house = 2, list_house_no_rating = 3,
                            search = 4, req_to_occupy = 5, view_req = 6, 
                            accept_req = 7, back = 8, exit = 9};   

        cout << "Please enter your username and password: ";
        cout << "Username: ";
        cout << "Password: ";

        /*
            IMPLEMENT LOG IN
        */
        runProgMember = true;
        while (runProgMember){
            MemberScreen(m2);
            int member_inp;
            cin >> member_inp;
            cin.clear();
            cin.ignore(1000, '\n'); // flush stream
    
            switch (member_inp){

                case view_info:{
                    m2.viewInfo();
                    BackorExit(runProg, runProgMember, 1, 2, 3);  
                    break;
                }
    
                case list_house:{                    
                    system.addHouse(m2);                                      
                    BackorExit(runProg, runProgMember, 1, 2, 3); 
                    break;
                }
    
                case list_house_no_rating:{
                    system.addHouse(m2);
                    BackorExit(runProg, runProgMember, 1, 2, 3);
                    break;
                }
    
                case search:{
                    system.searchHouse(m2);
                    break;
                }
    
                case req_to_occupy:{
                    system.RequestToOccupy(m2);
                    BackorExit(runProg, runProgMember, 1, 2, 3);
                    break;
                }
    
                // case view_req:{ // TEST LATER
                //     m2.viewAllReq();
                //     BackorExit(runProg, runProgMember, 1, 2, 3);
                //     break;
                // }
    
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
            int adminmode;
            cout << "1 to view all houses, 2 to view all members\n3 to go back, 4 to exit\n";
            cout << "Please enter what mode: ";
            cin >> adminmode;

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

    // string fname;
    // string phone;
    // cout << "Enter name:" << endl;
    // getline(cin, fname);
    // cout << "Enter phone:" << endl;
    // getline(cin, phone);
    // Member m1(fname, phone);

    // string location;
    // string description;
    // cout << "Enter location:" << endl;
    // getline(cin, location);
    // cout << "Enter description:" << endl;
    // getline(cin, description);
    // House h1(location, description);
    // add house to list via members listing their house

    // system.house_list.push_back(getHouseToList(&m1, d1, d2, cpoint, minr));
    // system.house_list.push_back(getHouseToList(&m2, d3, d4, cpoint2, minr2));
    // system.house_list.push_back(getHouseToList(&m3, d5, d2, cpoint, minr));
    // system.house_list.push_back(getHouseToList(&m4, d3, d4, cpoint2, minr2));

    // print list
    
    // cout << "List of all houses:\n";
    // for (House* h : system.house_list){
    //     cout << "--------------\n";
    //     h->viewInfoHouse();  
    //     cout << "--------------\n";     
    // }
    
    // UNLIST
    
    // h2.setAvailability(def, def);
    // h2.setConsumingPoint(0);    
    // h2.setMinRate(0.0);
    // system.house_list.pop_back();
    // 


    // CHECK AVAILABLE HOUSES

    // for (House* h:system.house_list){
    //     if (isSuitableHouse(h, test1, test2, "HCM", 6, 120000)){
    //         system.suitable_house_list.push_back(h);
    //     }
    // }

    // PRINT SUITABLE HOUSES

    // cout << "Available houses:\n";
    // for (House* h : system.suitable_house_list){
    //     cout << "--------------\n";
    //     h->viewInfoHouse();  
    //     cout << "--------------\n";
    // }

    // Review r1("nice", 6.7);
    // r1.showReview(); 

    // PRINT ALL MEMBERS INFO

    // for (Member* mem : system.member_list){
    //     mem->viewInfo();
    //     mem->getHouse()->viewInfoHouse();
    // }    


    // OCCUPIER RATING 

    // m2.rateOccupier(&m1, 3.4);
    // m2.rateOccupier(&m1, 7.2);
    // m2.rateOccupier(&m1, 4.7);
    // m2.rateOccupier(&m1, 3.4);
    // m2.rateOccupier(&m1, 7.2);
    // m2.rateOccupier(&m1, 4.2);
    // m2.rateOccupier(&m1, 9.4);
    // m2.rateOccupier(&m1, 2.2);
    // m2.rateOccupier(&m1, 5.7);
    // cout << "The rating of " << m1.getFullName() << " is: " << m1.cal_occupier_rate();  
    }
}
    
    




