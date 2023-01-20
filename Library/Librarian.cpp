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
void Librarian::requestBorrowedBook(Customer* _customer, Book* bookObject, vector<Customer*> CustomerList) {
	
	for (int i = 0; i < CustomerList.size(); i++)
	{
		if (CustomerList.at(i)->getName() == _customer->getName())
		{
			CustomerList.at(i)->NotificationList.push_back("please return the book :" + bookObject->getName());
		}
	}
};

void Librarian::AddPaymentMethod(string paymentMethodName) {

	Library::paymentMethods.push_back(paymentMethodName);
};


void Librarian::generateReport(int choice,vector<Person*> customerList,string currentDate, string author) {

	int counter = 0;
	switch (choice)
	{
	case 1:// i have to get the borrowed books list and number of borrowed books
		system("CLS");
		cout << "Number and list of borrowed books"<<endl;
		cout << "=================================" << endl;
		cout << "Number of borrowed books is : " << Library::borrowedBookList.size()<< endl;
		cout << "Borrowed Book List :\n" << "---------------\n";
		for (int i = 0; i < Library::borrowedBookList.size(); i++)
		{
			cout << i + i << ") " << Library::borrowedBookList.at(i)->book->getName();
		}
		break;
	case 2: // total number & list of all books in the library 
		// make sure this array works correctly 
		system("CLS");
		cout << "Number and list of all books in the library" << endl;
		cout << "=================================" << endl;
		cout << "Number of  books is : " << Library::booksList.size() << endl;
		cout << "Books List :\n" << "---------------\n";
		for (auto& it:Library::booksList)
		{
			cout << it.first << endl;
		}
		break;
	case 3: // number & list of each book in each category
		
		for (size_t i = 0; i < Library::categoryList.size(); i++)
		{
			counter = 0;
			cout << i + 1 << ") " << Library::categoryList.at(i) << endl;
			for (auto& it : Library::booksList)
			{
				if (it.second->getCategory() == Library::categoryList.at(i))
					counter += 1;
			}
			cout << "number of books in this Category is :" << counter << endl;
			cout << "===============================";
			for (auto& it : Library::booksList)
			{
				if (it.second->getCategory() == Library::categoryList.at(i))
					cout << it.first << endl;
			}
		}
		break;
	case 4: // total number & list of all missed books from the library based on date i guess
		//assume return date is day number from 1-31 in the same month
		 counter = 0;
		for (int i = 0; i < Library::borrowedBookList.size(); i++)
		{
			if (std::stoi(Library::borrowedBookList.at(0)->returnDate) > std::stoi(currentDate))
				counter++;
		}
		cout << "Number of missed books from the library is : " << counter << endl;
		for (int i = 0; i < Library::borrowedBookList.size(); i++)
		{
			cout << i + 1 << ") " << Library::borrowedBookList.at(i)->book->getName() << endl;
		}
		
		break;
	case 5: // total number & list of books for specific author
	 counter = 0;
		for (auto& it : Library::booksList)
		{
			if (it.second->getAuthor() == author)
				counter++;
		}
		cout << "Number of books for " << author << " is:" << counter << endl;
		for (auto& it : Library::booksList)
		{
			if (it.second->getAuthor() == author)
				cout << it.first << endl;
		}
		break;
	case 6: // total number & list of customer's details
		cout << "Total number of customers is : " << customerList.size() << endl;
		for (int i = 0; i < customerList.size(); i++)
		{
			cout << i + 1 << ") " << customerList.at(i)->getName()<<endl;
		}
		break;
	}
};


/// some notes on the side
// 1- we need to create the borrowed list as static pulic on the library
// 2- we need to create category list or enum or whatever
// 3- for missed book we need to check current date and compare it to the lendDate now we can count that book as missed from
// the library