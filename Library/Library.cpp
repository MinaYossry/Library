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
		displayBookList();
		title = enterBookName();
		book = activeCustomer->searchBook(title);
		if (book != nullptr) activeCustomer->buyBook(book);
		else cout << "Book not found" << endl;
		continueProgram();
		break;
	case 2:
		cout << "Borrow A Book: " << endl;
		displayBookList();
		title = enterBookName();
		book = activeCustomer->searchBook(title);
		if (book != nullptr) activeCustomer->borrowBook(book);
		else cout << "Book not found" << endl;
		continueProgram();
		break;
	case 3:
		cout << "Search For A Book: " << endl;
		displayBookList();
		title = enterBookName();
		book = activeCustomer->searchBook(title);
		if (book != nullptr) book->displayInfo();
		else cout << "Book not found" << endl;
		continueProgram();
		break;
	case 4:
		cout << "Return A Book: " << endl;
		if (activeCustomer->displayBorrowedBooks())
		{
			title = enterBookName();
			book = activeCustomer->searchBook(title);
			if (book != nullptr) activeCustomer->returnBook(book);
			else cout << "Book not found" << endl;
		}
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

void Library::addBookHdlr() {
	Book* book = new Book();
	activeLibrarian->AddBook(book);
}

void Library::deleteBookHdlr() {
	cout << "Delete a book" << endl;
	displayBookList();
	string bookName = enterBookName();
	if (validateBookExists(bookName)) {
		activeLibrarian->DeleteBook(bookName);
	}
}

void Library::updateBookHdlr() {
	cout << "Update Book Stock" << endl;
	displayBookList();
	string bookName = enterBookName();
	if (validateBookExists(bookName)) {
		cout << "Enter stock to be added to the currect stock: ";
		int newStock = Library::getValidInt();
		activeLibrarian->UpdateBook(bookName, newStock);
	}
}

void Library::lendBookHdlr() {
	cout << "Lend a book to customer" << endl;
	displayBookList();
	string bookName = enterBookName();
	if (validateBookExists(bookName)) {
		int id;
		do {
			cout << "Enter cutomer ID: ";
			id = Library::getValidInt();
		} while (customers.persons.find(id) == customers.persons.end());
		activeLibrarian->lendBook(bookName, Date(), static_cast<Customer*>(customers.persons.at(id)));
	}
}

void Library::requestBorrowedBookHdlr() {
	activeLibrarian->requestBorrowedBook(Date());
}

void Library::searchForBookHdlr() {
	cout << "Search For A Book: " << endl;
	displayBookList();
	string title = enterBookName();
	Book* book = activeLibrarian->searchBook(title);
	if (book != nullptr) book->displayInfo();
	else cout << "Book not found" << endl;
}

void Library::addPaymentMethodHdlr() {
	cout << "Add new payment method" << endl;
	cout << "===============================================" << endl;
	string payment;
	do {
		cout << "Enter new payment method: ";
		getline(cin >> ws, payment);
	} while (!validatePaymentMethodExists(payment));
	activeLibrarian->AddPaymentMethod(payment);
}

void Library::generateReportHdlr() {
	getChoice(reports);
}

void Library::librarianOptionsHdlr(int choice) {
	system("CLS");
	switch (choice) {
	case 1: addBookHdlr(); break;
	case 2: deleteBookHdlr(); break;
	case 3: updateBookHdlr(); break;
	case 4: lendBookHdlr(); break;
	case 5: requestBorrowedBookHdlr(); break;
	case 6: searchForBookHdlr(); break;
	case 7: addPaymentMethodHdlr(); break;
	case 8: generateReportHdlr(); break;
	case 9:
	default:
		currentUser = typNone;
		activeCustomer = nullptr; activeLibrarian = nullptr; activeUser = nullptr;
		getChoice(personTypeScreen);
		break;
	}
	continueProgram();
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
		activeLibrarian->generateReport(choice, customers.persons);
		break;
	case 4:
		activeLibrarian->generateReport(choice, customers.persons);
		break;
	case 5:
		cout << "Enter Author Name: " << endl;
		getline(cin >> ws, author);
		cout << endl;
		activeLibrarian->generateReport(choice, customers.persons, author);
		break;
	case 7:
	default:
		getChoice(librarianOptions);
		break;
	}
}

void Library::continueProgram()
{
	cout << "Press any key to continue" << endl;
    cin.get();
	if (currentUser == typCustomer)
		getChoice(customerOptions);
	else if (currentUser == typLibrarian)
		getChoice(librarianOptions);
	else
		exit(1); //error
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
		cin.get();
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
		cin.get();
		getChoice(personTypeScreen);
	}
}


void Library::displayBookList() {
	int counter = 0;
	cout << "Available books" << endl;
	cout << "===============================" << endl;
	for (auto& it : Library::booksList)
	{
		cout << ++counter << ") " << it.first << endl;
	}
	cout << "==========================" << endl;
}

string Library::enterBookName()
{
	
	cout << "Enter Book Name: ";
	string bookName;
	getline(cin >> ws, bookName);

	return bookName;
}

bool Library::validateBookExists(const std::string& bookName) {
	if (Library::booksList.find(bookName) != Library::booksList.end())
	{
		return true;
	}
	else {
		cout << "Book doesn't exist" << endl;
		return false;
	}
}

bool Library::validateCustomerExists(int id) {
	if (customers.persons.find(id) != customers.persons.end()) {
		return true;
	}
	else {
		cout << "Customer doesn't exist" << endl;
		return false;
	}
}

bool Library::validatePaymentMethodExists(const std::string& payment) {
	if (std::find(paymentMethods.begin(), paymentMethods.end(), payment) != paymentMethods.end()) {
		cout << "Payment method already exists" << endl;
		return false;
	}
	else {
		return true;
	}
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

