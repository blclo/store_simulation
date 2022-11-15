#include "Paypal.hpp"

#include <iostream>
#include "Address.hpp"
#include "PaymentMethod.hpp"

using namespace std;

Paypal::Paypal()
{
    _email = "";
}

string Paypal::show()
{
    string a = "\tid "+to_string(_id)+" - Paypal Account:\n";
    string b = "\tBilling address: "+_billing_address->show()+"\n";
    string c = "\t"+_email+"\n";

    string Info=a+b+c;
    return Info;
}

void Paypal::write(ostream& os)
{
    os << "Paypal:" << endl;
    os << _id << endl;
    os << _billing_address->getId() << endl;
    os << _email << endl;
}

