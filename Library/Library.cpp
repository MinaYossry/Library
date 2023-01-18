#include "Library.h"

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
	switch (choice)
	{
	case 1:
		cout << "Buy A Book: " << endl;
		searchForBook();
		break;
	case 2:
		cout << "Borrow A Book: " << endl;
		searchForBook();
		break;
	case 3:
		cout << "Search For A Book: " << endl;
		searchForBook();
		break;
	case 4:
		cout << "Return A Book: " << endl;
		searchForBook();
		break;
	case 5:
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
	switch (choice)
	{
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		break;
	case 7:

		break;
	case 8:

	default:
		currentUser = typNone;
		getChoice(personTypeScreen);
		break;
	}
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
		activeUser = librarians.login(id, password);
	}

	else if (currentUser == typCustomer) {
		activeUser = customers.login(id, password);
	}

	else {
		// error
		exit(1);
	}
	if (activeUser)
		getChoice(librarianOptions);
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

Book* Library::searchForBook()
{
	cout << "==========================" << endl;
	cout << "Enter Book Name: ";
	string bookName;
	cin >> bookName;

	// return Book::getBook(bookName);
	return nullptr;
}
