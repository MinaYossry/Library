#include "Customer.h"
#include "Library.h"
#include "BorrowedBook.h"

Customer::Customer(int ID, string name, int password,  double _accountBalance) : Person( ID,name, password) {
    accountBalance = _accountBalance;
}

void Customer::buyBook(Book* book, const vector<string>& paymentMethods)
{
    // code to buy a book
    if (book->getIsAvailable()) {
        if (choosePaymentMethod(book->getPrice(), paymentMethods))
            book->setStock(-1);
    }
    else {
        cout << "Book is not available" << endl;
    }
}

void Customer::borrowBook(Book* book, const vector<string>& paymentMethods)
{
    // code to borrow a book
    if (book->getIsAvailable()) {
        if (choosePaymentMethod(book->getPrice() * 0.15, paymentMethods))
        {
            Library::borrowedBookList.push_back(new borrowedBook(book, Date(), this));
            book->setStock(-1);
        }
    }
    else {
        cout << "Book is not available" << endl;
    }
}

void Customer::returnBook(Book* book, const vector<string>& paymentMethods)
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
        {
            if (choosePaymentMethod(target->book->getPrice() * 0.15, paymentMethods))
            {
                book->setStock(1);
                Library::borrowedBookList.erase(std::remove(Library::borrowedBookList.begin(), Library::borrowedBookList.end(), target), Library::borrowedBookList.end());
            }
        }
        else {
                book->setStock(1);
                Library::borrowedBookList.erase(std::remove(Library::borrowedBookList.begin(), Library::borrowedBookList.end(), target), Library::borrowedBookList.end());
        }
    }

}

bool Customer::choosePaymentMethod(double bill, const vector<string> &paymentMethods)
{
    system("CLS");
    cout << "=====================================" << endl;
    for (size_t i = 0; i < paymentMethods.size(); i++)
    {
        cout << i + 1 << "- " << paymentMethods.at(i) << endl;
    }
    cout << paymentMethods.size() + 1 << "- exit" << endl;
    cout << "=====================================" << endl;

    int choice{};
    do {
        cout << "Choice: ";
        choice = Library::getValidInt();
    } while (choice < 1 || choice > paymentMethods.size() + 1);
    if (choice - 1 >= paymentMethods.size()) {
        cout << "Transaction Cancelled...." << endl;
        return false;
    }
    else {
        cout << "You chose: " << paymentMethods.at(choice - 1) << endl;
        cout << "Checking balance .... " << endl;
        if (accountBalance >= bill) {
            cout << "Congratulation" << endl;
            accountBalance -= bill;
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
    bool found = false;
    for (auto borrowedBook : Library::borrowedBookList)
    {
        if (borrowedBook->customer == this) {
            if (!found) {
                cout << "List of Borrowed Books" << endl;
                cout << "====================================" << endl;
            }
            found = true;
            cout << borrowedBook->book->getId() << ") " << "Book Title: " << borrowedBook->book->getTitle() << " || Return Date: " << borrowedBook->returnDate << endl;
        }
    }
    if (found)
        cout << "====================================" << endl;

    return found;
}
