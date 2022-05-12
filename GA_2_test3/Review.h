#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Member.h"
#include "House.h"

using namespace std;

class Member;
class House;

class Review{
protected:
    Member* occupier;
    House* house_to_rate;
    string comment;
    double rating_score;
public:
    Review();
    Review(string comment, double rating_score);

    void showReview();
};