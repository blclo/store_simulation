#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <iostream>
#include <vector>

#include "Review.hpp"

using namespace std;

/**
 * @brief This class represents a product that is being sold on the platform
 */

class Product
{
public:
    /** Parametrized constructor */
    Product(string name, string description, unsigned long reference, float price);
    ~Product();

    /** getters */
    const string & getName() const;
    const string & getDescription() const;
    unsigned long getReference() const;
    float getPrice() const;

    /** setters */
    void setName(const string & name);
    void setDescription(string description);
    void setReference(unsigned long reference);
    void setPrice(float price);

    vector<Review*> & getReviews() { return _reviews; }
    void addReview(Review *review);
    void deleteReview(unsigned long id);

    /** sobrecarga de operadores */
    friend ostream & operator <<(ostream &os, const Product & P);

    void write(ostream & os);

private:
    string _name; // name or short desciption of the product
    string _description; // long description of the product
    unsigned long _reference; // unique reference for the product
    float _price; // price of the product
    vector<Review*> _reviews;

    /** Empty constructor */
    Product();
};

#endif // PRODUCT_HPP
