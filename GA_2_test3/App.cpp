#include <iostream>
#include <string>
#include <limits>
#include "Member.cpp"

using namespace std;


void welcomeScreen(){ // display main menu 
        cout << "EEET2482/COSC2082 ASSIGNMENT \n";
        cout << "VACATION HOUSE EXCHANGE APPLICATION \n\n";
        cout << "Instructor: Mr. Linh Tran \n";
        cout << "Group: Group Name \n";
        cout << "s3872105, Nguyen Ngoc Thang \n";
        cout << "sXXXXXXX, Student Name \n";
        cout << "sXXXXXXX, Student Name \n\n";
        cout << "Use the app as 1. Guest   2. Member   3. Admin \n";
        cout << "Enter your choice: ";    
}

void GuessScreen(){ // display screen for guess
    cout << "You are a guest\n";    
    cout << "1. Register to become a member\n";
    cout << "2. View all houses (with limited visibility)\n";
    cout << "3. Go back to main menu\n";
    cout << "4. Exit the program\n";
    cout << "What would you like to do?\n";
    cout << "Enter your choice: ";
}

void MemberScreen(Member mem){ // display screen for member
    cout << "Welcome back, " << mem.getFullName() << endl;        
    cout << "1. View your information\n";
    cout << "2. List your house available (with minimumm rating required)\n";
    cout << "3. List your house available (no rating required)\n";
    cout << "4. Search for a house\n";
    cout << "5. Request to occupy a house\n";
    cout << "6. View all requests to your listed house\n";
    cout << "7. Accept a request to your listed house\n";
    cout << "8. Go back to main menu\n";
    cout << "9. Exit the program\n";
    cout << "What would you like to do?\n";
    cout << "Enter your choice: ";
}

void BackorExit(bool& run_prog, bool& run_subprog, int prog, int subprog, int exit){ // function for going back to main menu or exit prog
    int temp;   
    cout << "PRESS "<< prog << " TO RETURN TO MAIN MENU\n";
    cout << "PRESS "<< subprog << " TO GO BACK \n";
    cout << "PRESS "<< exit << " TO EXIT \n";
    cin >> temp;
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
    
