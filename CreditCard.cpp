#include "CreditCard.hpp"

#include <iostream>
#include "Address.hpp"
#include "PaymentMethod.hpp"

using namespace std;

CreditCard::CreditCard(){
    _number  = 0;
    _cardholder = " ";
}

CreditCard::CreditCard( int id, Address* billingAddress, unsigned long number,
                        const string& cardholder): PaymentMethod(id, billingAddress){
   _number = number;
   _cardholder = cardholder;
}

string CreditCard::show(){
    string a = "\tid " + to_string(_id) + " - Credit Card:\n";
    string b = "\tBilling address: " + _billing_address->show() + "\n";
    string c = "\t" + to_string(_number) + " - " + _cardholder + "\n";

    string Info = a + b + c;
    return Info;
}

void CreditCard::write(ostream& os)
{
    os << "CreditCard:" << endl;
    os << _id << endl;
    os << _billing_address->getId() << endl;
    os << _number << endl;
    os << _cardholder << endl;
}
