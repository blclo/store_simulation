#include "Interface.hpp"
#include <stdlib.h>
#include <time.h>

/** MEJORA: Función delay para hacer que el programa espere. */
void delay(int secs) {
  for(int i = (time(NULL) + secs); time(NULL) != i; time(NULL));
}

Interface::Interface()
{

}


/** INITIAL MENU */
void Interface::InitialMenu() {

    /** Local variables */
    int answerInitialMenu;
    string answerSaveFile;
    string username;
    string email;
    string password;
    unsigned long employeeCode;
    string semployeeCode;
    string initialAnswer;
    int code;
    string filename = "Database.txt";

     /** check if users already exist */
    if (manager.getUsers() != vector<User*>())
    {
        /** if they do - INITIAL MENU */
        cout << endl << "********* INITIAL MENU ********"<< endl;
        cout << "What do you want to do? Choose option 1 or 2. " << endl;
        cout << " - LOGIN (1)" << endl;
        cout << " - REGISTER (2)" << endl;
        cout << " - SAVE DATA TO FILE (3)" << endl;
        cout << " - LOAD DATA FROM FILE (4)" << endl;
        cout << " - EXIT (5)" << endl;


        cin >> answerInitialMenu;

        switch (answerInitialMenu) {
        case 1:
            cout << "***** LOGIN *****";
            cout << "Please enter your credentials:"<<endl;
            cout << "Email:\t";
            cin >> email;
            cout  << "Password:\t";
            cin >> password;
            if (manager.login(email, password))
            {
                /** SUCCESS - PRINCIPAL MENU */
                this->MainMenu();
            }
            else
            {
                /** FAIL - return to INITIAL MENU */
                Interface::InitialMenu();
            }
            break;

        case 2:
            cout << "***** REGISTER *****" << endl;
            cout << "Register. Please introduce an username:\t";
            cin >> username;
            cout << "Email:\t";
            cin >> email;
            cout << "Password:\t";
            cin >> password;
            cout << "If you want to register as an administrator, introduce an 'employee code', otherwise type -1" << endl;
            cin >> code;

            /** check whether we have an user or an admin */
            if( code == -1 )
            {
                /** add an user */
                if (manager.addUser(username, email, password))
                {
                    /** SUCCESS - log in the user directly */
                    manager.login(email, password);

                    /** MAIN MENU  */
                    this->MainMenu();
                }
                else
                {
                    /** FAIL - return to INITIAL MENU */
                    this->InitialMenu();
                }
            }
            else
            {
                /** add an administrator */
                employeeCode = (unsigned long) code;
                if (manager.addAdministrator(username, email, password, employeeCode))
                {
                    /** SUCCESS - log in the user directly */
                    manager.login(email, password);

                    /** MAIN MENU  */
                    this->MainMenu();

                } else {
                    /** FAIL - return to INITIAL MENU */
                    this->InitialMenu();
                }
            }
            break;
        case 3:
            cout << "The file route is " << filename << " by default. Do you want to change this? (y/n)" << endl;
            cin >> answerSaveFile;
            if( answerSaveFile == "y")
            {
                cout << "Introduce the new file route: " ;
                cin >> filename;
            }
            manager.saveToFile(filename);
            cout << "System data saved correctly "<< endl;
            break;
        case 4:
            cout << "The file route is " << filename << " by default. Do you want to change this? (y/n)" << endl;
            cin >> answerSaveFile;
            if( answerSaveFile == "y")
            {
                cout << "Introduce the new file route: " ;
                cin >> filename;
            }
            manager.loadFromFile(filename);
            cout << "System data loaded correctly "<< endl;

            break;
        case 5:
            cout << "Data has been saved automatically." << endl;
            manager.saveToFile(filename);
            delay(2);
            system("clear");
            cout << "See you next time! ";
            break;
        }
    }
    else
    {
        bool add = 1;
        string newName;
        string newDescription;
        unsigned long newReference;
        float newPrice;
        /** It is the first time the program is being run. Demand administrator creation. */
        cout << "Please before starting, add an administrator. \nEnter a new admin username:\t";
        cin >> username;
        cout << "Add an email:\t";
        cin >> email;
        cout << "Add a password:\t" ;
        cin >> password;
        cout << "Add an employee code (must be a numeric) and different than -1:\t" ;
        cin >> semployeeCode;

        for(int i = 0; i<(int) semployeeCode.size(); ++i)
        {
            if( !isdigit(semployeeCode[i]))
            {
                cout << "An employee code is only composed of digits, try again" << endl;
                cin >> semployeeCode;
                i = 0;
            }
        }

        employeeCode = stoul(semployeeCode);
        manager.addAdministrator(username, email, password, employeeCode);
        cout << "***************************************" << endl;



        manager.login(email, password); // Admin MUST be logged in orde to add new products
        // To keep it simple we will log them automatically in and out

        do {
            cout << "Please add a product - " << endl;
            cout << "Name: \t";
            cin.ignore();
            getline(cin,newName);
            cout << "Description: \t";
            getline(cin,newDescription);
            cout << "Reference (must be numeric): \t";
            cin >> newReference;
            cout << "Price: \t" ;
            cin >> newPrice;
            if(manager.addProduct(newName, newDescription, newReference, newPrice)){
                cout << "Product added correctly." << endl;
            }else{
              cout << "Admin must be logged in to add a product"<< endl;
            }
            cout << "Do you want to add another product? (yes = 1, no = 0)" << endl;
            cin >> add;
        } while (add == 1);

        cout << "The product/s have been added correctly." << endl;
        cout << "Thanks for adding product/s. We have logged you out as an Admin." << endl;
        manager.logout();

        delay(2);
        /** SUCCESS OR FAIL - INITIAL MENU */
        this->InitialMenu();
    }
    this->InitialMenu();
}


void Interface::MainMenu()
{
    int answerMainMenu;
    int answerOrderActions;
    int answerReviewActions;
    int answerEditProfile;
    string answerCancelSubscription;
    string answerLogOut;

    system("clear");
    cout<< endl << "********* MAIN MENU **********" << endl;
    cout << "Choose from the following options: " << endl;
    cout << " - EDIT PROFILE (1) " << endl;
    cout << " - ORDER ACTIONS (2) " << endl;
    cout << " - REVIEW ACTIONS (3) " << endl;
    cout << " - CANCEL SUBSCRIPTION (4) " << endl;
    cout << " - LOG OUT (5) " << endl;
    if(manager.getCurrentMember()->isAdmin())
    {
        cout << " - SEE MY ADMIN OPTIONS (6)" << endl;
    }
    cin >> answerMainMenu;

    switch(answerMainMenu){
        /** WORKS */
        case 1:
            system("clear");
            cout << "***** EDIT PROFILE - CHOOSE ACTION *****" << endl;
            cout << " - EDIT USERNAME (1) " << endl;
            cout << " - EDIT EMAIL (2) " << endl;
            cout << " - EDIT PASSWORD (3) " << endl;
            cout << " - ADD ADDRESS (4) " << endl;
            cout << " - ADD PAYMENT METHOD (5) " << endl;
            cout << " - RETURN (6)" << endl;

            cin >> answerEditProfile;
            editProfileOptions(answerEditProfile);
            break;

        case 2:
            system("clear");
            cout << " ***** ORDER ACTIONS - CHOOSE ACTION *****" << endl;
            cout << " - SEE MY PREVIOUS ORDERS (1) " << endl;
            cout << " - MAKE A NEW ORDER (2) " << endl;
            cout << " - RETURN (3)" << endl;

            cin >> answerOrderActions;
            orderActionsOptions(answerOrderActions);
            break;

        case 3:
            system("clear");
            cout << " ***** REVIEW ACTIONS - CHOOSE ACTION *****" << endl;
            cout << " - CREATE REVIEW (1) " << endl;
            cout << " - SEE REVIEWS OF SPECIFIED RATING (2) " << endl;
            cout << " - VOTE REVIEW (3) " << endl;
            cout << " - MODIFY REVIEW (4) " << endl;
            cout << " - DELETE REVIEW (5) " << endl;
            cout << " - RETURN (6) " << endl;

            cin >> answerReviewActions;
            reviewActionsOptions(answerReviewActions);
            break;

        case 4:
            system("clear");
            cout << " ***** CANCEL SUBSCRIPTION *****" << endl;
            cout << "Your subscription is about to get cancelled. Are you sure? (yes/no) " << endl;
            cin >> answerCancelSubscription;
            if (answerCancelSubscription == "yes")
            {
                /** cancel subscription */
                if (manager.eraseCurrentMember()){
                    cout << "Subscription was cancelled" << endl;
                } else {
                    cout << "Error. Could not cancel your subscription." << endl;
                }

            }
            else
            {
                this->MainMenu();
            }
            delay(2);
            break;

        case 5:
        {
            system("clear");
            cout << " ***** LOG OUT *****" << endl;
            cout << "You are about to log out. Are you sure? (yes/no) " << endl;
            cin >> answerLogOut;
            if (answerLogOut == "yes")
            {
                /** log out */
                manager.logout();
                this->InitialMenu();
            }
            else
            {
                this->MainMenu();
            }
            break;
        }

        case 6:
        {
            system("clear");
            if(manager.getCurrentMember()->isAdmin())
            {
                /** open admin menu */
                this->AdminMenu();
            } else
            {
                /** the user it's not an admin. can't access this menu */
                cout << "Invalid option. Please introduce a valid number." << endl;
                delay(2);
                break;
            }
        }
        default:
            cout << "Invalid option. Please introduce a valid number." << endl;
            delay(2);
            this->MainMenu();
            break;
    }
}

void Interface::editProfileOptions(int n) {
    string newData;
    int answerChoosePayment;

    switch(n){
        case 1:
        {
            system("clear");
            cout << "***** EDIT USERNAME *****" << endl;
            cout << "Enter a new username: ";
            cin.ignore();
            getline(cin,newData);
            if (manager.editUsername(newData))
            {
                 cout << "Your username has been edited correctly. " << endl;
                 delay(2);
            } else
            {
                 cout << "Your username could not be edited. " << endl;
                 delay(2);
            }
            break;
        }

       case 2:
        {
            system("clear");
            cout << "***** EDIT EMAIL *****" << endl;
            cout << "Enter a new email: ";
            cin >> newData;
            if (manager.editEmail(newData))
            {
                cout << "Your email has been edited correctly. " << endl;
                delay(2);
            }
            else
            {
                cout << "Your email could not be edited. " << endl;
                delay(2);
            }
            break;
        }

        case 3:
        {
            system("clear");
            cout << "***** EDIT PASSWORD *****" << endl;
            cout << "Enter a new password: ";
            cin >> newData;
            if (manager.editPassword(newData))
            {
                cout << "Your password has been edited correctly. " << endl;
                delay(2);
            }
            else
            {
                 cout << "Your password could not be edited. " << endl;
                 delay(2);
            }

            break;
        }

        case 4:
        {
            string newAddress;
            string newCity;
            string newProvince;
            string postal;
            unsigned int newPC;
            system("clear");
            cout << "***** EDIT ADDRESS *****" << endl;
            cout << "Enter a new address - Adress:\t";
            cin.ignore();
            getline(cin,newAddress);
            cout << "City:\t";
            cin.ignore();
            getline(cin,newCity);
            cout << "Province:\t";
            cin.ignore();
            getline(cin, newProvince);
            cout << "Postal code:\t";
            cin >> postal;

            /** MEJORA: Un codigo postal solo puede tener números. */
            for(int i = 0; i<(int) postal.size(); ++i)
            {
                if( !isdigit(postal[i]))
                {
                    cout << "A postal code is only composed of digits, try again" << endl;
                    cin >> postal;
                    i = 0;
                }
            }

            /** MEJORA: Un código postal solo puede tener 5 dígitos. */
            while( (int) postal.size() != 5 ){
                cout << "A postal code has exactly 5 digits, try again" << endl;
                cin >> postal;
            }

            newPC = stoul(postal);

            if (!manager.addAddress(newAddress, newCity, newProvince, newPC)){
                cout << "The address could not be created.  " << endl;
                delay(2);
            }
            else
            {
                cout << "The address has been correctly added. " << endl;
                delay(2);
            }
            break;
        }

        case 5:
        {
            system("clear");
            cout << "***** ADD PAYMENT METHOD *****" << endl;
            cout << " - ADD CREDITCARD (1) " << endl;
            cout << " - ADD PAYPAL (2) " << endl;

            cin >> answerChoosePayment;

            switch(answerChoosePayment)
            {
                case 1:
                {
                    system("clear");
                    unsigned long newTarget;
                    string input;
                    string newCardHolder;
                    string newBillingAddressCC;

                    cout << "***** ADD CREDITCARD *****" << endl;
                    cout << "Please introduce the new CreditCard number: " << endl;
                    cin >> input;
                    //checkCIN();

                    /** MEJORA: Comprueba que el numero de la tarjeta de crédito es menor de 16 dígitos y solo son números */
                    for(int i = 0; i<(int) input.size(); ++i)
                    {
                        if( !isdigit(input[i]))
                        {
                            cout << "The credit card number is only composed of digits, try again" << endl;
                            cin >> input;
                            i = 0;
                        }
                    }

                    while (input.size() != 16 ){//|| !isdigit(input)
                        cout << "The CreditCard number must have 16 digits (No letters allowed). Introduce it again." << endl;
                        cin >> input;
                    }
                    newTarget = stoul(input);

                    cout << "Please introduce name of the new card holder: " << endl;
                    cin.ignore();
                    getline(cin,newCardHolder);


                    cout << "Please introduce the address that corresponds to the new billing address: " << endl;
                    cout << "**************************************************" << endl;

                    Interface::showAdresses();

                    getline(cin,newBillingAddressCC);

                    for (int j = 0; j < (int)manager.getCurrentMember()->getAddresses().size() ; j++) // ERROR
                    {

                        if (manager.getCurrentMember()->getAddresses()[j]->getAddress() == newBillingAddressCC)
                        {

                            if (!manager.addCreditCard(manager.getCurrentMember()->getAddresses()[j], newTarget, newCardHolder)){

                                cout << "Could not create CreditCard paying method." << endl;
                                delay(2);
                                this->MainMenu();
                            }
                            else
                            {
                                cout << "You have added a CreditCard paying method. " << endl;
                                delay(2);
                                this->MainMenu();
                            }
                        }
                    }
                    cout << "Could not find that existing address. Try again." << endl;
                    delay(2);
                    break;
                }

                case 2:
                {
                    string newEmail;
                    string newBillingAddress;

                    system("clear");
                    cout << "***** ADD PAYPAL *****" << endl;

                    cout << "Please introduce the new email associated with the pay-pal account. " << endl;
                    cin >> newEmail;
                    //quizas estaria bie mostrarle las addresses que tiene ya creadas, ademas de que tiene que introducirla tal cual esta guardad
                    cout << "Please introduce the address that corresponds to the new billing address. " << endl;
                    Interface::showAdresses();
                    cin.ignore();
                    getline(cin,newBillingAddress);

                    for (int i = 0; i < (int)manager.getCurrentMember()->getAddresses().size() ; i++)
                    {
                        if (manager.getCurrentMember()->getAddresses()[i]->getAddress() == newBillingAddress)
                        {
                            if (!manager.addPaypal(manager.getCurrentMember()->getAddresses()[i], newEmail)){
                                cout << "Could not create PayPal paying method." << endl;
                                delay(2);
                                break;
                            }
                            else
                            {
                                 cout << "You have added a Paypal paying method. " << endl;
                                 delay(2);
                                 break;
                            }

                        }
                    }
                break;
                }
            }
        }
        case 6:
        {
            this->MainMenu();
        }
        default:
        {
            this->MainMenu();
        }

    }

    this->MainMenu();
}


void Interface::orderActionsOptions(int n){
    switch(n){
        case 1:
        {
            string junk;
            /** see my previous orders */
            system("clear");
            cout << "***** SEE MY PREVIOUS ORDERS *****" << endl;

            if ((int)manager.getCurrentMember()->getOrders().size() == 0) {
                    cout << " You have no existing orders " << endl;
                    delay(2);
            }
            else
            {
                cout << "You have " << (int)manager.getCurrentMember()->getOrders().size() << " previous order/s." << endl;
                cout << "Loading ..." << endl;
                delay(1);
                for (int i = 0; i < (int)manager.getCurrentMember()->getOrders().size() ; i++)
                {
                    cout << "ORDER " << i+1 << endl;
                    cout << "**************************************************" << endl;
                    cout << "Reference for order " << i+1 << ": " << manager.getCurrentMember()->getOrders()[i]->getReference() << endl;
                    for (int j = 0 ; j < (int)manager.getCurrentMember()->getOrders()[i]->getProducts().size() ; j++)
                    {
                        cout << "Product " << j+1 << ": " << endl;
                        cout << "Reference: " << manager.getCurrentMember()->getOrders()[i]->getProducts()[j];
                        cout << "**************************************************" << endl;
                    }
                    time_t date = manager.getCurrentMember()->getOrders()[i]->getDate();
                    /** MEJORA: función formatLocalTime */
                    string localtime = this->formatLocalTime(date);
                    cout << "Date: " << localtime << endl;
                    cout << "Delivery address: " << manager.getCurrentMember()->getOrders()[i]->getDeliveryAddress() << endl;
                    cout << "Payment method ID: " << manager.getCurrentMember()->getOrders()[i]->getPaymentMethod() << endl;
                    cout << "Total: " << manager.getCurrentMember()->getOrders()[i]->getTotal() << endl;
                    cout << "****************************************" << endl;
                    cout << "Press key to go back to Main Menu." << endl;
                    cin >> junk;

                }
            }
            break;
        }

        case 2:
        {
            /** make new order */
            system("clear");
            cout << "***** MAKE NEW ORDER *****" << endl;
            unsigned long newReference;
            vector<unsigned long> shoppingBag;
            string ans;
            int addressID;
            int paymentMethodID;

            /** see available products */
            Interface::showproducts();

            do {
                /** Add product reference to the shopping bag */
                cout << "Introduce product reference for order: " << endl;
                cin >> newReference;
                for (int i = 0 ; i < (int)manager.getProducts().size() ; i++)
                {
                    if (manager.getProducts()[i]->getReference() == newReference)
                    {
                        shoppingBag.push_back(newReference);
                        cout << "[SUCCESS] Added to the shopping bag" << endl;
                        delay(2);
                        break;
                    }
                }
                cout << "Would you like to add another product? (y/n)" << endl;
                cin >> ans;
            } while (ans == "y");

            /** choose biling address */
            cout << "***** ENTER YOUR BILLING ADDRESS *****" << endl;
            Interface::showAdresses();

            cout << "Introduce address ID" << endl;
            cin >> addressID;

            Interface::showPaymentMethods();
            cout << "Introduce payment method ID" << endl;
            cin >> paymentMethodID;

            if (!manager.makeOrder(shoppingBag, addressID, paymentMethodID)){
                    cout << "The order could not be completed. Please check if that address and that paymentmethod exists." << endl;
                    delay(2);
            } else {
                cout << "The order was completed succesfully." << endl;
                delay(2);
            }
        break;
        }

        case 3:
        {
             this->MainMenu();
        }

        default:
        {
            this->MainMenu();
        }

    }
    this->MainMenu();
}

void Interface::reviewActionsOptions(int n)
{
    this->showproducts();
    switch(n)
    {
    case 1:
    {
        unsigned long newreference;
        int rPoints;
        string rText;
        /** create review */
        /** select the product */

        cout << "Introduce the reference of the product which you want to review: " << endl;
        cin >> newreference;

        for (int i = 0 ; i < (int)manager.getCurrentMember()->getOrders().size() ; i++)
        {
            for (int j = 0; j < (int)manager.getCurrentMember()->getOrders()[i]->getProducts().size() ; j++)
            {
                /** check if the user has acquired that product */
                if (manager.getCurrentMember()->getOrders()[i]->getProducts()[j] == newreference)
                {
                    /** seacrh that product on the manager database */
                    for (int k = 0 ; k < (int)manager.getProducts().size() ; k++)
                    {
                        if (manager.getCurrentMember()->getOrders()[i]->getProducts()[j] == manager.getProducts()[k]->getReference())
                        {
                            /** create review */
                            cout << "Introduce the number of points you give to this product: " << endl;
                            cin >> rPoints;
                            cout << "Introduce the text you want to add to the review: " << endl;
                            cin.ignore();
                            getline(cin, rText);
                            if( manager.createReview(newreference, rPoints, rText) )
                            {
                                cout << "The review has correctly been created." << endl;
                                delay(2);
                                this->MainMenu();
                            }
                            else
                            {
                                cout << "The review could not be created correctly, try again" << endl;
                                delay(2);
                                this->MainMenu();
                            }
                        }
                    }
                }
            }
        }
        cout << "You have not made an order with such product." << endl;
        break;
    }
    case 2:
    {
        string aux;
        unsigned long newreference;
        int filter_rating;
        vector<Review*> reviews;

        cout << "Introduce the reference of the product:\t" ;
        cin >> newreference;
        cout << endl << "Introduce the rating by which you wish to filter the product's reviews:\t" ;
        cin >> filter_rating;

        reviews = manager.getReviewsByRating( newreference, filter_rating );

        cout << endl << "The reviews with a rating of "<< filter_rating << " on the product selected are: "<< endl;
        for( int i=0; i<(int)reviews.size(); ++i)
        {
            cout << reviews[i]->show();
        }
        cout << "Press any key when done." << endl;
        cin >> aux;
        this->MainMenu();
        break;

    }
    case 3:
    {
        /** vote review */
        unsigned long newreference;
        int answervoting;
        this->showreviews();
        cout << "VOTING ACTIONS - CHOOSE ACTION " << endl;
        cout << " - ADD ONE VOTE TO A REVIEW (1) " << endl;
        cout << " - TAKE AWAY ONE VOTE FROM A REVIEW (2) " << endl;
        cin >> answervoting;

        cout << endl << "Introduce the id of the review you want to vote:\t";
        cin >> newreference;

        switch(answervoting)
        {
            case 1:
            {
                if(manager.upvoteReview(newreference))
                {
                    cout << "Your vote has been properly recorded " << endl;
                }else{
                    cout << "Your vote could not be recorded. Try again." << endl;
                }
                break;
            }
            case 2:
            {
                if (manager.downvoteReview(newreference))
                {
                    cout << "Your vote has been properly recorded " << endl;
                }else{
                    cout << "Your vote could not be recorded. Try again." << endl;
                }
                break;
            }
        }

     break;
    }
    case 4:
    {
        this->showreviews();
        /** modify review */
        unsigned long newreference;
        int answermodify;
        int rating;
        string text;

        cout << "MODIFY REVIEW ACTION - CHOOSE ACTION " << endl;
        cout << " - MODIFY A REVIEW RATING (1) " << endl;
        cout << " - MODIFY A REVIEW TEXT (2) " << endl;
        cin >> answermodify;

        cout << endl << "Introduce the id of the review;";
        cin >> newreference;

        switch(answermodify)
        {
        case 1:
        {
            cout << "Introduce a new rating from 0 to 5 stars to modify the review:";
            cin >> rating;
            if(manager.modifyReviewRating(newreference, rating))
            {
                cout << "The review has properly been modified." << endl;
                delay(2);
                this->MainMenu();
            }
            break;
        }
        case 2:
        {
            cout << "Introduce a new text to modify the review:";
            cin.ignore();
            getline(cin, text);
            if(manager.modifyReviewText(newreference, text))
            {
                cout << "The review has properly been modified." << endl;
                delay(2);
                this->MainMenu();
            }
            break;
        }
        }
        break;
    }
    case 5:
    {
        /** delete review */
        unsigned long newreference;
        char answer;
        this->showreviews();

        cout << "Introduce the id of the review you wish to delete: ";
        cin >> newreference;

        if( manager.deleteReview(newreference))
        {
            /** return to principal menu */
            cout << "Review succesfully deleted. " << endl;
        }
        else
        {
            cout << "Do you want to try again with a different reference? (y/n)" << endl;
            cin >> answer ;
            if(answer == 'y'){
                this->reviewActionsOptions(5);
            }
        }
        break;
    }
    case 6:
    {
         this->MainMenu();
        break;
    }

    default:
    {
        this->MainMenu();
        break;
    }
    }
    delay(2);
    this->MainMenu();
}

void Interface::AdminMenu(){

    int answerAdminMenu;
    vector<PublicUserData*> UsersHistory;
    string name;
    string description;
    unsigned long newreference;
    float price;

    cout << "******* ADMIN MENU *******" << endl;
    cout << "Choose from the following options: " << endl;
    cout << " - ACCESS USER HISTORY (1) " << endl;
    cout << " - ADD NEW PRODUCT TO THE SYSTEM (2) " << endl;
    cout << " - SEE ALL EXISTING PRODUCTS (3) " << endl;
    cout << " - SEE ALL EXISTING USERS (4) " << endl;
    cout << " - RETURN TO PRINCIPAL MENU (5) " << endl;

    cin >> answerAdminMenu;

    switch( answerAdminMenu )
    {
        case 1:
        {
            UsersHistory = manager.showMembers();
            for ( int i=0; i<(int) UsersHistory.size() ; ++i)
            {
                cout << "Username: " << UsersHistory[i]->getUsername() << endl;
                cout << "Reputation: " << UsersHistory[i]->getReputation() << endl;
                cout << endl;
            }

            /** Show admin options again below?*/
            this->AdminMenu();
            break;
        }
        case 2:
        {
            Interface::showproducts();
            cout << "Name of new product: ";
            cin.ignore();
            getline( cin, name);
            cout << "Write a description for the new product: ";
            cin.ignore();
            getline( cin, description);
            cout << "Reference of new product: ";
            cin >> newreference;
            cout << "Price for new product: ";
            cin >> price;

            manager.addProduct(name, description, newreference, price);
            delay(2);
            /** Principal menu */
            this->MainMenu();

            break;
        }

        case 3:
        {
            string aux;
            this->showproducts();
            cout << "Are you done?. Press any key to exit." << endl;
            cin >> aux;
            this->MainMenu();
        }

        case 4:
        {
            string aux;
            this->showUsers();
            cout << "Are you done?. Press any key to exit." << endl;
            cin >> aux;
            this->MainMenu();
        }

        case 5:
        {
            this->MainMenu();
            break;
        }

    }
}

void Interface::showPaymentMethods()
{
    cout << "***** YOUR EXISTING PAYMENT METHODS *****" << endl;
    if (manager.getCurrentMember()->getPaymentMethods().size() == 0)
    {
        cout << "No existing payment methods. Please add one and try again." << endl;
        delay(3);
        this->MainMenu();
    }
    else
    {
        for (int i = 0 ; i < (int)manager.getCurrentMember()->getPaymentMethods().size() ; i++)
        {
             cout << manager.getCurrentMember()->getPaymentMethods()[i]->show() << endl;
             cout << "**************************************************" << endl;
        }
    }
}

void Interface::showAdresses()
{
    cout << "***** YOUR EXISTING ADDRESSES *****" << endl;
    /** If no existing address, force the user to create one before continuing */
    if (manager.getCurrentMember()->getAddresses().size() == 0)
    {
        cout << "No existing addresses. Please add one and try again." << endl;
        delay(2);
        this->MainMenu();
    }
    else
    {
        for (int i = 0 ; i < (int)manager.getCurrentMember()->getAddresses().size() ; i++){
            cout << "Address " << i << ": " << manager.getCurrentMember()->getAddresses()[i]->getAddress() << endl;
            cout << "ID: " << manager.getCurrentMember()->getAddresses()[i]->getId() << endl;
            cout << "**************************************************" << endl;
        }
    }
}

void Interface::showproducts()
{
    cout << "***** AVAILABLE PRODUCTS *****" << endl;
    for (int i = 0 ; i < (int)manager.getProducts().size() ; i++)
    {

        cout << "name: " << manager.getProducts()[i]->getName() << endl;
        cout << "description: " << manager.getProducts()[i]->getDescription() << endl;
        cout << "reference: " << manager.getProducts()[i]->getReference() << endl;
        cout << "price: " << manager.getProducts()[i]->getPrice() << endl;
        cout << "**************************************************" << endl;
    }
}

void Interface::showUsers()
{
    string type = "Standard user";
    cout << "***** AVAILABLE USERS *****" << endl;
    for (int i = 0 ; i < (int)manager.getUsers().size() ; i++)
    {
        cout << "Username: " << manager.getUsers()[i]->getUsername() << endl;
        cout << "Email: " << manager.getUsers()[i]->getEmail() << endl;
        cout << "Reputation: " << manager.getUsers()[i]->getReputation() << endl;
        if (manager.getUsers()[i]->isAdmin() == 1) {
            type = "Administrator";
        }
        cout << "Type: " << type << endl;
        cout << "**************************************************" << endl;
    }
}

void Interface::showreviews()
{
    cout << "***** YOUR PRODUCT REVIEWS *****" << endl;
    for (int i = 0 ; i < (int)manager.getProducts().size() ; i++)
    {
        for(int j = 0; j < (int)manager.getProducts()[i]->getReviews().size() ; j++)
        {
            cout << manager.getProducts()[i]->getReviews()[j]->show();
            cout << "**************************************************" << endl;
        }
    }

}

/** MEJORA: Comprobar que el tipo de dato es correcto */
/*void checkCIN(){
    if (cin){
        cout << "Incorrect format for input data. Try again." << endl;
    }
}*/


/** ******** MEJORA: Dar formato a la fecha e imprimirla por pantalla ******/

string Interface::formatLocalTime(const time_t & date)
{
    string time = asctime(localtime(&date));

    return time;
}

/** ******** MEJORA: Mostrar valoraciones realizadas por un determinado usuario ordenadas cronológicamente ******/

void Interface::showReviewOrdered(const User& U)
{
    vector<Review*> allreviews; // vector donde almacenamos todas las reviews del usuario

    vector<Review*> orderedreviews; // vector con las reviews ordenadas cronologicamente

    for(int i = 0; i < (int)manager.getProducts().size() ; ++i)
    {
        for(int j = 0; j < (int)manager.getProducts()[i]->getReviews().size() ; j++)
        {
            if(manager.getProducts()[i]->getReviews()[j]->getAuthor()->getUsername() == U.getUsername())
            {
                allreviews.push_back(manager.getProducts()[i]->getReviews()[j]);
            }
        }
    }

    int mintime = allreviews[0]->getTime();   // variable auxiliar que guarda la date de la review mas reciente en cada momento
    int minpos = 0;                             // variable auxiliar que guarda posicion en el vector de la review mas reciente en cada momento
    do{
        for(int i = 0; i < (int) allreviews.size() ; ++i)
        {
            if ( mintime > allreviews[i]->getTime())
            {
                mintime = allreviews[i]->getTime();
                minpos = i;
            }
        }

        orderedreviews.push_back(allreviews[minpos]);
        allreviews.erase(allreviews.begin()+minpos);

    }while(allreviews.size() != 0);

    for(int i = 0; i < (int)orderedreviews.size() ; ++i)
    {
        cout << *orderedreviews[i] <<endl;
    }
}
