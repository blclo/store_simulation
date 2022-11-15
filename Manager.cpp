#include "Manager.hpp"

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>        // std::remove
#include <stdio.h>
#include <string.h>

#include "User.hpp"
#include "Product.hpp"
#include "Address.hpp"
#include "Administrator.hpp"
#include "CreditCard.hpp"
#include "Paypal.hpp"

using namespace std;

Manager::Manager()
{
    _users = vector<User*>();
    _products = vector<Product*>();
    _current_member = -1;

}

Manager::~Manager()
{
    for(int i=0; i < (int)_users.size(); ++i)
    {
        delete _users[i];
    }

    for(int i=0; i<(int)_products.size(); ++i)
    {
        delete _products[i];
    }

}

bool Manager::login(const string & email, const string & password)
{
    if (_current_member == -1)
    {
        for(int i=0 ; i < (int)_users.size() ; ++i)
        {
            if((_users[i]->getEmail() == email) && (_users[i]->getPassword() == password))
            {
                _current_member = i;
                cout << "You have logged in correctly!" << endl;
                return true;
            }
        }
    }
    cout << "Your username or password does not match our records. Please try again or register."<< endl;
    return false;
}

bool Manager::logout()
{
    if (isLogged())
    {
        _current_member = -1;
        return true;
    }  else
    {
        // nobody is logged in
        cout << "Sorry, you are not logged." << endl;
        return false;
    }
}

bool Manager::isLogged()
{
    if (_current_member != -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

User* Manager::getCurrentMember() {
    if (isLogged())
    {
        return _users[_current_member];
    } else
    {
        return nullptr ;
    }
}

bool Manager::addUser(const string & username, const string & email, const string & password)
{
    for (int i = 0; i < (int)_users.size() ; i++)
    {

        if (_users[i]->getUsername() == username || _users[i]->getEmail() == email)
        {
            cout << "Please try again, this username or email already exist. " << endl;
            return false;   
        }
    }

    User *A = new User(username, email, password);
    _users.push_back(A);
    cout << "You have registered correctly. " << endl;
    return true;
}

bool Manager::addAdministrator(const string & username, const string & email, const string & password, unsigned long employeeCode)
{
    for (int i = 0; i < (int)_users.size() ; i++)
    {
        if (_users[i]->getUsername() == username || _users[i]->getEmail() == email)
        {
            cout << "This username or email is already in use. Try again. " << endl;
            return false;
        }
    }

    User *A = new Administrator(username, email, password, employeeCode);
    _users.push_back(A);
    cout << "An administrator has been created. " << endl;
    return true;
}

bool Manager::eraseCurrentMember()
{
    if (isLogged())
    {
        _users.erase(_users.begin() + _current_member);
        _current_member = -1;
        return true;
    } else {
        return false;
    }
}


bool Manager::addAddress(const string & address, const string & city, const string & province, unsigned int postalCode)
{
    if (isLogged())
    {
        int id = getCurrentMember()->getAddresses().size();

        Address *A = new Address(id, address, city, province, postalCode);
        _users[_current_member]->addAddress(A);
        return true;
    }
    else
    {
        return false;
    }
    
}

bool Manager::addCreditCard(Address *address, unsigned long target, const string & cardHolder)
{
    
    if (isLogged())
    {
        int id = getCurrentMember()->getPaymentMethods().size();

        CreditCard *A = new CreditCard(id, address , target , cardHolder);
        getCurrentMember()->addPaymentMethod(A);
        return true;
    }
    else
    {
        return false;
    }

}

bool Manager::addPaypal(Address *address, const string & email)
{
    if (isLogged())
    {
        int id = getCurrentMember()->getPaymentMethods().size();

        Paypal *A = new Paypal(id, address, email);
        getCurrentMember()->addPaymentMethod(A);
        return true;
    }
    else
    {
        return false;
    }
}


bool Manager::editUsername(const string & username)
{
    if(isLogged())
    {
        for (int i = 0 ; i < (int)_users.size() ; i++)
        {
            if (_users[i]->getUsername() == username)
            {
                cout << "This username already exists. Could not change your username to this one. " << endl;
                return false;
            }
        }
        getCurrentMember()->setUsername(username);
        return true;
    }else{
        return false;
    }
}

bool Manager::editEmail(const string & email)
{
    if(isLogged())
    {
        for (int i = 0 ; i < (int)_users.size() ; i++)
        {
            if (_users[i]->getEmail() == email)
            {
                cout << "This email already exists. Could not change your email to this one. " << endl;
                return false;
            }
        }
        getCurrentMember()->setEmail(email);
        return true;
    }else{
        return false;
    }
}
bool Manager::editPassword(const string & password)
{
    if(isLogged())
    {

        if (_users[_current_member]->getPassword() == password)
        {
            cout << "Please introduce a password you have not used before. " << endl;
            return false;
        }

        getCurrentMember()->setPassword(password);
        return true;
    }else{
        return false;
    }
}

bool  Manager::addProduct(const string & name, const string & description, unsigned long reference, float price)
{
    if (_current_member == -1 || getCurrentMember()->isAdmin() == 0) {       
        return false;
    }

    for (int i = 0; i < (int)_products.size() ; i++)
    {
        if (_products[i]->getReference() == reference)
        {
            cout << "This product already exists." << endl;
            return false;
        }
    }
    Product *P = new Product(name, description, reference, price);
    _products.push_back(P);
    cout << "The product has been added correctly." << endl;
    return true;
}

vector<PublicUserData*>  Manager::showMembers()
{
    vector<PublicUserData*> membersPublicData;

    if (isLogged() && getCurrentMember()->isAdmin() == true )
    {

        for (int i = 0 ; i < (int)_users.size() ; ++i)
        {
            PublicUserData* current_PublicUserData = new PublicUserData( _users[i]->getUsername());

            for( int m = 0; m < _users[i]->getReputation(); ++m)
            {
                current_PublicUserData->increaseReputation();
            }

            membersPublicData.push_back(current_PublicUserData);
            delete current_PublicUserData;

        }


    } else {
        membersPublicData = vector<PublicUserData*>();

    }
    return membersPublicData;
}


bool Manager::makeOrder(vector<unsigned long> products, int delivery_address, int payment_method)
{
    float total_price = 0;
    bool conditionA = false;
    bool conditionP = false;
    if(_current_member !=-1)
    {
        for( int i =0; i< (int) _users.size(); ++i)
        {
            for( int j=0; j<(int)getCurrentMember()->getAddresses().size(); ++j)
            {
                if(getCurrentMember()->getAddresses()[j]->getId() == delivery_address  )
                {
                    conditionA = true;
                    break;
                }
            }
        }

        for( int i =0; i< (int) _users.size(); ++i)
        {
            for( int j=0; j<(int)getCurrentMember()->getPaymentMethods().size(); ++j)
            {
                if(getCurrentMember()->getPaymentMethods()[j]->getId() == payment_method  )
                {
                    conditionP = true;
                    break;
                }
            }
        }

        if( conditionA== true && conditionP == true)
        {
            for( int i = 0; i < (int)products.size(); ++i)
            {
                for( int j=0; j < (int)_products.size(); ++j)
                {
                    if(_products[j]->getReference() == products[i])
                    {
                        if( getCurrentMember()->isAdmin() == true)
                        {
                            total_price += 0.925 * (_products[j]->getPrice());
                        }else{
                            total_price += _products[j]->getPrice();
                        }
                    }
                }
            }
            // orders_reference es una variable global definida en manager
            Order* current_Order = new Order(orders_reference, products, delivery_address, total_price);
            current_Order->setPaymentMethod(payment_method);

            getCurrentMember()->addOrder(current_Order);
            ++orders_reference ;
            return true;
        }
    }
    cout << "The provided address or paymentMethod ID does not exist." << endl;
    return false;
}

bool Manager::createReview(unsigned long reference, int rating, const string & text)
{
    /** If the user is logged */
    if (isLogged()) {
        // check for all the existing orders
        for (int i = 0 ; i < (int)getCurrentMember()->getOrders().size() ; i++)
        {
            // check if the user has bought the products in any of the orders he has made
            for (int j = 0 ; j < (int)getCurrentMember()->getOrders()[i]->getProducts().size() ; j++)
            {
                if(getCurrentMember()->getOrders()[i]->getProducts()[j] == reference)
                {
                    // add review
                    /** podriamos mandar solo author y no user
                    PublicUserData* Author = new PublicUserData(getCurrentMember()->getUsername());
                    for( int m = 0; m< getCurrentMember()->getReputation(); ++m)
                    {
                        Author->increaseReputation();
                    }
*/
                    Review *R = new Review(reference, rating, text, getCurrentMember());
                    for (int k = 0 ; k < (int)_products.size() ; k++)
                    {
                        if (_products[k]->getReference() == reference)
                        {
                            _products[k]->addReview(R);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}


vector<Review*> Manager::getReviewsByRating(unsigned long product_reference, int filter_rating)
{
    vector<Review*> current_reviews;
    vector<Review*> filtered_reviews;

    for( int i=0; i < (int)_products.size(); ++i)
    {
        if (_products[i]->getReference() == product_reference)
        {
            current_reviews = _products[i]->getReviews();
            break;
        }
    }

    for( int i = 0; i < (int)current_reviews.size(); ++i)
    {
        if(current_reviews[i]->getRating() == filter_rating)
        {
            filtered_reviews.push_back(current_reviews[i]);
        }
    }

    return filtered_reviews;
}

bool Manager::upvoteReview(unsigned long review_id)
{

    bool has_voted = false;

    if(isLogged() )
    {
        for (int i = 0 ; i < (int)getCurrentMember()->getVotesHistory().size(); ++i)
        {
            if( review_id == getCurrentMember()->getVotesHistory()[i])
            {
                has_voted = true;
                break;
            }
        }

        if(has_voted == false){
            for( int i=0; i < (int)_products.size(); ++i)
            {
                for( int j=0; j < (int)_products[i]->getReviews().size(); ++j)
                {
                    if(_products[i]->getReviews()[j]->getId() == review_id)
                    {
                        if(_products[i]->getReviews()[j]->getAuthor()->getUsername() != getCurrentMember()->getUsername())
                        {
                            _products[i]->getReviews()[j]->incrementVotes();
                            _products[i]->getReviews()[j]->getAuthor()->increaseReputation();
                            getCurrentMember()->addVoteHistory( review_id );
                            return true;
                        }else{
                            cout << " A user cannot vote their own reviews nor vote twice on the same review." << endl;
                            return false;
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool Manager::downvoteReview(unsigned long review_id)
{

    bool has_voted = false;

    if( isLogged() )
    {
        for ( int i = 0; i < (int)getCurrentMember()->getVotesHistory().size(); )
        {
            if( review_id == getCurrentMember()->getVotesHistory()[i])
            {
                has_voted = true;
                break;
            }
        }

        if(has_voted == false){
            for( int i=0; i < (int)_products.size(); ++i)
            {
                for( int j=0; j < (int)_products[i]->getReviews().size(); ++j)
                {
                    if(_products[i]->getReviews()[j]->getId() == review_id)
                    {
                        if(_products[i]->getReviews()[j]->getAuthor()->getUsername() != getCurrentMember()->getUsername() )
                        {
                            _products[i]->getReviews()[j]->decrementVotes();
                            _products[i]->getReviews()[j]->getAuthor()->decreaseReputation();
                            getCurrentMember()->addVoteHistory( review_id);
                            return true;
                        }else{
                            cout << " A user cannot vote their own reviews nor vote twice on the same review." << endl;
                            return false;
                        }
                    }
                }
            }
        }
    }
    return false;

}

bool Manager::modifyReviewRating(unsigned long review_id, int new_rating)
{
    if( isLogged())
    {
        for( int i=0; i < (int)_products.size(); ++i)
        {
            for( int j=0; j < (int)_products[i]->getReviews().size(); ++j)
            {
                if(_products[i]->getReviews()[j]->getId() == review_id)
                {
                    if(_products[i]->getReviews()[j]->getAuthor()->getUsername() == getCurrentMember()->getUsername())
                    {
                        _products[i]->getReviews()[j]->setRating(new_rating);
                        return true;
                    }else{
                        cout << "Only the author of this review can modify it" << endl;
                        return false;
                    }
                }
            }
        }
    }
    cout << "You have to be logged in in order to modify a review" << endl;
    return false;
}

bool Manager::modifyReviewText(unsigned long review_id, string new_text)
{
    if( isLogged())
    {
        for( int i=0; i < (int)_products.size(); ++i)
        {
            for( int j=0; j < (int)_products[i]->getReviews().size(); ++j)
            {
                if(_products[i]->getReviews()[j]->getId() == review_id)
                {
                    if(_products[i]->getReviews()[j]->getAuthor()->getUsername() == getCurrentMember()->getUsername())
                    {
                        _products[i]->getReviews()[j]->setText(new_text);
                        return true;
                    }else{
                        cout << "Only the author of this review can modify it" << endl;
                        return false;
                    }
                }
            }
        }
    }
    cout << "You have to be logged in in order to modify a review" << endl;
    return false;
}

bool Manager::deleteReview(unsigned long review_id)
{
    if( isLogged())
    {
        for( int i=0; i < (int)_products.size(); ++i)
        {
            for( int j=0; j < (int)_products[i]->getReviews().size(); ++j)
            {
                if(_products[i]->getReviews()[j]->getId() == review_id)
                {
                    if(_products[i]->getReviews()[j]->getAuthor()->getUsername() == getCurrentMember()->getUsername() || getCurrentMember()->isAdmin() == true)
                    {

                        _products[i]->getReviews().erase(_products[i]->getReviews().begin()+j);
                        /** Si se desea emplear el método delete Review de products */
                        // _products[i]->deleteReview(review_id);
                        return true;
                    }else{
                        cout << "Only the Author of the review or an Administrator can delete a review" << endl;
                        return false;
                    }
                }
            }
        }
    }
    return false;
}

void Manager::clear()
{
    /** clear user by user */
    for(int i=0; i<(int)_users.size(); ++i)
    {
        _users[i]->clear();
    }
}

void Manager::saveToFile( string  file_route )
{
    /** create write file */
    ofstream fsalida(file_route);

    /** user by user */
    for(int i=0; i<(int)_users.size(); ++i)
    {
        _users[i]->write(fsalida);

        for(int j=0; j< (int)_users[i]->getAddresses().size(); ++j)
        {
            _users[i]->getAddresses()[j]->write(fsalida);
        }

        for(int j=0; j< (int)_users[i]->getPaymentMethods().size(); ++j)
        {
            _users[i]->getPaymentMethods()[j]->write(fsalida);
        }

        for(int j=0; j< (int)_users[i]->getOrders().size(); ++j)
        {
            _users[i]->getOrders()[j]->write(fsalida);
        }

    }

    for( int i=0; i< (int)_products.size(); ++i)
    {
        _products[i]->write(fsalida);

        for(int j=0; j< (int)_products[i]->getReviews().size(); ++j)
        {
            _products[i]->getReviews()[j]->write(fsalida);
        }
    }

    fsalida.close();

}

void Manager::loadFromFile( const string & file_route )
{
    /** declare empty string */
    string search = "";
    /** key words needed */
    /** USER: */
    string user = "User:";
    string username = "" ;
    string email = "";
    string password = "";
    string reputation = "";
    string employeeCode = "";


    /** ADDRESS: */
    string address = "Address:";
    string id = "";
    string addressDirection = "";
    string city = "";
    string province = "";
    string postal_code = "";

    /** CREDITCARD */
    string CCid;
    string CCbiling;
    string CCnumber;
    string CCholder;

    /** PAYPAL */
    string Pid;
    string Pbiling;
    string Pemail;

    /** ORDER */
    string Oreference;
    string OdeliveryAddress;
    string OpaymentMethod;
    string Ototal;
    string Odate;
    string Preference;

    /** PRODUCT */
    string Pname;
    string PRreference;
    string Pprice;
    string Pdescription;
    string Rid;
    string Rdate;
    string Rrating;
    string Rtext;
    string Rvotes;
    string Rusername;

    vector<unsigned long> products;
    //int i = 0;
    //vector<unsigned long> Oproducts;

    /** create reading file */
    ifstream fentrada (file_route);

    while(!fentrada.eof())
    {
        getline(fentrada, search);

        if ( search == "User:" )
        {
          do{
            getline(fentrada, username);
            getline(fentrada, email);
            getline(fentrada, password);
            getline(fentrada, reputation);
            getline(fentrada, employeeCode);

            User *U = new User(username, email, password);
            U->setReputation(stoul(reputation));
            _users.push_back(U);


            getline(fentrada, search);
            if (search == "Address:"){
                do
                {
                    getline(fentrada, id);
                    getline(fentrada, addressDirection);
                    getline(fentrada, city);
                    getline(fentrada, province);
                    getline(fentrada, postal_code);

                    Address *A = new Address(stoi(id), addressDirection, city, province, stoul(postal_code)); // le mando un unsigned int
                    U->addAddress(A);

                    getline(fentrada, search);
                } while(search == "Address:");
            }
            if (search == "CreditCard:" || search == "Paypal:")
            {
                do{
                    if (search == "CreditCard:")
                    {
                        do {
                            getline(fentrada, CCid);
                            getline(fentrada, CCbiling);
                            getline(fentrada, CCnumber);
                            getline(fentrada, CCholder);

                            CreditCard *A = new CreditCard(stoi(CCid), U->getAddresses()[stoi(CCbiling)], stoul(CCnumber), CCholder);
                            U->addPaymentMethod(A);
                            //_users[iu]->addPaymentMethod(A);

                           /* for (int j = 0 ; j < (int)_users[iu]->getAddresses().size() ; j++){

                                if (_users[iu]->getAddresses()[j]->getId() == stoi(CCbiling)){
                                   CreditCard *A = new CreditCard(stoi(CCid), _users[iu]->getAddresses()[j], stoul(CCnumber), CCholder);
                                   _users[iu]->addPaymentMethod(A);
                                }
                            }*/

                            getline(fentrada, search);
                        } while (search == "CreditCard:");
                    }

                    if( search == "Paypal:" )
                    {
                        do
                        {
                            getline(fentrada, Pid);
                            getline(fentrada, Pbiling);
                            getline(fentrada, Pemail);

                            Paypal *P = new Paypal(stoi(Pid), U->getAddresses()[stoi(Pbiling)], Pemail);
                            U->addPaymentMethod(P);

                          /*  for (int j = 0 ; j < (int)_users[iu]->getAddresses().size() ; j++){

                                if (_users[iu]->getAddresses()[j]->getId() == stoi(Pbiling)){
                                   Paypal *P = new Paypal(stoi(Pid), _users[iu]->getAddresses()[j], Pemail);
                                   _users[iu]->addPaymentMethod(P);
                                }
                            }*/

                            getline(fentrada, search);
                        } while (search == "Paypal:");
                    }
                }while(search == "CreditCard:" || search == "Paypal:");
            }

            if ( search == "Order:")
            {
                do
                {
                    getline(fentrada, Oreference);
                    getline(fentrada, search);
                    if (search == "order_product:"){
                        do
                        {
                            getline(fentrada, Preference);
                            products.push_back(stoul(Preference));
                            //_users[iu]->getOrders()[io]->addProduct(stoul(Preference));
                            getline(fentrada, search);
                        } while (search == "order_product:");
                    }
                    Odate = search;
                    getline(fentrada, OdeliveryAddress);
                    getline(fentrada, OpaymentMethod);
                    getline(fentrada, Ototal);

                    Order *O = new Order(stoul(Oreference), products, stoi(OdeliveryAddress), stof(Ototal));
                    O->setPaymentMethod(stoi(OpaymentMethod));
                    O->setDate(Odate);
                    U->addOrder(O);

                    //_users[iu]->addOrder(O);
                    //_users[iu]->getOrders()[io]->setDate(Odate);
                    //_users[iu]->getOrders()[io]->setTotal(stof(Ototal));

                    getline(fentrada, search);
                } while (search == "Order:");
            }
            //_users.push_back(U);
            if (stoi(employeeCode) != -1){

                Administrator *U2 = new Administrator(username, email, password, stoul(employeeCode));
                U2->setReputation(stoul(reputation));

                //meter addresses, pm y orders de U en U2
                for(int j=0; j< (int)U->getAddresses().size(); ++j)
                {
                    U2->addAddress(U->getAddresses()[j]);
                }

                for(int j=0; j< (int)U->getPaymentMethods().size(); ++j)
                {
                    U2->addPaymentMethod(U->getPaymentMethods()[j]);
                }

                for(int j=0; j< (int)U->getOrders().size(); ++j)
                {
                    U2->addOrder(U->getOrders()[j]);
                }

                _users.pop_back();
                _users.push_back(U2);
            }
            } while(search == user);
        }

        if (search == "Product:")
        {
            do{
                getline(fentrada, Pname);
                getline(fentrada, Pdescription);
                getline(fentrada, PRreference);
                getline(fentrada, Pprice);
                Product *P = new Product(Pname, Pdescription, stoul(PRreference), stof(Pprice));
                this->_products.push_back(P);
                getline(fentrada, search);
                if (search == "Review:")
                {
                    do
                    {
                        getline(fentrada, Rid);
                        getline(fentrada, Rdate);
                        getline(fentrada, Rrating);
                        getline(fentrada, Rtext);
                        getline(fentrada, Rvotes);
                        getline(fentrada, Rusername);
                        for (int i = 0 ; i < (int)_users.size(); i++){
                            if (_users[i]->getUsername() == Rusername){
                                Review *R = new Review(stoul(Rid), stoi(Rrating), Rtext, _users[i]);
                                R->setDate(Rdate);
                                R->setVotes(stoi(Rvotes));
                                P->addReview(R);
                            }
                        }
                        // PublicUserData *User = new PublicUserData(Rusername);
                        //User->setReputation(_users[iu]->getReputation());

                        /*for (int i = 0 ; i < (int)this->getUsers().size() ; i++){
                            if (this->getUsers()[i]->getUsername() == Rusername){
                                Review *R = new Review(stoul(Rid), stoi(Rrating), Rtext, this->getUsers()[i]);
                                R->setDate(Rdate);
                                R->setVotes(stoi(Rvotes));
                            }
                        }*/
                        getline(fentrada, search);
                    } while (search == "Review:");
                }
                //getline(fentrada, search);
            } while (search == "Product:");
        }
    }
    fentrada.close();
}

