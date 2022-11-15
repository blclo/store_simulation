#ifndef PAYPAL_HPP
#define PAYPAL_HPP

#include <iostream>
#include "Address.hpp"
#include "PaymentMethod.hpp"

using namespace std;

/**
 * @brief This class defines the Payment Method carried out through Paypal
 */

class Paypal: public PaymentMethod
{
public:
    /** Parametrized constructor */
    Paypal(int id, Address* billingAddress, const string & email): PaymentMethod(id, billingAddress){ _email = email;}

    /** Method to display the Paypal Info */
    string show();
    void write(ostream& os);

    /** Setter and Getter */
    void setEmail(const string & email) { _email = email; }
    const string & getEmail() const { return _email;}

private:
    string _email;

    /** Empty Constructor */
    Paypal();    
};

#endif // PAYPAL_HPP
