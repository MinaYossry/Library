#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "Person.h"
#include "Book.h"
#include <vector>
#include <iostream>
#include <string>



class Customer : public Person
{
private:
    double accountBalance = 500;
    vector<string> messages;
public:
    Customer(int ID, string name, int password);
    void buyBook(Book* book, const vector<string>& paymentMethods);
    void borrowBook(Book* book, const vector<string>& paymentMethods);
    void returnBook(Book* book, const vector<string>& paymentMethods);
    bool choosePaymentMethod(double bill, const vector<string>& paymentMethods);
    void recieveMessage(const string& message);
    void displayMessage();
    bool displayBorrowedBooks();
};



#endif