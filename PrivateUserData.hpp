#ifndef PRIVATEUSERDATA_HPP
#define PRIVATEUSERDATA_HPP

#include <iostream>
#include <string>
#include <vector>

#include "Address.hpp"
#include "PaymentMethod.hpp"
#include "Order.hpp"

using namespace std;

/**
 * @brief This class represents the private data of the user
 */
class PrivateUserData {
public:
    /** Parametrized constructor */
    PrivateUserData(string email, string password);
    virtual ~PrivateUserData();

    /** Getters */
    const string & getEmail() const { return _email; }
    const string & getPassword() const { return _password; }
    vector<Address*> getAddresses() const { return _addresses; }
    vector<PaymentMethod*> getPaymentMethods() const { return _payment_methods; }
    vector<Order*> getOrders() const { return _orders; }
    vector<unsigned long> getVotesHistory() const {return _votes_history;}

    /** Setters */
    void setEmail(const string & email) { _email = email; }
    void setPassword(const string & password) { _password = password; }
    void addVoteHistory (unsigned long review_id) { _votes_history.push_back( review_id);}
    
    /** Methods */
    void addAddress(Address * A);
    void addPaymentMethod(PaymentMethod * P);
    void addOrder(Order * O);

protected:
    string _email;
    string _password;
    vector<Address*> _addresses;
    vector<PaymentMethod*> _payment_methods;
    vector<Order*> _orders;
    vector <unsigned long> _votes_history;

    /** Empty constructor */
    PrivateUserData();
};

#endif // PRIVATEUSERDATA_HPP
