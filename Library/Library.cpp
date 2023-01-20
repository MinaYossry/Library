#include "Library.h"
#include "Customer.h"
#include <string>

void Library::displayScreen(const vector<string>& screen)
{
	system("CLS");
	cout << "=====================================" << endl;
	for (size_t i = 0; i < screen.size(); i++)
	{
		cout << i + 1 << "- " << screen.at(i) << endl;
	}
	cout << screen.size() + 1 << "- exit" << endl;
	cout << "=====================================" << endl;
}

void Library::getChoice(const vector<string>& screen)
{
	int choice{};
	do {
		displayScreen(screen);
		cout << "Choice: ";
		cin >> choice;
	} while (choice < 1 || choice > screen.size() + 1);

	if (screen == personTypeScreen) {
		personTypeScreenHdlr(choice);
	}

	else if (screen == loginOrRegister) {
		loginOrRegisterHdlr(choice);
	}

	else if (screen == customerOptions) {
		customerOptionsHdlr(choice);
	}

	else if (screen == librarianOptions) {
		librarianOptionsHdlr(choice);
	}
	else if (screen == reports) {
		reportScreenHdlr(choice);
	}
}

void Library::openLibrary()
{
	getChoice(personTypeScreen);
}

void Library::personTypeScreenHdlr(int choice)
{
	switch (choice)
	{
	case 1:
		currentUser = typLibrarian;
		break;
	case 2:
		currentUser = typCustomer;
		break;
	case 3:
	default:
		exit(0);
		break;
	}
	getChoice(loginOrRegister);
}

void Library::loginOrRegisterHdlr(int choice)
{
	switch (choice)
	{
	case 1:
		loginScreen();
		break;
	case 2:
		registerScreen();
		break;
	case 3:
	default:
		getChoice(personTypeScreen);
		break;
	}
}

void Library::customerOptionsHdlr(int choice)
{
	system("CLS");
	Customer* customer = dynamic_cast<Customer*>(activeUser);
	switch (choice)
	{
	case 1:
		cout << "Buy A Book: " << endl;
		string title;
		cout << "Enter the title of the book you want to buy: ";
		cin >> title;
		Book* book = searchForBook(title);
		if (book != nullptr) customer->buyBook(*book);
		break;
	case 2:
		cout << "Borrow A Book: " << endl;
		cout << "Enter the title of the book you want to borrow: ";
		cin >> title;
		book = searchForBook(title);
		if (book != nullptr) customer->borrowBook(*book);
		break;
	case 3:
		cout << "Search For A Book: " << endl;
		cout << "Enter the title of the book you want to search for: ";
		cin >> title;
		book = customer->searchForBook(title);
		if (book != nullptr) cout << book->getTitle() << endl;
		break;
	case 4:
		cout << "Return A Book: " << endl;
		cout << "Enter the title of the book you want to return: ";
		cin >> title;
		book = customer->searchForBook(title);
		if (book != nullptr) customer->returnBook(*book);
		break;
	case 5:
		cout << "Choose Payment Method: " << endl;
		customer->choosePaymentMethod();
		break;
	case 6:
	default:
		currentUser = typNone;
		getChoice(personTypeScreen);
		break;
	}
}

void Library::librarianOptionsHdlr(int choice)
{
	system("CLS");
	string bookName;
	Book* book;
	int newStock;
	int id;
	string returnDate;
	string payment;
	switch (choice)
	{
	case 1:
		book = new Book();
		activeLibrarian->AddBook(book);
		break;
	case 2:
		cout << "Delete a book" << endl;
		bookName = enterBookName();
		activeLibrarian->DeleteBook(bookName);
		break;
	case 3:
		cout << "Update Book Stock" << endl;
		bookName = enterBookName();
		cout << "Enter stock to be added to the currect stock";
		cin >> newStock;
		activeLibrarian->UpdateBook(bookName, newStock);
		break;
	case 4:
		cout << "Lend a book to customer" << endl;
		bookName = enterBookName();
		cout << "Enter cutomer ID: ";
		cin >> id;
		activeLibrarian->lendBook(bookName, getDate(), static_cast<Customer*>(customers.persons.at(id)));
		break;
	case 5:

		break;
	case 6:
		cout << "Add new payment method" << endl;
		cout << "===============================================" << endl;
		cout << "Enter new payment method: ";
		cin >> payment;
		activeLibrarian->AddPaymentMethod(payment);
		break;
	case 7:
		getChoice(reports);
		break;
	case 8:

	default:
		currentUser = typNone;
		getChoice(personTypeScreen);
		break;
	}
}

void Library::reportScreenHdlr(int choice)
{
	string date;
	string author;
	switch (choice)
	{
	case 1:
	case 2:
	case 3:
	case 6:
		activeLibrarian->generateReport(choice, customers.persons, tm());
		break;
	case 4:
		cout << "Enter Current Date: ";
		cin >> date;
		activeLibrarian->generateReport(choice, customers.persons, getDate());
		break;
	case 5:
		cout << "Enter Author Name: ";
		cin >> author;
		activeLibrarian->generateReport(choice, customers.persons, tm(), author);
		break;
	case 7:
	default:
		getChoice(librarianOptions);
		break;
	}
}

tm Library::getDate()
{
	tm date;
	cout << "Enter return date: " << endl;
	cout << "Day: ";
	cin >> date.tm_mday;
	cout << "Month: ";
	cin >> date.tm_mon;
	cout << "Year: ";
	cin >> date.tm_year;
	return date;
}

void Library::loginScreen()
{
	system("CLS");
	cout << "Login: " << endl;
	cout << "==========================" << endl;
	int id{};
	int password{};
	cout << "ID: ";
	cin >> id;
	cout << "Password: ";
	cin >> password;

	// validate to login
	if (currentUser == typLibrarian) {
		activeUser = (librarians.login(id, password));
		activeLibrarian = static_cast<Librarian*> (activeUser);
	}

	else if (currentUser == typCustomer) {
		activeUser = customers.login(id, password);
		activeCustomer = static_cast<Customer*> (activeUser);
	}

	else {
		// error
		exit(1);
	}
	if (currentUser == typLibrarian)
		getChoice(librarianOptions);
	else if (currentUser == typCustomer)
		getChoice(customerOptions);
	else
		getChoice(personTypeScreen);
}

void Library::registerScreen()
{
	system("CLS");
	cout << "Registeration: " << endl;
	cout << "==========================" << endl;
	int id{};
	int password{};
	string name;
	cout << "ID: ";
	cin >> id;
	cout << "Password: ";
	cin >> password;
	cout << "Name: ";
	cin >> name;


	// create new object
	if (currentUser == typLibrarian) {
		activeUser = librarians.registeration(id, password, name);
	}

	else if (currentUser == typCustomer) {
		activeUser = customers.registeration(id, password, name);
	}

	else {
		// error
		exit(1);
	}

	if (activeUser)
		loginScreen();
	else
		getChoice(personTypeScreen);
}

string Library::enterBookName()
{
	cout << "==========================" << endl;
	cout << "Enter Book Name: ";
	string bookName;
	cin >> bookName;

	return bookName;
}


vector<string> Library::paymentMethods = {};
unordered_map<string, Book*> Library::booksList = { };
vector<borrowedBook*> Library::borrowedBookList = {  };
vector<string> Library::categoryList = {  };
