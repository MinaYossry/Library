#pragma once
#include <unordered_map>
#include <vector>

#include "Person.h"
#include "Customer.h"

using namespace std;

enum personTypes
{
	typLibrarian,
	typCustomer,
	typnone,
};

class personsManager
{
public:
	unordered_map<int, Person*> persons;

	personTypes type;
	personsManager(personTypes _type) : type {_type} {}

	bool validateLoginCred(int _ID, int _password);
	Person* login(int _ID, int _password);
	Person* registeration(int _ID, int _password, const std::string &_name) ;
};

