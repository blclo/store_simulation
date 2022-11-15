#include "User.hpp"
#include "Administrator.hpp"

bool User::isAdmin()
{
    return false;
}

ostream & operator <<(ostream &os, const User & U)
{
   os << "Username: " << U._username << " - Email: " << U._email << endl;
   os << "Reputation: " << U._reputation << " - Number of orders: " << U.getOrders().size() << endl;
   os << "Number of payment methods: " << U.getPaymentMethods().size() << "\tNumber of address: " <<  U.getAddresses().size() << endl;

   if ((int)U.getOrders().size() != 0) {
       os << "***** ORDERS *****" << endl;
       for (int j = 0 ; j < (int)U.getOrders().size() ; j++)
       {
           cout << *U.getOrders()[j]; // deberia funcionar si sobre cargo << en order
       }
   }

   if ((int)U.getPaymentMethods().size() != 0) {
       os << "***** PAYMENT METHODS *****" << endl;
       for (int i = 0 ; i < (int)U.getPaymentMethods().size(); i++)
       {
           cout << U.getPaymentMethods()[i]->show();
       }
   }

   if ((int)U.getAddresses().size() != 0) {
       os << "***** ADDRESSES *****" << endl;
       for (int j = 0 ; j < (int)U.getAddresses().size() ; j++)
       {
           cout << *U.getAddresses()[j]; // deberia funcionar si sobre cargo << en order
       }
   }

   return os;
}


void User::clear()
{
    _username = " ";
    _reputation = 0;
    _email = " ";
    _password = " ";
    _addresses = vector<Address*>();
    _payment_methods = vector<PaymentMethod*>();
    _orders = vector<Order*>();
    _votes_history = vector<unsigned long>();
}

void User::write(ostream &os)
{
    os << "User:" << endl;
    os << _username << endl;
    os << _email << endl;
    os << _password << endl;
    os << _reputation << endl;
    os << "-1" << endl;
}
