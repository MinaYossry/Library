#include "Librarian.h"
#include "Library.h"

Librarian::Librarian(int _ID, string _name, int _password)
	: Person(_ID, _name, _password) { }

///
void Librarian::AddBook(Book* object) {

	Library::booksList.insert_or_assign(object->getTitle(), object);

};
// free memory after deletetion don't forget
void Librarian::DeleteBook(string bookName) {

	if (Library::booksList.find(bookName) != Library::booksList.end())
	{
		Library::booksList.erase(bookName);
	}
	else {
		cout << "Book doesn't exist" << endl;
	}
};


void Librarian::UpdateBook(string bookName, int newStock) {

	if (Library::booksList.find(bookName) != Library::booksList.end())
	{
		Person::searchBook(bookName)->setStock(newStock);
	}
	else
	{
		cout << "Book doesn't exist" << endl;
	}
}

void Librarian::lendBook(string bookName, const Date& _returnDate, Customer* obj) {

	Book* b1 = searchBook(bookName);
	if (b1 && obj)
	{
		b1->setStock(-1);
		borrowedBook* b2 = new borrowedBook(b1, _returnDate, obj);
		Library::borrowedBookList.push_back(b2);
	}
	else {
		cout << "Book doesn't exist" << endl;
	}

};

void Librarian::requestBorrowedBook(const Date &currentDate) {
	cout << endl;
	for (auto borrowedBook : Library::borrowedBookList)
	{
		if (currentDate > borrowedBook->returnDate) {
			cout << "Book Title: " << borrowedBook->book->getTitle() << " || " << "Customer: " << borrowedBook->customer->getName();
			borrowedBook->customer->recieveMessage("Please return book ( " + borrowedBook->book->getTitle() + " ) becaused it passed its return date");
		}
	}
	cout << endl << "Messages is sent to customers" << endl;
}

void Librarian::AddPaymentMethod(string paymentMethodName) {

	Library::paymentMethods.push_back(paymentMethodName);
};


void Librarian::generateReport(int choice, const unordered_map<int, Person*>& customers, const string& author) {
    system("CLS");
    switch (choice) {
    case 1: {
        generateBorrowedBooksReport();
        break;
    }
    case 2: {
        generateAllBooksReport();
        break;
    }
    case 3: {
        generateBooksByCategoryReport();
        break;
    }
    case 4: {
        generateMissedBooksReport(Date());
        break;
    }
    case 5: {
        generateBooksByAuthorReport(author);
        break;
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
            Date date = borrowedBook->returnDate;
            string returnDate = to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
            cout << ++counter << ") " << borrowedBook->book->getTitle() << " || return date " << returnDate << " || Customer " << borrowedBook->customer->getName() << endl;
        }
    }
}


void Librarian::generateAllBooksReport() {
    cout << "Number and list of all books in the library" << endl;
    cout << "=================================" << endl;

    if (Library::booksList.size() == 0) {
        cout << "No books found in the library." << endl;
    }
    else {
        cout << "Number of  books is : " << Library::booksList.size() << endl;
        cout << "Books List :\n" << "---------------\n";

        for (auto& it : Library::booksList) {
            cout << it.first << " || Stock: " << it.second->getStock() << endl;
        }
    }
}

void Librarian::generateBooksByCategoryReport() {
    int categoryCounter = 1;
    int counter = 0;
    bool found = false;
    for (const auto& category : Library::categoryList) {
        cout << categoryCounter << ") " << category << endl;
        counter = 0;

        for (auto& it : Library::booksList) {
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
            for (auto& it : Library::booksList) {
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
            Date date = borrowedBook->returnDate;
            string returnDate = to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
            cout << ++counter << ") " << borrowedBook->book->getTitle() << " || return date " << returnDate << " || Customer " << borrowedBook->customer->getName() << endl;
        }
    }
    if (counter == 0) {
        cout << "No missed books found." << endl;
    }
}

void Librarian::generateBooksByAuthorReport(const string& author) {
    int counter = 0;
    cout << "Total number & list of books for specific author" << endl;
    cout << "=================================" << endl;
    for (auto& it : Library::booksList) {
        if (it.second->getAuthor() == author) {
            cout << ++counter << ") " << it.first << endl;
        }
    }
    if (counter == 0) {
        cout << "No books found for the specific author." << endl;
    }
}


/// some notes on the side
// 1- we need to create the borrowed list as static pulic on the library
// 2- we need to create category list or enum or whatever
// 3- for missed book we need to check current date and compare it to the lendDate now we can count that book as missed from
// the library