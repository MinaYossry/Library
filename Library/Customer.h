#pragma once
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
    void buyBook(Book* book);
    void borrowBook(Book* book);
    void returnBook(Book* book);
    bool choosePaymentMethod(double bill);
    void recieveMessage(const string& message);
    void displayMessage();
};