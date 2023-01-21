#pragma once
#include <string>
#include <vector>

#include "Person.h"
#include "Book.h"
#include "Customer.h"

using namespace std;

class Librarian : public Person
{
public:
	Librarian(int _ID, string _name, int _password);
	// i give the addBook the book object and the array we want to attach this new book  to it
	void AddBook(Book* object);

	// this searches for the book first then deletes the book from the book vector
	void DeleteBook(string bookName);

	// do i just want to update the stock based on lend/buy/sell or what
	// so it searchs for the book first then depend on the case buy/sell/lend increase or decrease the stock of the book
	void UpdateBook(string bookName, int newStock);


	// so i search for that book and then update with case lend --decrease its stock number for the duration
	void lendBook(string bookName, const Date& returnDate, Customer* custObject);

	// sends notification to the customer
	void requestBorrowedBook(const Date& currentDate);
	//creates new paymentmethod  and add it to the payment method list
	void AddPaymentMethod(string paymentMethodName);


	// you can just cout each report based on the choice from 1-6
	//iam jsut sending this list
	void generateReport(int choice, const unordered_map<int, Person*>& customers, const string& author = "");

	void generateBorrowedBooksReport();

	void generateAllBooksReport();

	void generateBooksByCategoryReport();

	void generateMissedBooksReport(const Date& currectDate);

	void generateBooksByAuthorReport(const string& author);


};


