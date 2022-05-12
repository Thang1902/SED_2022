#include <iostream>
#include <vector>
#include <string>
#include "Member.cpp"
#include "House.cpp"
#include "Date.cpp"
#include "Review.cpp"

using namespace std;

class System{
public:
    vector <Member*> member_list;
    vector <House*> house_list;
    vector <House*> suitable_house_list;
    System(){};
};  

House* getHouseToList(Member* owner_list, Date start, Date end, int consum_point, double minrate){
    owner_list->getHouse()->setAvailability(start, end);    
    owner_list->getHouse()->setConsumingPoint(consum_point);
    owner_list->getHouse()->setMinRate(minrate);
    return owner_list->getHouse();    
}

House* getHouseToListNoRating(Member* owner_list, Date start, Date end, int consum_point){
    owner_list->getHouse()->setAvailability(start, end);    
    owner_list->getHouse()->setConsumingPoint(consum_point);    
    return owner_list->getHouse();    
}

bool isSuitableHouse(House* cmphouse, Date start, Date end, string city, double rate, int points){    
    // cout << "start date of house:" <<cmphouse->start_avai.viewDate() << endl;
    // cout << "end date of house:" <<cmphouse->end_avai.viewDate() << endl;
    // cout << "start required: " << start.viewDate() << endl;
    // cout << "end required: " << end.viewDate() << endl;
    // cout << "city: " << cmphouse->location << endl;
    // cout << "city required: " << city << endl;
    // cout << "After comparison: "  << end.biggerDate(cmphouse->end_avai).viewDate();
    if (cmphouse->start_avai > start){       
        if (end > cmphouse->end_avai){                            
            if (city == cmphouse->location){                
                if (rate >= cmphouse->min_rate){
                    if (points > (stoi(end.getDay()) - stoi(start.getDay())) * cmphouse->consuming_point){
                        return true;
                    }
                }
            }
        }
    }    
    return false;    
}

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

    Member m1("thang", "0000");
    Member m2("ewrr", "eer");
    Member m3("ewrr", "eer");
    Member m4("ewrr", "eer");
        
    
    House h1("HCM", "A house");
    House h2("HCM", "aparment");
    House h3("HCM", "villa");
    House h4("HCM", "big house");

    m1.setHouse(&h1);
    h1.setOwner(&m1);

    m2.setHouse(&h2);
    h2.setOwner(&m2);

    m3.setHouse(&h3);
    h3.setOwner(&m3);

    m4.setHouse(&h4);
    h4.setOwner(&m4);   

    // check.member_list.push_back(&m1);

    // for (Member* mem : check.member_list){
    //     mem->viewInfo();
    //     mem->getHouse()->viewInfoHouse();
    // }

    // check.house_list.push_back(&h1);   

    // m2.rateOccupier(&m1, 3.4);
    // m2.rateOccupier(&m1, 7.2);
    // m2.rateOccupier(&m1, 4.7);
    // m2.rateOccupier(&m1, 3.4);
    // m2.rateOccupier(&m1, 7.2);
    // m2.rateOccupier(&m1, 4.2);
    // m2.rateOccupier(&m1, 9.4);
    // m2.rateOccupier(&m1, 2.2);
    // m2.rateOccupier(&m1, 5.7);

    // OCCUPIER RATING 
    // cout << "The rating of " << m1.getFullName() << " is: " << m1.cal_occupier_rate();

    Date def("010100");
    Date d1("120522");
    Date d2("170522");
    Date d3("220622");
    Date d4("280622");
    Date d5("130522");
    int cpoint = 200;
    int cpoint2 = 300;
    double minr = 5.5;
    double minr2 = 6.5;

    Date test1("100522");
    Date test2("180522");

    // add house to list
    check.house_list.push_back(getHouseToList(&m1, d1, d2, cpoint, minr));
    check.house_list.push_back(getHouseToList(&m2, d3, d4, cpoint2, minr2));
    check.house_list.push_back(getHouseToList(&m3, d5, d2, cpoint, minr));
    check.house_list.push_back(getHouseToList(&m4, d3, d4, cpoint2, minr2));

    // print list
    cout << "List of all houses:\n";
    for (House* h : check.house_list){
        cout << "--------------\n";
        h->viewInfoHouse();  
        cout << "--------------\n";     
    }
    
    // unlist
    // h2.setAvailability(def, def);
    // h2.setConsumingPoint(0);    
    // h2.setMinRate(0.0);
    // check.house_list.pop_back();
    // 


    // check available houses
    for (House* h:check.house_list){
        if (isSuitableHouse(h, test1, test2, "HCM", 6, 120000)){
            check.suitable_house_list.push_back(h);
        }
    }

    cout << "Available houses:\n";
    for (House* h : check.suitable_house_list){
        cout << "--------------\n";
        h->viewInfoHouse();  
        cout << "--------------\n";
    }

    // Review r1("nice", 6.7);
    // r1.showReview();


    
}
    
    




