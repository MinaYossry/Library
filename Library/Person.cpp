#include "Person.h"
#include "Book.h"
#include "Library.h"
Person::Person(int _ID, int _password, string _name)
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