#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>

#include "PersonsManager.h"
#include "Book.h"

using namespace std;


class Library
{
private:
	PersonsManager customers{typCustomer};
	PersonsManager librarians{ typLibrarian };

	

	personTypes currentUser = personTypes::typNone;
	Person* activeUser = nullptr;

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

public:
	void addBorrowedBook(borrowedBook* Object) {
		borrowedBookList.push_back(Object);
	}
	void displayScreen(const vector<string> &screen);
	void loginScreen();
	void registerScreen();
	Book* searchForBook();
	void getChoice(const vector<string>& screen);
	void openLibrary();

	void personTypeScreenHdlr(int choice);
	void loginOrRegisterHdlr(int choice);
	void customerOptionsHdlr(int choice);
	void librarianOptionsHdlr(int choice);

};

