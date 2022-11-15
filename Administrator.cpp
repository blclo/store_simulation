#include "Administrator.hpp"

Administrator::Administrator()
{
    _username = " ";
    _email = " ";
    _password = " ";
    _employee_code = 0;
}

void Administrator::clear()
{
    _username = " ";
    _email = " ";
    _password = " ";
    _employee_code = 0;
}

void Administrator::write(ostream &os)
{
    os << "User:" << endl;
    os << _username << endl;
    os << _email << endl;
    os << _password << endl;
    os << _reputation << endl;
    os << _employee_code <<endl;
}

