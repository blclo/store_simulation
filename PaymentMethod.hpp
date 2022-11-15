#ifndef PAYMENTMETHOD_HPP
#define PAYMENTMETHOD_HPP

#include <iostream>
#include "Address.hpp"

using namespace std;

/**
 * @brief This is an abstract base class representing a general payment method
 *        there are two types of methods by Credit Card or by Paypal
 */

class PaymentMethod
{
public:
    /** Parametrized constructor */
    PaymentMethod(int id, Address* billingAddress);
    virtual ~PaymentMethod() {}
    virtual string show() = 0;
    virtual void write(ostream& os) = 0;

    /** setters */
    void setId(int id) { _id = id; }
    void setBillingAddress(Address* billingAddress) { _billing_address = billingAddress; }

    /** Getters  */
    int getId() const { return _id; }
    Address* getBillingAddress() const { return _billing_address; }

protected:
    int _id; // number of payment methods the user has
    Address* _billing_address;

    /** Empty constructor */
    PaymentMethod();
};

#endif // PAYMENTMETHOD_HPP
