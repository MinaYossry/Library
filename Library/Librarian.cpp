#include "Librarian.h"
#include <unordered_map>
#include <string>
#include "Book.h"
#include "Library.h"
Librarian::Librarian(int _ID, int _password, string _name)
	: Person(_ID, _password, _name) { }

///
void Librarian::AddBook(Book* object) {

	Library::booksList.insert_or_assign(object->getName(), object);
	
};
// free memory after deletetion don't forget
void Librarian::DeleteBook(string bookName) {

	if (Library::booksList.find(bookName) != Library::booksList.end())
	{
		Library::booksList.erase(bookName);
	}
};


void Librarian::UpdateBook(string bookName,string caseType) {

	if (Library::booksList.find(bookName) != Library::booksList.end())
	{
		if (caseType == "buy"||caseType=="lend")
		{
			Person::searchBook(bookName)->setStock(-1);
		}
		else if (caseType == "returnBook")
		{
			Person::searchBook(bookName)->setStock(1);
		}
	}
}

void Librarian::lendBook(string bookName, string _returnDate, Customer* obj) {
		
	Book* b1 = searchBook(bookName);
	borrowedBook b2;
	b2.book = b1;
	b2.returnDate = _returnDate;
	
	Library::borrowedBookList.push_back(&b2);
};

///lets consider that we have customer list or vector whatever
void Librarian::requestBorrowedBook(Customer* _customer, Book* bookObject) {
	//psudo code for the customer vector
	vector<Customer*> CustomerList;
	for (int i = 0; i < CustomerList.size(); i++)
	{
		if (CustomerList.at(i) == _customer)
		{
			CustomerList.at(i)->NotificationList.push_back("please return the book :" + bookObject->getName());
		}
	}
};

void Librarian::AddPaymentMethod(string paymentMethodName) {

	Library::paymentMethods.push_back(paymentMethodName);
};


void Librarian::generateReport(int choice) {


	switch (choice)
	{
	case 1:// i have to get the borrowed books list and number of borrowed books
		system("CLS");
		cout << "Number and list of borrowed books";
		cout << "=========================";
		break;
	case 2: // total number & list of all books in the library
		break;
	case 3: // number & list of each book in each category
		break;
	case 4: // total number & list of all missed books from the library based on date i guess
		break;
	case 5: // total number & list of books for specific author
		break;
	case 6: // total number & list of customer's details
		break;
	}
};


/// some notes on the side
// 1- we need to create the borrowed list as static pulic on the library
// 2- we need to create category list or enum or whatever
// 3- for missed book we need to check current date and compare it to the lendDate now we can count that book as missed from
// the library