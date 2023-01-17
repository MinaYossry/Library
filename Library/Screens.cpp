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
}

int Screens::getChoice(const vector<string>& screen)
{
	int c{};
	do {
		displayScreen(screen);
		cout << "Choice: ";
		cin >> c;
	} while (c < 1 || c > screen.size() + 1);

	if (screen == personTypeScreen) {
		switch (c)
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
			getChoice(personTypeScreen);
			break;
		}
	}
	return c;
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
			getChoice(librarianOptions);
		else
			getChoice(personTypeScreen);
	}

	else if (currentUser == typCustomer) {
		activeUser = customers.login(id, password);
		if (activeUser) {
			getChoice(customerOptions);
		}
		else
			getChoice(personTypeScreen);
	}

	else {
		// error
		exit(1);
	}
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
		activeUser = librarians.registeration(id, password, name); 
		if (activeUser)
			loginScreen();
		else
			getChoice(personTypeScreen);
	}
	else if (currentUser == typCustomer) {
		activeUser = customers.registeration(id, password, name); 
		if (activeUser)
			loginScreen();
		else
			getChoice(personTypeScreen);
	}
	else {
		// error
		exit(1);
	}
}
