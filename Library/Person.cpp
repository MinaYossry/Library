#include "Person.h"
#include "Book.h"
#include "Library.h"
Person::Person(int _ID, string _name, int _password)
	: ID(_ID), password{ _password }, name{ _name }
{
}

int Person::getPassword() const
{
	return this->password;
}

int Person::getID() const
{
	return this->ID;
}

string Person::getName() const
{
	return this->name;
}

Book* Person::searchBook(string name)
{
	if (Library::booksList.find(name) != Library::booksList.end())
	{
		return Library::booksList.at(name);
	}
	return nullptr;
}

bool Person::compareDates(const tm& currentDate, const tm& returnDate)
{
	return currentDate.tm_year > returnDate.tm_year || (currentDate.tm_year > returnDate.tm_year == currentDate.tm_mon > returnDate.tm_mon)
		|| (currentDate.tm_year == returnDate.tm_year && currentDate.tm_mon == returnDate.tm_mon && currentDate.tm_mday > returnDate.tm_mday);
}