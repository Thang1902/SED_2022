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

int main(){
    System system; // create system object to manage program   

    /*
    RETRIEVE MEMBER DATA
    */  
    system.importMember();
    system.importHouse();
    system.importRequest();  
      

    // program control button
    bool runProg = true;
    bool runProgGuest = false;
    bool runProgMember = false;
    bool runProgAdmin = false; 

    /*
    PROGRAM RUN
    */     
    cout << "\n\t\t\t\tEEET2482/COSC2082 ASSIGNMENT\n";
    cout << "\t\t\t\tInstructor: Mr. Linh Tran \n\n";
    while (runProg) // outer loop
    {
    welcomeScreen();
    int mode = inputNumber("your choice", admin); // what mode to use      
    
    switch (mode)
    {
    case guest:{
        runProgGuest = true;
        enum guest_mode {mem_reg = 1, view_all = 2, back = 3, exit = 4};

        while (runProgGuest){ // inner loop for guest
            GuessScreen();
            int guess_inp = inputNumber("your choice", exit);           
            
            switch (guess_inp)
            {
            case mem_reg:{ // new member registration
                cout << "\n\t\t\t\tYou have selected to register to become member\n";
                string fname;                
                cout << "\n\t\t\t\tEnter your full name:\n\t\t\t\t"; // have whitespace
                getline(cin, fname);           
                string phone = inputPhone();                 
                string uname = inputString("your username");      
                string password = inputString("your password");                
                Member* new_mem = new Member(system.generateMemberID(), fname, uname, password, phone); // new obj created                           
                system.member_list.insert({new_mem->getID(), *new_mem}); // add to member list
                system.login_list.insert({new_mem->getUserName(), *new_mem}); // add to login list
                cout << "\n\t\t\t\tYou are now a member. Here is your information\n";
                new_mem->viewInfo();
                cout << "\n\t\t\t\tPlease go back to main menu if you want to log in\n";
                BackorExit(runProg, runProgGuest, 1, 2, 3);           
                break;
            }

            case view_all:{ // list all houses
                cout << "\n\t\t\t\t-----------------------\n";
                cout << "\n\t\t\t\tList of all houses:\n";
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

            default: // wrong number input
                cout << "\n\t\t\t\tNo such choice, choose again!: ";
                runProgGuest = true;                
            }
        }
        
        break;
    }

    case member:{   
        int mem;
        enum member_mode {view_info = 1, list_house = 2, search = 3, req_to_occupy = 4, 
                            view_req = 5, accept_req = 6, back = 7, exit = 8};  
        cout << "\n\t\t\t\tPlease enter log in information:\n";
        int mem_id = system.authenticateMemberLogin(); // log in feature      
        if (mem_id == -1){
            cout << "\n\t\t\t\tToo many fail attempts, exited the program" << endl;
            runProg = false;
            break;            
        } 
        // member verified            
        runProgMember = true;
        while (runProgMember){ // inner loop for member
            MemberScreen(system.member_list.find(mem_id)->second);            
            int member_inp = inputNumber("your choice", exit); 

            switch (member_inp){
                case view_info:{ // view their information
                    system.member_list.find(mem_id)->second.viewInfo();
                    BackorExit(runProg, runProgMember, 1, 2, 3);  
                    break;
                }
    
                case list_house:{ // list their house                    
                    system.addHouse(system.member_list.find(mem_id)->second);                                      
                    BackorExit(runProg, runProgMember, 1, 2, 3); 
                    break;
                }   
                
                case search:{ // search for a house
                    system.searchHouse(system.member_list.find(mem_id)->second);
                    break;
                }
    
                case req_to_occupy:{ // request to occupy a house
                    system.RequestToOccupy(system.member_list.find(mem_id)->second);                                        
                    BackorExit(runProg, runProgMember, 1, 2, 3);
                    break;
                }
    
                case view_req:{ // view all request to their house
                    system.viewRequestList(system.member_list.find(mem_id)->second);
                    BackorExit(runProg, runProgMember, 1, 2, 3);
                    break;
                }
    
                case accept_req:{ 
                    cout << "\n\t\t\t\tThis feature is exempted, thus not implemented!\n";
                    BackorExit(runProg, runProgMember, 1, 2, 3);
                    break;
                }
    
                case back:{ // go back to main menu
                    runProg = true;
                    runProgMember = false;
                    break;
                }
    
                case exit:{ // exit program
                    runProg = false;
                    runProgMember = false;
                    break;
    
                default: // wrong number input
                    cout << "\n\t\t\t\tNo such choice, choose again!";
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

        // admin log in feature
        for (int uattempts = 0; uattempts < MAX_LOGIN_ATTEMPTS && runProgAdmin == false; uattempts++){
            cout << "\n\t\t\t\tYou have " << 3 - uattempts << " username attempts." << endl;                 
            cout << "\n\t\t\t\tUsername: ";
            getline(cin, adminusername);  
                              
            if (adminusername.compare("sedtest") != 0){ //
                cout << "\n\t\t\t\tWrong admin username" << endl;
                continue;
            }
            else{
                cout << "\n\t\t\t\tCorrect username" << endl;
                for (int pattempts = 0; pattempts < MAX_LOGIN_ATTEMPTS && runProgAdmin == false; pattempts++){
                    
                    cout << "\n\t\t\t\tYou have " << 3 - pattempts << " password attempts." << endl;
                    cout << "\n\t\t\t\tPassword: ";
                    getline(cin, adminpassword); 

                    if (adminpassword.compare("HD100") == 0){                        
                        cout << "\n\t\t\t\tCorrect password!\n";
                        runProgAdmin = true;                                                                      
                    }
                }
                //admin right, pw wrong
                break; 
            }                  
        }      
        if(runProgAdmin == false){ // too many fail, exit for security
            cout << "\n\t\t\t\tToo many fail attempts. Exit program";
            runProg = false;
        }   

        // admin verified    
        while (runProgAdmin){ // inner loop for admin
            
            AdminScreen();
            int adminmode = inputNumber("your choice", exit);                        

            switch (adminmode){
                case view_all_houses:{ // view all houses on the record
                    system.viewHouses(admin);
                    BackorExit(runProg, runProgAdmin, 1, 2, 3);
                    break;
                }

                case view_all_members:{ // view all members on the record
                    system.viewAllMembers();
                    BackorExit(runProg, runProgAdmin, 1, 2, 3);
                    break;
                }

                case back:{ // go back to main meu
                    runProg = true;
                    runProgAdmin = false;
                    break;
                }

                case exit:{ // exit program
                    runProg = false;
                    runProgAdmin = false;
                    break;
                }
                default: // wrong number input
                    cout << "\n\t\t\t\tNo such choice, choose again!";
                    runProgAdmin = true;                   
            }        
        }        
        break;
    }
    default: // wrong number input
        cout << "\n\t\t\t\tNo such choice, choose again!";
        runProg = true;        
    }    
    }

    /* 
    WRITE DATA INTO FILE
    */
    system.exportMember();
    system.exportHouse();
    system.exportRequest();        
}

/*
USER INPUT VALIDATION FUNCTIONS
*/
bool isDigit(string str){ // check if a string is all digits   
    if (str.size() > 10){return false;}
    for (char c : str){
        if (!isdigit(c)){return false;}
    }  
    return true; 
}

int inputNumber(string prompt){ // validate numeric input (no white space, mixed data type)
    cout << "\n\t\t\t\tPlease enter " << prompt << " : ";
    string temp; 
    getline(cin, temp);
    while (temp.size() == 0 || !isDigit(temp)){
        cout << "\n\t\t\t\tInvalid input, please enter again: ";
        getline(cin, temp);              
    }
    int num = stoi(temp);
    return num;
}

int inputNumber(string str, int maxsize){ // validate number with an upper bound
    int temp = inputNumber(str);
    while(temp <0 || temp>maxsize) {
        temp = inputNumber(str + " less than " + to_string(maxsize+1));
    }
    return temp;
}

double inputRating(){ // validate rating input (double)
    double num;
    int minus_count = 0;    
    int decimal_count = 0;    
    bool isDouble = false;
    string temp;    

    while (!isDouble){ 
        cout << "\n\t\t\t\tEnter rating from -10 to 10: " ;
        getline(cin, temp);
        while (temp.size() == 0){
            cout << "\n\t\t\t\tInput empty, enter again: ";
            getline(cin, temp);
        }
        minus_count = 0;    
        decimal_count = 0;
        isDouble = true;
        for (char c : temp){
            if (c == '-'){minus_count++;} 
            if (c == '.'){decimal_count++;}
            if (minus_count > 1 || decimal_count>1){ // if number has more than 1 '-' or '.'               
                isDouble = false; // not double           
                break; // break for loop
            }           
        } 
        if (!(minus_count == 0 || (minus_count == 1 && temp[0] == '-')) // '-' in the wrong place (not 1st element)
                && (decimal_count == 0 || decimal_count == 1) ) {                  
            isDouble = false;             
        }
        else {
            string temp_no_sign = temp; // convert number to string to check if all digits           
            if (minus_count == 1){
                temp_no_sign.erase(0, 1); // if negative, erase the '-' sign               
            }
            if (decimal_count == 1){ // if decimal, ersae the '.' sign
                temp_no_sign.erase(temp_no_sign.find('.'),1);                
            }
            if (!isDigit(temp_no_sign)){ // once erased, if all not digit               
                isDouble = false; // not double       
            }
            if (isDouble == true) {
                num = stod(temp); // convert string to double                
                if (-10 <= num && num <= 10){ // number has to be -10 < num < 10                   
                    return num;
                }
                else{isDouble = false;} // else, out of range
            }            
        }        
    }
    return num;
}

string inputPhone(){ // validate phone number inputted
    cout << "\n\t\t\t\tEnter phone (10 digits): " ;
    string temp; 
    getline(cin, temp);
    while (!isDigit(temp) || temp.size() != 10){
        cout << "\n\t\t\t\tInvalid phone number, please enter again: ";
        getline(cin, temp);              
    }    
    return temp;    
}

string inputString(string prompt){ // validate no-white-space string
    cout << "\n\t\t\t\tPlease enter " << prompt << ": ";
    string str; 
    bool hasSpace = false;
    getline(cin, str);
    while (str.size() == 0){ // check empty string
        cout << "\n\t\t\t\t" << prompt << " cannot be empty\n";
        getline(cin, str);
    }
    for (char c : str){ // check for white space
        if (isspace(c)){hasSpace = true;}
    }
    while (hasSpace){
        cout << "\n\t\t\t\tInvalid string, please enter again (no space): ";
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
        cout << "\t\t\t\tVACATION HOUSE EXCHANGE APPLICATION \n";        
        cout << "\t\t\t\tGroup: 3 - Group Name: KEY GEN C\n";
        cout << "\t\t\t\ts3872105, Nguyen Ngoc Thang\n";
        cout << "\t\t\t\ts3926751, Pham Quang Huy\n";
        cout << "\t\t\t\ts3926937, Nguyen Mau Bach\n\n";
        cout << "\t\t\t\tHello! You can choose to use the app as: 1.Guest - 2.Member - 3.Admin \n";           
}

void GuessScreen(){ // display screen for guess
    cout << "\n\t\t\t\tYou are a guest. You can choose to:\n";    
    cout << "\t\t\t\t1. Register to become a member\n";
    cout << "\t\t\t\t2. View all houses (with limited visibility)\n";
    cout << "\t\t\t\t3. Go back to main menu\n";
    cout << "\t\t\t\t4. Exit the program\n";
    cout << "\t\t\t\tWhat would you like to do?\n";    
}

void MemberScreen(Member mem){ // display screen for member
    cout << "\n\t\t\t\tWelcome back, " << mem.getFullName() << endl; 
    cout << "\t\t\t\tYou can choose to:\n";       
    cout << "\t\t\t\t1. View your information\n";
    cout << "\t\t\t\t2. List your house available (with/without minimumm rating required)\n";    
    cout << "\t\t\t\t3. Search for a house\n";
    cout << "\t\t\t\t4. Request to occupy a house\n";
    cout << "\t\t\t\t5. View all requests to your listed house\n";
    cout << "\t\t\t\t6. Accept a request to your listed house\n";
    cout << "\t\t\t\t7. Go back to main menu\n";
    cout << "\t\t\t\t8. Exit the program\n";
    cout << "\t\t\t\tWhat would you like to do?\n";    
}

void AdminScreen(){   
    cout << "\n\t\t\t\tYou are am admin. You can choose to:\n";       
    cout << "\n\t\t\t\t1. View all houses (all information)\n";
    cout << "\t\t\t\t2. View all members (all information)\n";
    cout << "\t\t\t\t3. Go back to main menu\n";
    cout << "\t\t\t\t4. Exit the program\n";    
}

void BackorExit(bool& run_prog, bool& run_subprog, int prog, int subprog, int exit){ // function for going back to main menu or exit prog    
    cout << "\n\t\t\t\tPRESS "<< prog << " TO RETURN TO MAIN MENU\n";
    cout << "\t\t\t\tPRESS "<< subprog << " TO GO BACK \n";
    cout << "\t\t\t\tPRESS "<< exit << " TO EXIT \n";
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
        cout << "\n\t\t\t\tInvalid date, plese enter again: ";
        getline(cin, inp);         
    }     
    return inp;
}

string getDateInput(string& inp, string sstart){ // fucntion overload to validate that end day > start day
    Date start(sstart);    
    Date end(getDateInput(inp));
    while (start > end){        
        cout << "\n\t\t\t\tStart date cannot be later than end date: ";
        getline(cin, inp);
        end.updateDate(inp);         
    }         
    return inp;
}
    
    




