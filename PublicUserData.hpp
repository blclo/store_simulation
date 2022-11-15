#ifndef PUBLICUSERDATA_H
#define PUBLICUSERDATA_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief This class represents the public data of the user
 */
class PublicUserData {
public:
    /** Parametrized constructor */
    PublicUserData(const string & username);
    virtual ~PublicUserData(){}

    /** getters */
    const string & getUsername() const { return _username; }
    int getReputation() const { return _reputation; }
    
    /** methods */
    void increaseReputation();
    void decreaseReputation();
    void setReputation(int reputation);

    /** setters */
    void setUsername(const string & username) { _username = username; }

protected:
    string _username;
    int _reputation;

    /** Empty constructor */
    PublicUserData();
};

#endif // PUBLICUSERDATA_H
