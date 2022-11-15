#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <iostream>
#include <ctime>
#include "User.hpp"
#include "Product.hpp"
#include "Address.hpp"
#include "Administrator.hpp"
#include "CreditCard.hpp"
#include "Paypal.hpp"
#include <fstream>

using namespace std;

/**
 * @brief This class is responsible for the whole system, therefore it controls
 * all its functionalities
 */

/** Definicion de variables estaticas que usaremos para las referencias de los products y los orders */
static int products_reference = 0;
static unsigned long orders_reference = 0;

class Manager
{
public:
    /** Empty constructor */
    Manager();

    /** Destructor */
    ~Manager();

    /** Getters  */
    vector<User*> getUsers() const {return _users;}
    vector<Product*> getProducts() const {return _products;}

    /** Methods  */
    bool login(const string & email, const string & password);
    bool logout();
    bool isLogged();
    User* getCurrentMember();
    bool addUser(const string & username, const string & email, const string & password);
    bool addAdministrator(const string & username, const string & email, const string & password, unsigned long employeeCode);
    bool eraseCurrentMember();

    bool editUsername(const string & username);
    bool editEmail(const string & email);
    bool editPassword(const string & password);

    bool addAddress(const string & address, const string & city, const string & province, unsigned int postalCode);
    bool addCreditCard(Address* address, unsigned long target, const string & cardHolder);
    bool addPaypal(Address* address, const string & email);

    bool  addProduct(const string & name, const string & description, unsigned long reference, float price);
    vector<PublicUserData*> showMembers();
    bool makeOrder(vector<unsigned long> products, int delivery_address, int payment_method);
    bool createReview(unsigned long reference, int rating, const string & text);

    vector<Review*> getReviewsByRating(unsigned long product_reference, int rating);
    bool upvoteReview(unsigned long review_id);
    bool downvoteReview(unsigned long review_id);
    bool modifyReviewRating(unsigned long review_id, int new_rating);
    bool modifyReviewText(unsigned long review_id, string new_text);
    bool deleteReview(unsigned long review_id); 

    /** saves all the system information into a file */
    void saveToFile( string file_route );
    /** loads all the file information into the system */
    void loadFromFile( const string & file_route );
    /** empties all the system information */
    void clear();

private:
    vector<User*> _users;
    vector<Product*> _products;
    int _current_member; // position of the vector _users

};

#endif // MANAGER_HPP
