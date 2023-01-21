#ifndef PERSON_H
#define PERSON_H


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
	Book* searchBook(string name, const unordered_map<string, Book*>& booksList);

	//bool compareDates(const Date& currentDate, const Date& returnDate);

};

#endif