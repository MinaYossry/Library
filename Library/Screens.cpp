#include "Screens.h"

void Screens::displayScreen(const vector<string>& screen)
{
	system("CLS");
	cout << "=====================================" << endl;
	for (size_t i = 0; i < screen.size(); i++)
	{
		cout << i + 1 << "- " << screen.at(i) << endl;
	}
	cout << screen.size() + 1 << "- exit" << endl;
	cout << "=====================================" << endl;
	getChoice(screen);
}

void Screens::loginScreen()
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
		if (activeUser)
			displayScreen(customerOptions);
		else
			displayScreen(personType);
	}

	else if (currentUser == typCustomer) {
		activeUser = customers.login(id, password);
		if (activeUser) {
			displayScreen(librarianOptions);
		}
		else
			displayScreen(personType);
	}

	else {
		// error
		exit(1);
	}
}

int Screens::getChoice(const vector<string>& screen)
{
	int c{};
	do {
		cout << "Choice: ";
		cin >> c;
	} while (c < 1 || c > screen.size() + 1);

	if (screen == personType) {
		switch (c)
		{
		case 1:
			currentUser = typLibrarian;
			displayScreen(loginOrRegister);
			break;
		case 2:
			currentUser = typCustomer;
			displayScreen(loginOrRegister);
			break;
		case 3:
		default:
			exit(0);
			break;
		}
	}

	else if (screen == loginOrRegister) {
		switch (c)
		{
		case 1:
			loginScreen();
			break;
		case 2:
			registerScreen();
			break;
		case 3:
		default:
			displayScreen(personType);
			break;
		}
	}
	return c;
}

void Screens::registerScreen()
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
		activeUser = librarians.registeration(id, password, name); // true will be replaced by validation function;
		if (activeUser)
			loginScreen();
		else
			displayScreen(personType);
	}
	else if (currentUser == typCustomer) {
		activeUser = customers.registeration(id, password, name); // true will be replaced by validation function;
		if (activeUser)
			loginScreen();
		else
			displayScreen(personType);
	}
	else {
		// error
		exit(1);
	}
}
