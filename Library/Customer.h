#pragma once
#include <unordered_map>
#include <vector>
#include "Person.h"

struct borrowedBook
{
	Book* book;
	string returnDate;
};

class Customer : public Person
{
private:
	// Book
	// Return Date


	vector<string> notification;

public:
	Customer(int _ID, int _password, string _name);

	vector<borrowedBook*> borrowedBookList;


	void reqBook(string name)
	{
		Book* currentBook = searchBook(name);
		if (currentBook)
		{
			borrowedBook* newBorrowedBook = new borrowedBook();
			newBorrowedBook->book = currentBook;
			newBorrowedBook->returnDate = "sadkljasdlkas";

			borrowedBookList.push_back(newBorrowedBook);
		}
		else {
			cout << "book not found";
		}
	}

	void reqBook(Book* book)
	{
		if (book)
		{
			////
		}
		else {
			cout << "book not found";
		}
	}

	void recieveNot(string messange)
	{
		notification.push_back(messange);
	}

};

