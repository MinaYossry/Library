#pragma once
#include <unordered_map>
#include "Person.h"
#include "Book.h"
#include <string>

class Customer : public Person
{
public:
	Customer(int _ID, int _password, string _name);
	
	vector<string> NotificationList;
};

