#pragma once
#include <unordered_map>
#include "Person.h"

class Customer : public Person
{
public:
	Customer(int _ID, int _password, string _name);
};

