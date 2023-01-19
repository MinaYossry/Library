#pragma once
#include "Person.h"
#include "Book.h"
#include <vector>
#include <iostream>

class Customer : public Person
{
private:
    vector<Book> boughtBooks;
    vector<Book> borrowedBooks;
    double accountBalance = 500;
    string paymentMethod;
public:
    Customer(int ID, int password, string name);
    void buyBook(Book& book);
    void borrowBook(Book& book);
    void returnBook(Book& book);
    void choosePaymentMethod();
    Book* searchForBook(string title);
    vector<Book>& getBoughtBooks();
    vector<Book>& getBorrowedBooks();
};