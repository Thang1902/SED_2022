#pragma once
     
using namespace std;

class Member;
class Date;
class Request;

class House{
private:
    int house_ID; // unique ID of this house obj
    int owner_ID; // ID of owner       
    string location;
    string description;
    int consuming_point;
    double min_rate; // minimum rating for occupier   
    double house_rate; // house rating (default 10)
    Date start_avai; // availability
    Date end_avai;                
public:
    // constructors
    House();    
    House(int id, string location, string description, Date start, Date end, int consum_point, double minrate); // for listing    
    House(int house_ID, int owner_ID, string location, string description, int consuming_point,
                double min_rate, double house_rate, Date start_avai, Date end_avai); // for file io    
    void setID(int id);

    // getters and setters
    void setID(); 
    int getID();
    int getOwnerID();   
    void setOwner(Member& add_owner);           
    Date getStartAvai(); 
    Date getEndAvai();       
    string getLocation(); 
    void setLocation(string location);
    string getDescription(); 
    void setDescription(string description);
    double getMinrate(); 
    void setMinRate(double rate);
    double getHouseRating();  
    int getConsumingP();
    void setConsumingPoint(int cpoint);

    // methods
    void setAvailability(Date st, Date e);
    void viewInfoHouse(Member owner);
    void viewInfoHouseGuest(Member owner);
    // check if a house is suitable
    bool isSuitableHouse(Member mem, Date start, Date end, string city, double rate, int points);
};
