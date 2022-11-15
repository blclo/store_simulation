#include "Product.hpp"
#include <iostream>

using namespace std;

Product::Product(string name, string description, unsigned long reference, float price) {
    _name = name;
    _description = description;
    _reference = reference;
    _price = price;
}

Product::~Product()
{
    for (int j = 0; j < (int)_reviews.size(); j++) {
        delete _reviews[j];
    }
}

const string & Product::getName() const
{
    return _name;
}

const string & Product::getDescription() const {
    return _description;
}

unsigned long Product::getReference() const {
    return _reference;
}

float Product::getPrice() const
{
    return _price;
}

void Product::setName(const string& name)
{
    _name = name;
}

void Product::setDescription(string description)
{
    _description = description;
}

void Product::setReference(unsigned long reference)
{
    _reference = reference;
}

void Product::setPrice(float price)
{
    _price = price;
}

void Product::addReview(Review *review)
{
       _reviews.push_back(review);
}

/** No es utilizado pero sería un posible método para elimar el review */
void Product::deleteReview(unsigned long id)
{
    vector<Review*> copy;
    int j = -1;
    for (int i = 0 ; i < (int)_reviews.size() - 1 ; i++)
    {
        j++;
        if (_reviews[j]->getId() == id)
        {
            j++;
        }
        copy[i] = _reviews[j];
    }
    _reviews.clear();
    _reviews = copy;
}

ostream & operator <<(ostream &os, const Product & P)
{
   os << P._reference << " - " << P._name << endl;
   os << P._description << endl;
   os << P._price << endl;
   for (int i = 0 ; i < (int)P._reviews.size() ; i++)
   {
       os << "\t" << P._reviews[i] << endl;
   }
   return os;
}

void Product::write(ostream & os)
{
    os << "Product:" << endl;
    os << _name << endl;
    os << _description << endl;
    os << _reference << endl;
    os << _price << endl;

}

