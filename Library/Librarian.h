#pragma once
#include "Person.h"
#include "Book.h"
#include "Customer.h"
#include<string>
#include <vector>
using namespace std;
class Librarian : public Person
{
public:
	Librarian(int _ID, int _password, string _name);
	// i give the addBook the book object and the array we want to attach this new book  to it
	void AddBook(Book* object);

	// this searches for the book first then deletes the book from the book vector
	void DeleteBook(string bookName);

	// do i just want to update the stock based on lend/buy/sell or what
	// so it searchs for the book first then depend on the case buy/sell/lend increase or decrease the stock of the book
	void UpdateBook(string bookName,string caseType);


	// so i search for that book and then update with case lend --decrease its stock number for the duration
	void lendBook(string bookName, string returnDate,Customer* custObject);

	// sends notification to the customer
	void requestBorrowedBook(Customer* customer,Book* bookObject);
	//creates new paymentmethod  and add it to the payment method list
	void AddPaymentMethod(string paymentMethodName);


	// you can just cout each report based on the choice from 1-6
	//iam jsut sending this list
	void generateReport(int choice,vector<Person*> customerList,string currentDate="0",string author="");

};

