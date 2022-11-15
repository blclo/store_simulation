#include "Review.hpp"

#include <iostream>
#include <ctime>
#include <string>
#include "PublicUserData.hpp"

using namespace std;

Review::Review()
{
    _id = 0;
    _date = time(0);
    _rating = 0;
    _text = "";
    _votes = 0;
    _author = nullptr;
}

Review::Review(unsigned long ID, int points, string text, PublicUserData* author)
{
    _id = ID;
    _date = time(0);
    _rating = points;
    _text = text;
    _votes = 0;
    _author = author;
}

string Review::show(){

    string a = "\t" + to_string(_rating) + " stars on the date " + asctime(localtime(&_date)) + " by " + _author->getUsername() + "\n";
    string b = "\t" + _text + "\n";
    string c = "\t" + to_string(_votes) + " votes\n";

    string review= a+b+c;
    return review;
}


ostream & operator <<(ostream &os, const Review & R)
{
   os << "\tReview ID: " << R._id << " - date: " << R._date << endl;
   os << "\tRating: " << R._rating << " - text:" << R._text << endl;
   os << "\tVotes: " << R._votes << endl;

   return os;
}

void Review::write (ostream & os)
{
    os << "Review:" << endl;
    os << _id << endl;
    os << _date << endl;
    os << _rating << endl;
    os << _text << endl;
    os << _votes << endl;
    os << _author->getUsername() << endl;
}

void Review::setDate(const string &date)
{
    double aux;
    aux = stod(date);
    _date = (time_t)aux;
}

void Review::setVotes(int votes){
    for (int i = 0 ; i < votes; i++){
        incrementVotes();
    }
}
