#include "Customer.h"

Customer::Customer(int ID, int password, string name) : Person( ID, password,name ) {
    accountBalance = 500;
}

void Customer::buyBook(Book& book)
{
    // code to buy a book
    if (book.getIsAvailable()) {
        if (accountBalance >= book.getPrice()) {
            accountBalance -= book.getPrice();
            boughtBooks.push_back(book);
            book.setAvailability(false);
        }
        else {
            cout << "Not Enough balance" << endl;
        }
    }
    else {
        cout << "Book is not available" << endl;
    }
}

void Customer::borrowBook(Book& book)
{
    // code to borrow a book
    if (book.getIsAvailable()) {
        borrowedBooks.push_back(book);
        book.setAvailability(false);
    }
    else {
        cout << "Book is not available" << endl;
    }
}

void Customer::returnBook(Book& book)
{
    // code to return a book
    book.setAvailability(true);
    borrowedBooks.erase(std::remove(borrowedBooks.begin(), borrowedBooks.end(), book), borrowedBooks.end());
}

void Customer::choosePaymentMethod()
{
    //// code to choose a payment method
    cout << "Enter Payment Method: " << endl;
    cout << "1. Credit Card" << endl;
    cout << "2. Debit Card" << endl;
    cout << "3. Cash" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        paymentMethod = "Credit Card";
        break;
    case 2:
        paymentMethod = "Debit Card";
        break;
    case 3:
        paymentMethod = "Cash";
        break;
    default:
        break;
    }
}

Book* Customer::searchForBook(string title)
{
    // code to search for a book by title
    for (auto& book : Book::getCollection()) {
        if (book.getTitle() == title) return &book;
    }
    cout << "Book not found" << endl;
    return nullptr;
}
vector<Book>& Customer::getBoughtBooks() {
    return boughtBooks;
}
vector<Book>& Customer::getBorrowedBooks() {
    return borrowedBooks;
}