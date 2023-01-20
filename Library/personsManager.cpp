#include "PersonsManager.h"

bool PersonsManager::validateLoginCred(int _ID, int _password)
{   
    /*  This function checks if the    */
    return PersonsManager::persons.find(_ID) != PersonsManager::persons.end() && PersonsManager::persons.at(_ID)->getPassword() == _password;
}

Person* PersonsManager::login(int _ID, int _password)
{
    if (validateLoginCred(_ID, _password))
        return PersonsManager::persons.at(_ID);
    else
        return nullptr;
}

Person* PersonsManager::registeration(int _ID, int _password, const std::string& _name)
{
    Person* newPerson{ nullptr };
    if (persons.find(_ID) == persons.end()) {
        if (type == typLibrarian) {
            newPerson = new Librarian(_ID, _name, _password);
        }
        else if (type == typCustomer) {
            newPerson = new Customer(_ID, _name, _password);
        }

        if (newPerson)
            persons[_ID] = newPerson;
    }
    return newPerson;
}