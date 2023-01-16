#include "personsManager.h"

bool personsManager::validateLoginCred(int _ID, int _password)
{
    return personsManager::persons.find(_ID) != personsManager::persons.end() && personsManager::persons.at(_ID)->getPassword() == _password;
}

Person* personsManager::login(int _ID, int _password)
{
    if (validateLoginCred(_ID, _password))
        return personsManager::persons.at(_ID);
    else
        return nullptr;
}

Person* personsManager::registeration(int _ID, int _password, const std::string& _name)
{
    if (persons.find(_ID) == persons.end()) {
        Person* newPerson{ nullptr };
        if (type == typLibrarian) {

        }
        else if (type == typCustomer) {
            newPerson = new Customer(_ID, _password, _name);
            persons[_ID] = newPerson;
        }
        return newPerson;
    }
    return nullptr;
}
