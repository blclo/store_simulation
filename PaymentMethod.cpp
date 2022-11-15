#include "PaymentMethod.hpp"

#include <iostream>
#include "Address.hpp"

using namespace std;

PaymentMethod::PaymentMethod()
{
    _id = 0;
    _billing_address = nullptr;
}

PaymentMethod::PaymentMethod(int id, Address* billingAddress)
{
    _id = id;
    _billing_address = billingAddress;
}


