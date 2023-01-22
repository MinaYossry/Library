#include "Librarian.h"
#include "Library.h"

Librarian::Librarian(int _ID, string _name, int _password)
	: Person(_ID, _name, _password) { }

///
void Librarian::AddBook(Book* object, unordered_map<string, Book*>& booksList) {

    booksList.insert_or_assign(object->getTitle(), object);

};
// free memory after deletetion don't forget
void Librarian::DeleteBook(string bookName, unordered_map<string, Book*>& booksList) {

	if (booksList.find(bookName) != booksList.end())
	{
		booksList.erase(bookName);
	}
	else {
		cout << "Book doesn't exist" << endl;
	}
};


void Librarian::UpdateBook(string bookName, int newStock,const unordered_map<string, Book*>& booksList) {

	if (booksList.find(bookName) != booksList.end())
	{
		Person::searchBook(bookName, booksList)->setStock(newStock);
	}
	else
	{
		cout << "Book doesn't exist" << endl;
	}
}

void Librarian::lendBook(string bookName, const Date& _returnDate, Customer* obj, const unordered_map<string, Book*>& booksList, const vector<string> &paymentMethods) {

	Book* b1 = searchBook(bookName, booksList);
	if (b1 && obj && b1->getIsAvailable())
	{
        if (obj->choosePaymentMethod(b1->getPrice() * 0.15, paymentMethods))
        {
		    b1->setStock(-1);
		    borrowedBook* b2 = new borrowedBook(b1, _returnDate, obj);
		    Library::borrowedBookList.push_back(b2);
        }
	}
	else {
		cout << "Book doesn't exist" << endl;
	}

};

void Librarian::requestBorrowedBook(const Date &currentDate) {
    bool found = false;
	cout << endl;
	for (auto borrowedBook : Library::borrowedBookList)
	{
		if (currentDate > borrowedBook->returnDate) {
            found = true;
            cout << "Book Title: " << borrowedBook->book->getTitle() << " || " << "Customer: " << borrowedBook->customer->getName() << " || Return Date: " << borrowedBook->returnDate << endl;;
			borrowedBook->customer->recieveMessage("Please return book ( " + borrowedBook->book->getTitle() + " ) becaused it passed its return date");
		}
	}
    if (found)
        cout << endl << "Messages is sent to customers" << endl;
    else
        cout << endl << "No late books in library" << endl;
}

void Librarian::AddPaymentMethod(string paymentMethodName, vector<string> &paymentMethods) {

    paymentMethods.push_back(paymentMethodName);
};


void Librarian::generateReport(int choice, const unordered_map<int, Person*>& customers, const string& author, const unordered_map<string, Book*>& booksList, const unordered_set<string>& categoryList) {
    system("CLS");
    switch (choice) {
        case 1: {
            generateBorrowedBooksReport();
            break;
        }
        case 2: {
            generateAllBooksReport(booksList);
            break;
        }
        case 3: {
            generateBooksByCategoryReport(booksList, categoryList);
            break;
        }
        case 4: {
            generateMissedBooksReport(Date());
            break;
        }
        case 5: {
            generateBooksByAuthorReport(author, booksList);
            break;
        }
        case 6: {
            generateAllCustomersDetails(customers);
            break;
        }
    }
}

void Librarian::generateAllCustomersDetails(const unordered_map<int, Person*>& customers) {
    cout << "Total number of customers is : " << customers.size() << endl;
    for (const auto& customer : customers) {


        cout << "ID: " << customer.first << ") " << customer.second->getName() << endl;
        if (static_cast<Customer*>(customer.second)->displayBorrowedBooks())
        {
            cout << endl;
        }


    }
}

void Librarian::generateBorrowedBooksReport() {
    int counter = 0;
    cout << "Number and list of borrowed books" << endl;
    cout << "=================================" << endl;

    if (Library::borrowedBookList.size() == 0) {
        cout << "No borrowed books found." << endl;
    }
    else {
        cout << "Number of borrowed books is : " << Library::borrowedBookList.size() << endl;
        cout << "Borrowed Book List :\n" << "---------------\n";

        for (auto& borrowedBook : Library::borrowedBookList) {
            cout << ++counter << ") " << borrowedBook->book->getTitle() << " || return date " << borrowedBook->returnDate << " || Customer " << borrowedBook->customer->getName() << endl;
        }
    }
}


void Librarian::generateAllBooksReport(const unordered_map<string, Book*>& booksList) {
    cout << "Number and list of all books in the library" << endl;
    cout << "=================================" << endl;

    if (booksList.size() == 0) {
        cout << "No books found in the library." << endl;
    }
    else {
        cout << "Number of  books is : " << booksList.size() << endl;
        cout << "Books List :\n" << "---------------\n";

        for (auto& it : booksList) {
            cout << it.first << " || Stock: " << it.second->getStock() << " || Price: " << it.second->getPrice() << endl;
        }
    }
}

void Librarian::generateBooksByCategoryReport(const unordered_map<string, Book*>& booksList, const unordered_set<string> & categoryList) {
    int categoryCounter = 1;
    int counter = 0;
    bool found = false;
    for (const auto& category : categoryList) {
        cout << categoryCounter << ") " << category << endl;
        counter = 0;

        for (auto& it : booksList) {
            if (it.second->getCategory() == category) {
                counter++;
                found = true;
            }
        }

        if (counter == 0) {
            cout << "No books found in this category." << endl;
        }
        else {
            cout << "number of books in this Category is :" << counter << endl;
            cout << "===============================" << endl;
            for (auto& it : booksList) {
                if (it.second->getCategory() == category) {
                    cout << it.first << endl;
                }
            }
            cout << "===============================" << endl;
        }
        categoryCounter++;
    }
    if (!found) {
        cout << "No books found in any categories" << endl;
    }

}

void Librarian::generateMissedBooksReport(const Date& currectDate) {
    int counter = 0;
    cout << "Total number & list of all missed books from the library based on date" << endl;
    cout << "=================================" << endl;
    for (auto& borrowedBook : Library::borrowedBookList) {
        if (currectDate > borrowedBook->returnDate) {
            cout << ++counter << ") " << borrowedBook->book->getTitle() << " || return date " << borrowedBook->returnDate << " || Customer " << borrowedBook->customer->getName() << endl;
        }
    }
    if (counter == 0) {
        cout << "No missed books found." << endl;
    }
}

void Librarian::generateBooksByAuthorReport(const string& author, const unordered_map<string, Book*>& booksList) {
    int counter = 0;
    cout << "Total number & list of books for specific author" << endl;
    cout << "=================================" << endl;
    for (auto& it : booksList) {
        if (it.second->getAuthor() == author) {
            cout << ++counter << ") " << it.first << endl;
        }
    }
    if (counter == 0) {
        cout << "No books found for the specific author." << endl;
    }
}
