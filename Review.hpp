#ifndef REVIEW_HPP
#define REVIEW_HPP

#include <iostream>
#include <ctime>
#include "PublicUserData.hpp"

using namespace std;

/**
 * @brief This class represents the Reviews that users make on a certain product
 */

class Review
{
public:

    /** Parametrized constructor */
    Review(unsigned long ID, int points, string text, PublicUserData* author);

    /** Getters */
    unsigned long getId() const {return _id;}
    time_t getTime() const {return _date;}
    time_t getDate() const {return _date;}
    int getRating() const { return _rating; }
    const string & getText() const { return _text; }
    int getVotes(){ return _votes; }
    PublicUserData* getAuthor() const { return _author; }
    void setDate(const string & date);

    /** Setters */
    void setRating(int rating) { _rating = rating; }
    void setText(string text) { _text = text; }

    void incrementVotes(){ ++_votes; }
    void decrementVotes(){ --_votes; }
    void setVotes(int votes);

    /** sobrecarga de operadores */
    friend ostream & operator <<(ostream &os, const Review & R);

    string show();

    void write (ostream & os);

private:
    unsigned long _id; // id for each review
    time_t _date; // date the review was created
    int _rating; // mark from 0 to 5 starts, for the review
    string _text;
    int _votes;
    PublicUserData* _author; // public information of the author that created the review

    Review();

};

#endif // REVIEW_HPP
