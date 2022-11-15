#include "PublicUserData.hpp"
#include <iostream>

using namespace std;

/** Empty constructor */
PublicUserData::PublicUserData()
{
    _username = " ";
    _reputation = 0;
}

/** Parametrized constructor */
PublicUserData::PublicUserData(const string & username)
{
    _username = username;
    _reputation = 0;
}

/** Increase the reputation */
void PublicUserData::increaseReputation()
{
    ++_reputation;
}


/** Decrease the reputation */
void PublicUserData::decreaseReputation()
{
    if (_reputation > 0)
    {
        --_reputation;
    }
    else
    {
        cout << "La reputacion del usuario es nula" << endl;
    }
}

void PublicUserData::setReputation(int reputation) {
    for (int i = 0; i < reputation; i++) {
        increaseReputation();
    }     
}
