#ifndef PERSON_MANAGER_H
#define PERSON_MANAGER_H

#include <unordered_map>
#include <vector>

#include "Person.h"
#include "Customer.h"
#include "Librarian.h"

using namespace std;

enum personTypes
{
	typLibrarian,
	typCustomer,
	typNone
};

class PersonsManager
{
public:
	unordered_map<int, Person*> persons;

	personTypes type;
	PersonsManager(personTypes _type) : type{ _type } {}

	bool validateLoginCred(int _ID, int _password);
	Person* login(int _ID, int _password);
	Person* registeration(int _ID, int _password, const std::string& _name);
};

#endif