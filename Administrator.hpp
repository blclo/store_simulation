#ifndef ADMINISTRATOR_HPP
#define ADMINISTRATOR_HPP

#include <iostream>
#include "User.hpp"

/**
 * @brief This class is an administrator which is a type of User
 */

/** It is also a worker thus it gets a 7.5% discount on each purchase.
    Administrators are the only ones that can add products for
    costumer to buy them
*/

class Administrator : public User {
public:
    /** Parametrized constructor */
    Administrator(const string & username, const string & email, const string & password, unsigned long employeeCode) : User(username, email, password)
    {
        _employee_code = employeeCode;
    }

    /** Method indicating if the user is an admin  */
    bool isAdmin() { return true; }

    /** Getter */
    unsigned long getEmployeeCode() const { return _employee_code; }

    void clear();
    void write(ostream &os);
    bool read(istream &is);

private:
    unsigned long _employee_code;

    /** Empty constructor */
    Administrator();
};

#endif // ADMINISTRATOR_HPP
