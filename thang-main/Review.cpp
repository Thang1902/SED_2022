#include <iostream>
#include <vector>
#include <string>
#include "Review.h"

using namespace std;

Review::Review(string comment, double rating_score){
    this->comment = comment;
    this->rating_score = rating_score;
}

void Review::showReview(){
    cout << "The score for this house is: " << this->rating_score << endl;
    cout << "Review for this house is: " << this->comment << endl;
    
}
