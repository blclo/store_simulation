#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief This class represents the address where the products
 * will be sent to for each user
 */

class Address{
public:
    /** Parametrized constructor */
    Address(int id, const string & address, const string & city, const string & province, unsigned int postalCode);

    /** Getters */
    int getId() const { return _id; }
    const string & getAddress() const { return _address; }
    const string & getCity() const { return _city; }
    const string & getProvince() const { return _province; }
    unsigned int getPostalCode() const { return _postal_code; }

    /** Setters */
    void setId(int id) { _id = id; }
    void setAddress(const string & address) { _address = address; }
    void setCity(const string & city) { _city = city; }
    void setProvince(const string & province) { _province = province; }
    void setPostalCode(unsigned int postalCode) { _postal_code = postalCode; }

    /** Method that provides the Address info */
    string show() const;

    /** Overloaded operator << */
    friend ostream & operator <<(ostream &os, const Address & A);

    /** File functions */
    void write(ostream& os);
    bool read(istream & is);

private:
    /** Attributes */
    int _id;
    string _address;
    string _city;
    string _province;
    unsigned int _postal_code;

    /** Empty constructor */
    Address();
};

#endif // ADDRESS_HPP
