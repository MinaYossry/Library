#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>

#include "personsManager.h"

using namespace std;


struct Screens
{
	personsManager customers{typCustomer};
	personsManager librarians{ typLibrarian };
	personTypes currentUser = personTypes::typnone;
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
		"Search for a book",
		"Return a book",
		"Choose payment method",
	};

	const vector<string> librarianOptions{
		"Add book",
		"Delete book",
		"Update a book",
		"Lend a book",
		"Request Borrowed Book",
		"Add Payment method",
		"Generate Reports",
	};

	void  displayScreen(const vector<string> &screen);
	void  loginScreen();
	void  registerScreen();
	int getChoice(const vector<string>& screen);
};

