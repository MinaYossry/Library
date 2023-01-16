#pragma once
#include <string>
using namespace std;

class Person
{
protected:
	string name;
	int ID;
	int password;

public:
	Person(int _ID, int _password, string _name);
	int getPassword() const;
	int getID() const;
	string getName() const;
};

