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


void Library::buyBookHdlr() {
	cout << "Buy A Book: " << endl;
	displayBookList();
	string title = enterBookName();
	if (validateBookExists(title)) {
		activeCustomer->buyBook(activeCustomer->searchBook(title, this->booksList), this->paymentMethods);
	}
}

void Library::borrowBookHdlr() {
	cout << "Borrow A Book: " << endl;
	displayBookList();
	string title = enterBookName();
	if (validateBookExists(title)) {
		activeCustomer->borrowBook(activeCustomer->searchBook(title, this->booksList), this->paymentMethods);
	}
}

void Library::searchForBookHdlrC() {
	cout << "Search For A Book: " << endl;
	displayBookList();
	string title = enterBookName();
	Book* book = activeCustomer->searchBook(title, this->booksList);
	if (validateBookExists(title)) {
		book->displayInfo();
	}
}

void Library::returnBookHdlr() {
	cout << "Return A Book: " << endl;
	if (activeCustomer->displayBorrowedBooks()) {
		string title = enterBookName();
		if (validateBookExists(title)) {
			activeCustomer->returnBook(activeCustomer->searchBook(title, this->booksList), this->paymentMethods);
		}
	}
	else {
		cout << "You don't have any borrowed books" << endl;
	}
}

void Library::displayMessageHdlr() {
	activeCustomer->displayMessage();
}

void Library::customerOptionsHdlr(int choice) {
	system("CLS");
	switch (choice) {
	case 1: buyBookHdlr(); break;
	case 2: borrowBookHdlr(); break;
	case 3: searchForBookHdlr(); break;
	case 4: returnBookHdlr(); break;
	case 5: displayMessageHdlr(); break;
	case 6:
	default:
		currentUser = typNone;
		activeCustomer = nullptr; activeLibrarian = nullptr; activeUser = nullptr;
		getChoice(personTypeScreen);
		break;
	}
	continueProgram();
}


void Library::addBookHdlr() {
	Book* book = new Book(this->booksList, this->categoryList);
	activeLibrarian->AddBook(book, this->booksList);
}

void Library::deleteBookHdlr() {
	cout << "Delete a book" << endl;
	displayBookList();
	string bookName = enterBookName();
	if (validateBookExists(bookName)) {
		activeLibrarian->DeleteBook(bookName, this->booksList);
	}
}

void Library::updateBookHdlr() {
	cout << "Update Book Stock" << endl;
	displayBookList();
	string bookName = enterBookName();
	if (validateBookExists(bookName)) {
		cout << "Enter stock to be added to the currect stock: ";
		int newStock = Library::getValidInt();
		activeLibrarian->UpdateBook(bookName, newStock, this->booksList);
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
		activeLibrarian->lendBook(bookName, Date(), static_cast<Customer*>(customers.persons.at(id)), this->booksList, this->paymentMethods);
	}
}

void Library::requestBorrowedBookHdlr() {
	activeLibrarian->requestBorrowedBook(Date());
}

void Library::searchForBookHdlr() {
	cout << "Search For A Book: " << endl;
	displayBookList();
	string title = enterBookName();
	Book* book = activeLibrarian->searchBook(title, this->booksList);
	if (book != nullptr) book->displayInfo();
	else cout << "Book not found" << endl;
}

void Library::addPaymentMethodHdlr() {
	cout << "Add new payment method" << endl;
	cout << "===============================================" << endl;
	string payment;
	cout << "Enter new payment method: ";
	getline(cin >> ws, payment);
	if (validatePaymentMethodExists(payment)) {
		activeLibrarian->AddPaymentMethod(payment, this->paymentMethods);
		cout << "New payment method added" << endl;
	}
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
	case 5:
		cout << "Enter Author Name: " << endl;
		getline(cin >> ws, author);
		cout << endl;
	case 1:
	case 2:
	case 3:
	case 4:
	case 6:
		activeLibrarian->generateReport(choice, customers.persons, author, this->booksList, this->categoryList);
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
    _getch();
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


void Library::displayBookList() {
	cout << "Available books" << endl;
	cout << "===============================" << endl;
	for (auto& it : Library::booksList)
	{
		cout << it.second->getId() << ") " << it.first << endl;
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


vector<borrowedBook*> Library::borrowedBookList = {};

