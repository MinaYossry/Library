#include "Person.h"
#include "Book.h"

Person::Person(int _ID, int _password, string _name)
	: ID (_ID), password {_password}, name {_name}
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
	if (Book::booksList.find(name) != Book::booksList.end())
	{
		return Book::booksList.at(name);
	}
	return nullptr;
}
