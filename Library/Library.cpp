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
		choice = Library::getValidInt();
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
	string title;
	Book* book;
	system("CLS");
	switch (choice)
	{
	case 1:
		cout << "Buy A Book: " << endl;
		title = enterBookName();
		book = activeCustomer->searchBook(title);
		if (book != nullptr) activeCustomer->buyBook(book);
		else cout << "Book not found" << endl;
		continueProgram();
		break;
	case 2:
		cout << "Borrow A Book: " << endl;
		title = enterBookName();
		book = activeCustomer->searchBook(title);
		if (book != nullptr) activeCustomer->borrowBook(book);
		else cout << "Book not found" << endl;
		continueProgram();
		break;
	case 3:
		cout << "Search For A Book: " << endl;
		title = enterBookName();
		book = activeCustomer->searchBook(title);
		if (book != nullptr) book->displayInfo();
		else cout << "Book not found" << endl;
		continueProgram();
		break;
	case 4:
		cout << "Return A Book: " << endl;
		title = enterBookName();
		book = activeCustomer->searchBook(title);
		if (book != nullptr) activeCustomer->returnBook(book);
		else cout << "Book not found" << endl;
		continueProgram();
		break;
	case 5:
		activeCustomer->displayMessage();
		continueProgram();
		break;
	case 6:
	default:
		currentUser = typNone;
		activeCustomer = nullptr; activeLibrarian = nullptr; activeUser = nullptr;
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
		continueProgram();
		break;
	case 2:
		cout << "Delete a book" << endl;
		bookName = enterBookName();
		activeLibrarian->DeleteBook(bookName);
		continueProgram();
		break;
	case 3:
		cout << "Update Book Stock" << endl;
		bookName = enterBookName();
		cout << "Enter stock to be added to the currect stock: ";
		newStock = Library::getValidInt();
		activeLibrarian->UpdateBook(bookName, newStock);
		continueProgram();
		break;
	case 4:
		cout << "Lend a book to customer" << endl;
		bookName = enterBookName();
		do {
			cout << "Enter cutomer ID: ";
			id = Library::getValidInt();
		} while (customers.persons.find(id) == customers.persons.end());
		activeLibrarian->lendBook(bookName, getDate(), static_cast<Customer*>(customers.persons.at(id)));
		continueProgram();
		break;
	case 5:
		activeLibrarian->requestBorrowedBook(getDate());
		continueProgram();
		break;
	case 6:
		cout << "Add new payment method" << endl;
		cout << "===============================================" << endl;
		do {
			cout << "Enter new payment method: ";
			getline(cin >> ws, payment);
		} while (find(paymentMethods.begin(), paymentMethods.end(), payment) != paymentMethods.end());
		activeLibrarian->AddPaymentMethod(payment);
		continueProgram();
		break;
	case 7:
		getChoice(reports);
		continueProgram();
		break;
	case 8:
	default:
		currentUser = typNone;
		activeCustomer = nullptr; activeLibrarian = nullptr; activeUser = nullptr;
		getChoice(personTypeScreen);
		break;
	}
}

void Library::reportScreenHdlr(int choice)
{
	string author;
	switch (choice)
	{
	case 1:
	case 2:
	case 3:
	case 6:
		activeLibrarian->generateReport(choice, customers.persons, Date());
		break;
	case 4:
		activeLibrarian->generateReport(choice, customers.persons, getDate());
		break;
	case 5:
		cout << "Enter Author Name: " << endl;
		getline(cin >> ws, author);
		cout << endl;
		activeLibrarian->generateReport(choice, customers.persons, Date(), author);
		break;
	case 7:
	default:
		getChoice(librarianOptions);
		break;
	}
}

void Library::continueProgram()
{
	cout << "\nContinue....." << endl;
	_getch();
	if (currentUser == typCustomer)
		getChoice(customerOptions);
	else if (currentUser == typLibrarian)
		getChoice(librarianOptions);
	else
		exit(1); //error
}

Date Library::getDate()
{
	Date date;
	cout << "Enter date: " << endl;
	do {
		cout << "Day: ";
		date.day = Library::getValidInt();
	} while (date.day < 1 || date.day > 31);
	do {

		cout << "Month: ";
		date.month = Library::getValidInt();
	} while (date.month < 1 || date.month > 12);
	do {

		cout << "Year: ";
		date.year = Library::getValidInt();
	} while (date.year < 2000 || date.year > 2025);
	return date;
}

int Library::getValidInt()
{
	int output{};
	cin >> output;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Please enter an integer: ";
		cin >> output;
	}
	return output;
}

double Library::getValidDouble()
{
	double output{};
	cin >> output;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a double: ";
		cin >> output;
	}
	return output;
}

void Library::loginScreen()
{
	system("CLS");
	cout << "Login: " << endl;
	cout << "==========================" << endl;
	int id{};
	int password{};
	cout << "ID: ";
	id = Library::getValidInt();
	cout << "Password: ";
	password = Library::getValidInt();

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
	if (activeLibrarian)
		getChoice(librarianOptions);
	else if (activeCustomer)
		getChoice(customerOptions);
	else
	{
		cout << "Sorry, user doesn't exist" << endl;
		_getch();
		getChoice(personTypeScreen);
	}
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
	id = Library::getValidInt();
	cout << "Password: ";
	password = Library::getValidInt();;
	cout << "Name: ";
	getline(cin >> ws, name);


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
	else {
		cout << "Sorry user already exists" << endl;
		_getch();
		getChoice(personTypeScreen);
	}
}

string Library::enterBookName()
{
	int counter = 0;
	cout << "Available books"<< endl;
	cout << "===============================" << endl;
	for (auto& it : Library::booksList)
	{
		cout << ++counter << ") " << it.first << endl;
	}
	cout << "==========================" << endl;
	cout << "Enter Book Name: ";
	string bookName;
	getline(cin >> ws, bookName);

	return bookName;
}


vector<string> Library::paymentMethods = {
	"Cash",
	"Debit Card",
	"Credit Card"
};

vector<borrowedBook*> Library::borrowedBookList = {  };
unordered_set<string> Library::categoryList = {  };

unordered_map<string, Book*> Library::booksList{
	{"Harry Potter and the Philosopher's Stone" ,new Book(1, "Harry Potter and the Philosopher's Stone", "J.K. Rowling", 1997, 12.99, 1000, "Fantasy")},
	{"To Kill a Mockingbird" ,new Book(2, "To Kill a Mockingbird", "Harper Lee", 1960, 14.99, 800, "Classics")},
	{"The Catcher in the Rye" ,new Book(3, "The Catcher in the Rye", "J.D. Salinger", 1951, 10.99, 500, "Classics")},
	{"The Lord of the Rings" ,new Book(4, "The Lord of the Rings", "J.R.R. Tolkien", 1954, 24.99, 1200, "Fantasy")},
	{"The Great Gatsby" ,new Book(5, "The Great Gatsby", "F. Scott Fitzgerald", 1925, 8.99, 900, "Classics")},
	{"The Alchemist" ,new Book(6, "The Alchemist", "Paulo Coelho", 1988, 15.99, 800, "Self-Help")},
	{"The Hobbit" ,new Book(7, "The Hobbit", "J.R.R. Tolkien", 1937, 19.99, 1000, "Fantasy")},
	{"The Diary of a Young Girl" ,new Book(8, "The Diary of a Young Girl", "Anne Frank", 1947, 9.99, 600, "Non-Fiction")},
	{"The Da Vinci Code" ,new Book(9, "The Da Vinci Code", "Dan Brown", 2003, 16.99, 1000, "Thriller")},
	{"1984" ,new Book(10, "1984", "George Orwell", 1949, 12.99, 700, "Classics")},
};

