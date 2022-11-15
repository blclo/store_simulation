#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include "Manager.hpp"
#include <unistd.h>
using namespace std;

/** global variables */


void checkCIN();

class Interface
{
public:

    Interface();

    /** INITIAL MENU : if first time ? addAdministrator : login or register  */
    void InitialMenu();

    /** PRINCIPAL MENU */
    void MainMenu();
    void editProfileOptions(int n);

    void orderActionsOptions(int n);
    void reviewActionsOptions(int n);

    /** ADMIN MENU */
    void AdminMenu();

    void showproducts();
    void showreviews();
    void showAdresses();
    void showPaymentMethods();
    void showUsers();


    /** ******** MEJORAS: *********/

    string formatLocalTime(const time_t& date);

    void showReviewOrdered(const User& U);


//protected:
    /** Create manager */
        Manager manager;

};

#endif // INTERFACE_HPP
