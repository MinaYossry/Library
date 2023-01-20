#pragma once
#include <string>
#include "Book.h"
#include "Date.h"


using namespace std;

class Person
{
protected:
	string name;
	int ID;
	int password;

public:
	Person(int _ID, string _name, int _password);
	int getPassword() const;
	int getID() const;
	string getName() const;
	Book* searchBook(string name);

	bool compareDates(const Date& currentDate, const Date& returnDate);

};
