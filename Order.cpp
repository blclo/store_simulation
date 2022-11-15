#include "Order.hpp"

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>        // std::remove

using namespace std;

Order::Order()
{
    _reference = 0;
    _products = vector<unsigned long>();
    _date = time(0);
    _delivery_address = 0;
    _payment_method = 0;
    _total = 0;
}

Order::Order(unsigned long reference, vector<unsigned long>products, int deliveryAddress, float total)
{
    _date = time(0);
    _reference = reference;
    for(int i=0; i<(int)products.size(); ++i)
    {
        _products.push_back(products[i]);
    }

    _delivery_address = deliveryAddress;
    _total = total;
}

Order::Order(unsigned long reference, int deliveryAddress, int payment_method)
{
    _date = time(0);
    _reference = reference;
    _delivery_address = deliveryAddress;
    _payment_method = payment_method;
}


ostream & operator <<(ostream &os, const Order & O)
{
   os << "* Order reference: *" << O._reference << " - delivery address id: " << O._delivery_address << endl;
   os << "Payment method id: " << O._payment_method << endl;
   os << "Date : " << O._date << endl;
   os << "Total price: " << O._total << endl;
   if (O.getProducts().size() != 0)
   {
        os << "Reference of the products included in this order: " << endl;
        for (int i = 0 ; i < (int)O.getProducts().size() ; i++ )
        {
            os << O.getProducts()[i] << endl;
        }
   }
   return os;
}

void Order::write( ostream& os)
{
    os << "Order:" << endl;
    os << _reference << endl;
    for(int i=0; i< (int)_products.size(); ++i)
    {
        os << "order_product:" << endl;
        os << _products[i] << endl;
    }
    os << _date << endl;
    os << _delivery_address << endl;
    os << _payment_method << endl;
    os << _total << endl;
}

void Order::setDate(const string &date)
{
    double aux;
    aux = stod(date);
    _date = (time_t)aux;
}
