#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
//#include <ctime>

#include "Person.h"
#include "Customer.h"
#include "Librarian.h"
#include "PersonsManager.h"
#include "Book.h"

using namespace std;


struct borrowedBook
{
	Book* book;
	tm returnDate;
	Customer* customer;
};

class Library
{
private:
	PersonsManager customers{ personTypes::typCustomer };
	PersonsManager librarians{ personTypes::typLibrarian };

	

	personTypes currentUser = personTypes::typNone;

	Person* activeUser = nullptr;
	Customer* activeCustomer = nullptr;
	Librarian* activeLibrarian = nullptr;

	const  vector<string> personTypeScreen{
		"Librarien",
		"Customer",
	};

	const  vector<string> loginOrRegister{
		"Login",
		"Register"
	};

	const vector<string> customerOptions{
		"Buy a book",
		"Borrow a book",
		"Search for a book", // should be in the person class
		"Return a book",
		"Choose payment method",
	};

	const vector<string> librarianOptions{
		"Add book",
		"Delete book",
		"Update a book",
		"Lend a book",
		"Request Borrow0ed Book",
		"Add Payment method",
		"Generate Reports",
	};

	const vector<string> reports{
		"Total number & List of borrowed books",
		"Total number & list of all books in the library ",
		"Number & list of books in each book category",
		"Total number & list of missed books from the library ",
		"Total number & list of books for a specific author",
		"Total number & list of customers details ",
	};

public:
	void addBorrowedBook(borrowedBook* Object) {
		borrowedBookList.push_back(Object);
	}
	void displayScreen(const vector<string> &screen);
	void loginScreen();
	void registerScreen();
	string enterBookName();
	void getChoice(const vector<string>& screen);
	void openLibrary();

	void personTypeScreenHdlr(int choice);
	void loginOrRegisterHdlr(int choice);
	void customerOptionsHdlr(int choice);
	void librarianOptionsHdlr(int choice);
	void reportScreenHdlr(int choice);
	tm getDate();


	// my added dynamic lists (taha)
	static vector<string> paymentMethods;
	static unordered_map<string, Book*> booksList;
	static vector<borrowedBook*> borrowedBookList;
	static vector<string> categoryList;
	//vector<Customer*> CustomerList;

};