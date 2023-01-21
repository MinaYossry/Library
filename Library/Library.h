﻿#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <unordered_set>
#include <ctime>
#include <stdio.h>
#include <conio.h>

#include "Person.h"
#include "Customer.h"
#include "Librarian.h"
#include "PersonsManager.h"
#include "Book.h"
#include "Date.h"

using namespace std;



struct borrowedBook
{
	Book* book;
	Date returnDate;
	Customer* customer;
	borrowedBook(Book* _book, const Date& _returnDate, Customer* _customer)
		: book{ _book }, returnDate{ _returnDate }, customer{ _customer } {};
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
		"Display messages",
	};

	const vector<string> librarianOptions{
		"Add book",
		"Delete book",
		"Update a book",
		"Lend a book",
		"Request Borrow0ed Book",
		"Search for a book",
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
	Library() {
		customers.persons = {
			{1,new Customer(1, "John Doe",123)},
			{2,new Customer(2, "Jane Smith",123)},
			{3,new Customer(3, "Bob Johnson",123)},
			{4,new Customer(4, "Emily Davis",123)},
			{5,new Customer(5, "Michael Brown",123)},
			{6,new Customer(6, "Jessica Garcia",123)},
			{7,new Customer(7, "David Martinez",123)},
			{8,new Customer(8, "Sarah Anderson",123)},
			{9,new Customer(9, "Edward Taylor",123)},
			{10,new Customer(10, "Ashley Hernandez",123)},
		};

		librarians.persons = {
			{1,new Customer(1, "John Doe",123)},
			{2,new Customer(2, "Jane Smith",123)},
			{3,new Customer(3, "Bob Johnson",123)},
			{4,new Customer(4, "Emily Davis",123)},
			{5,new Customer(5, "Michael Brown",123)},
			{6,new Customer(6, "Jessica Garcia",123)},
			{7,new Customer(7, "David Martinez",123)},
			{8,new Customer(8, "Sarah Anderson",123)},
			{9,new Customer(9, "Edward Taylor",123)},
			{10,new Customer(10, "Ashley Hernandez",123)},
		};
	}

	void addBorrowedBook(borrowedBook* Object) {
		borrowedBookList.push_back(Object);
	}
	void displayScreen(const vector<string> &screen);
	void loginScreen();
	void registerScreen();
	void displayBookList();

	 


	string enterBookName();

	bool validateBookExists(const std::string& bookName);
	bool validateCustomerExists(int id);
	bool validatePaymentMethodExists(const std::string& payment);
	void getChoice(const vector<string>& screen);
	void openLibrary();


	void personTypeScreenHdlr(int choice);
	void loginOrRegisterHdlr(int choice);
	void customerOptionsHdlr(int choice);
	void addBookHdlr();
	void deleteBookHdlr();
	void updateBookHdlr();
	void lendBookHdlr();
	void requestBorrowedBookHdlr();
	void searchForBookHdlr();
	void addPaymentMethodHdlr();
	void generateReportHdlr();
	void librarianOptionsHdlr(int choice);
	void reportScreenHdlr(int choice);
	void buyBookHdlr();
	void borrowBookHdlr();
	void searchForBookHdlrC();
	void returnBookHdlr();
	void displayMessageHdlr();
	void continueProgram();



	// my added dynamic lists (taha)
	static vector<string> paymentMethods;
	static unordered_map<string, Book*> booksList;
	static vector<borrowedBook*> borrowedBookList;
	static unordered_set<string> categoryList;
	static int getValidInt();
	static double getValidDouble();

	//vector<Customer*> CustomerList;

};