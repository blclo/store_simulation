#ifndef ORDER_HPP
#define ORDER_HPP

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>        // std::remove

using namespace std;

/**
 * @brief This class represents the purchase made by an User
 */

class Order
{
public:
    /** Parametric constructors */
    Order(unsigned long reference, vector<unsigned long> products, int deliveryAddress, float total);
    Order(unsigned long reference, int deliveryAddress, int payment_method);

    /** Getters */
    unsigned long getReference() const { return _reference; }
    const vector <unsigned long> & getProducts() const {return _products; }
    time_t getDate() {return _date;}
    int getDeliveryAddress() const { return _delivery_address; }
    int getPaymentMethod() const { return _payment_method; }
    float getTotal() const { return _total; }

    /** Getters */
    void setReference(unsigned long reference) { _reference = reference; }
    void addProduct(unsigned long reference){ _products.push_back(reference);}
    void setDeliveryAddress(int deliveryAddress) {_delivery_address = deliveryAddress; }
    void setPaymentMethod(int payment_method) { _payment_method = payment_method;}
    void setTotal(float total) { _total = total; }
    void setDate(const string & date);

    void write(ostream& os);

    /** sobrecarga de operadores */
    friend ostream & operator <<(ostream &os, const Order & O);

private:
    unsigned long _reference;
    vector <unsigned long> _products;
    time_t _date; //Hace falta inicializarlo en el consturctor y aqui?? O solo en el constructor?
    int _delivery_address; //el id de la direccion registrada por el usuario
    int _payment_method; //es el id del metodo de pago elegido por el usuario
    float _total;

    /** Empty constructor */
    Order();

};

#endif // ORDER_HPP
