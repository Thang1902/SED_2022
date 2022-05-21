#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Review{
private:
    string comment;
    double rating_score;
public:
    Review();
    Review(string comment, double rating_score);
    void showReview();
};