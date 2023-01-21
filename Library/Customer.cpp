#include "Customer.h"
#include "Library.h"

Customer::Customer(int ID, string name, int password) : Person( ID,name, password) {
    accountBalance = 500;
}

void Customer::buyBook(Book* book)
{
    // code to buy a book
    if (book->getIsAvailable()) {
        if (choosePaymentMethod(book->getPrice()))
            book->setStock(-1);
    }
    else {
        cout << "Book is not available" << endl;
    }
}

void Customer::borrowBook(Book* book)
{
    // code to borrow a book
    if (book->getIsAvailable()) {
        if (choosePaymentMethod(book->getPrice() * 0.15))
        {
            Library::borrowedBookList.push_back(new borrowedBook(book, Date(), this));
            book->setStock(-1);
        }
    }
    else {
        cout << "Book is not available" << endl;
    }
}

void Customer::returnBook(Book* book)
{
    // code to return a book
    borrowedBook* target = nullptr;
    bool found = false;
    for (const auto& borrowedBook : Library::borrowedBookList)
    {
        if (borrowedBook->book == book)
        {
            target = borrowedBook;
            found = true;
            break;
        }
    }

    if (found) {
        if (Date() > target->returnDate)
            choosePaymentMethod(target->book->getPrice() * 0.15);

        book->setStock(1);
        Library::borrowedBookList.erase(std::remove(Library::borrowedBookList.begin(), Library::borrowedBookList.end(), target), Library::borrowedBookList.end());
    }

}

bool Customer::choosePaymentMethod(double bill)
{
    system("CLS");
    cout << "=====================================" << endl;
    for (size_t i = 0; i < Library::paymentMethods.size(); i++)
    {
        cout << i + 1 << "- " << Library::paymentMethods.at(i) << endl;
    }
    cout << Library::paymentMethods.size() + 1 << "- exit" << endl;
    cout << "=====================================" << endl;

    int choice{};
    do {
        cout << "Choice: ";
        choice = Library::getValidInt();
    } while (choice < 1 || choice > Library::paymentMethods.size() + 1);
    if (choice - 1 >= Library::paymentMethods.size()) {
        return false;
    }
    else {
        cout << "You chose: " << Library::paymentMethods.at(choice - 1) << endl;
        cout << "Checking balance .... " << endl;
        if (accountBalance >= bill) {
            cout << "Congratulation" << endl;
            return true;
        }
        else {
            cout << "Not Enough balance" << endl;
            return false;
        }
    }
}

void Customer::recieveMessage(const string& message)
{
    messages.push_back(message);
}

void Customer::displayMessage()
{
    system("CLS");
    cout << "Messages" << endl;
    cout << "==========================================" << endl;
    for (const auto& message : messages) {
        cout << message << endl;
    }
    cout << "==========================================" << endl;
}

bool Customer::displayBorrowedBooks()
{
    int counter = 0;
    bool found = false;
    for (auto borrowedBook : Library::borrowedBookList)
    {
        if (borrowedBook->customer == this) {
            if (!found) {
                cout << "List of Borrowed Books" << endl;
                cout << "====================================" << endl;
            }
            found = true;
            cout << ++counter << ") " << "Book Title: " << borrowedBook->book->getTitle() << " || Return Date: " << borrowedBook->returnDate << endl;
        }
    }
    if (counter)
        cout << "====================================" << endl;

    return counter;
}
