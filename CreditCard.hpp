#ifndef CREDITCARD_HPP
#define CREDITCARD_HPP

#include <iostream>
#include "Address.hpp"
#include "PaymentMethod.hpp"

using namespace std;

/**
 * @brief This class represents a CreditCard which is a derived class of PaymentMethod
 */

class CreditCard: public PaymentMethod{
public:
    /** Parametrized constructor */
    CreditCard( int id, Address* billingAddress , unsigned long number , const string & cardholder);


    /** Method that displays the credit card info for the current user*/
    string show();
    void write(ostream& os);


    /** Setters */
    void setNumber(unsigned long number) { _number = number; }
    unsigned long getNumber() const { return _number; }

    /** Getters */
    void setCardholder(string holder) { _cardholder = holder; }
    const string & getCardholder() const { return _cardholder; }

private:
    unsigned long _number;
    string _cardholder;

    CreditCard();

};
#endif // CREDITCARD_HPP
