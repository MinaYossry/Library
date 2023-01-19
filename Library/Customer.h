#pragma once
#include <unordered_map>
#include "Person.h"
#include "Book.h"
#include <string>
struct borrowedBook
{
public:
	Book* book;
	string returnDate;
};
class Customer : public Person
{
public:
	Customer(int _ID, int _password, string _name);
	vector<borrowedBook*> borrowedBookList;
	vector<string> NotificationList;
};

