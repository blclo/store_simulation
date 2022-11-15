////////////////////////////////////////////////////
/// User header file
////////////////////////////////////////////////////

#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <string>
#include "PrivateUserData.hpp"
#include "PublicUserData.hpp"

using namespace std;

/**
 * @brief This class represents an user, whom inherits data from
 * PrivateUserData and PublicUserData
 */
class User : public PrivateUserData, public PublicUserData {
public:
    /** Parametrized constructor */
    User(const string & username, const string & email, const string & password) : PrivateUserData(email, password), PublicUserData(username) {}
    ~User(){}

    /** Method to check if the user is an admin */
    virtual bool isAdmin();

    virtual void write(ostream &os);
    virtual void clear();

    friend ostream & operator <<(ostream &os, const User & U);

protected:
    /** Empty constructor */
    User() : PrivateUserData(), PublicUserData() {}
};

#endif // USER_HPP
