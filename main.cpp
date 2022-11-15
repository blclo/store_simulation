#include <iostream>
#include "Manager.hpp"
#include "Interface.hpp"


using namespace std;

int main() {

   Interface interface;
    Manager Many;
    cout << " ********** Welcome to LSimpson S.L.! ********** " << endl;

    interface.InitialMenu();
    return 0;
}
