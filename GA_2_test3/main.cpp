#include <iostream>
#include <vector>
#include <string>
#include "App.cpp"
#include "House.cpp"
#include "Date.cpp"
#include "Review.cpp"
#include "Program.cpp"


using namespace std;

class System{
public:
    vector <Member*> member_list;
    vector <House*> house_list;
    vector <House*> suitable_house_list;
    System(){};
};  

int main(){
    System check;

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

    /*
    THIS SEGMENT IS FOR CODE CHECKING AND TESTINTG
    */

    // create members
    Member m1("thang", "0000");
    Member m2("ewrr", "eer");
    Member m3("ewrr", "eer");
    Member m4("ewrr", "eer");
        
    // create houses
    House h1("HCM", "A house");
    House h2("HCM", "aparment");
    House h3("HCM", "villa");
    House h4("HCM", "big house");

    // create connection between house and owner
    m1.setHouse(&h1);
    h1.setOwner(&m1);

    m2.setHouse(&h2);
    h2.setOwner(&m2);

    m3.setHouse(&h3);
    h3.setOwner(&m3);

    m4.setHouse(&h4);
    h4.setOwner(&m4);   

    
    // PRINT ALL MEMBERS INFO

    // for (Member* mem : check.member_list){
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

    Date test1("100522");
    Date test2("180522");

    // add house to list via members listing their house

    // check.house_list.push_back(getHouseToList(&m1, d1, d2, cpoint, minr));
    // check.house_list.push_back(getHouseToList(&m2, d3, d4, cpoint2, minr2));
    // check.house_list.push_back(getHouseToList(&m3, d5, d2, cpoint, minr));
    // check.house_list.push_back(getHouseToList(&m4, d3, d4, cpoint2, minr2));

    // print list
    
    // cout << "List of all houses:\n";
    // for (House* h : check.house_list){
    //     cout << "--------------\n";
    //     h->viewInfoHouse();  
    //     cout << "--------------\n";     
    // }
    
    // UNLIST
    
    // h2.setAvailability(def, def);
    // h2.setConsumingPoint(0);    
    // h2.setMinRate(0.0);
    // check.house_list.pop_back();
    // 


    // CHECK AVAILABLE HOUSES

    // for (House* h:check.house_list){
    //     if (isSuitableHouse(h, test1, test2, "HCM", 6, 120000)){
    //         check.suitable_house_list.push_back(h);
    //     }
    // }

    // PRINT SUITABLE HOUSES

    // cout << "Available houses:\n";
    // for (House* h : check.suitable_house_list){
    //     cout << "--------------\n";
    //     h->viewInfoHouse();  
    //     cout << "--------------\n";
    // }

    // Review r1("nice", 6.7);
    // r1.showReview();

    check.house_list.push_back(&h1);
    check.house_list.push_back(&h2);

    // program control
    bool runProg = true;    
    int Guess_mode = 1;
    int Member_mode = 2;
    int Admin_mode = 3;

    // run the program
    while (runProg)
    {

    welcomeScreen();
    int mode; // what mode to use 
    cin >> mode;
    
    if (mode == Guess_mode){ // AS GUESS
        GuessScreen();
        int guess_inp; // what to do as guess
        cin >> guess_inp;
        cin.sync(); // flush stream

        switch (guess_inp)
        {
        case 1:{ // new member registration
            cout << "Register to become member\n";
            string fname;
            string phone;
            cout << "Enter name: ";
            getline(cin, fname);            
            cout << "Enter phone: ";    
            getline(cin, phone);    
            Member* new_mem = new Member(fname, phone);
            check.member_list.push_back(new_mem);                         
            BackorExit(runProg);           
            break;
        }
        case 2:{ // list all houses
            cout << "---------------------\n";
            cout << "List of all houses:\n";
            for (House* hou : check.house_list){
                hou->viewInfoHouseGuess();
                cout << "--------------\n";
            }
            BackorExit(runProg); 
            break;
        }
        case 3:{ // go back to main menu
            runProg = true;
            break;
        }
        case 4:{ // exit
            runProg = false;
            break;
        }
        default:
            break;
        }        
    }

    if (mode == Member_mode){
        cout << "Please enter your username and password: ";
        cout << "Username: ";
        cout << "Password: ";

        MemberScreen(&m1);
        int member_inp;
        cin >> member_inp;
        cin.sync(); // flush stream

        switch (member_inp){
            case 1:
            m1.viewInfo();
            runProg = 0;
        }
    }

    if (mode == 3){
        std::cout << "You are an admin";
    }    

    
    }
}
    
    




