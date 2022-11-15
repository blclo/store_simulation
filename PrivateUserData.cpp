#include "PrivateUserData.hpp"
#include "Review.hpp"

PrivateUserData::PrivateUserData()
{
    _email = " ";
    _password = " ";
    _addresses = vector<Address*>();
    _payment_methods = vector<PaymentMethod*>();
    _orders = vector<Order*>();
    _votes_history = vector<unsigned long>();
}

PrivateUserData::~PrivateUserData()
{
    for (int j = 0; j < (int)_addresses.size(); j++) {
        delete _addresses[j];
    }
    for (int j = 0; j < (int)_payment_methods.size(); j++) {
        delete _payment_methods[j];
    }
    for (int j = 0; j < (int)_orders.size(); j++) {
        delete _orders[j];
    }
}

PrivateUserData::PrivateUserData(string email, string password)
{
    _email = email;
    _password = password;
}


void PrivateUserData::addAddress(Address * A) { // añade un puntero a address
    _addresses.push_back(A);
}

void PrivateUserData::addPaymentMethod(PaymentMethod * P)
{
    _payment_methods.push_back(P);
}

void PrivateUserData::addOrder(Order * O) {
    _orders.push_back(O);
}


