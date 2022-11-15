#include "Address.hpp"

Address::Address(int id, const string & address, const string & city, const string & province, unsigned int postalCode)
{
    _id = id;
    _address = address;
    _city = city;
    _province = province;
    _postal_code = postalCode;
}

Address::Address()
{
    _id = 0;
    _address = " ";
    _city = " ";
    _province = " ";
    _postal_code = 0;
}

string Address::show() const {

    string direction = _address + ", " + _city + ", " + _province + ", " + to_string(_postal_code) ;
    return direction;
}

ostream & operator <<(ostream &os, const Address & A)
{
   os << "\tAddress ID: " << A._id << " - address: " << A._address << endl;
   os << "\tcity: "<< A._city << " - province: " << A._province << " - postal code: " << A._postal_code << endl;

   return os;
}


void Address::write(ostream &os)
{
    os << "Address:" <<endl;
    os << _id << endl;
    os<< _address <<endl;
    os<< _city <<endl;
    os<< _province <<endl;
    os<< _postal_code <<endl;
}