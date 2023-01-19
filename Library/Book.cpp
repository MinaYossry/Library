#include "Book.h"

Book::Book(int _id, string _name, float _price, string _author, bool _status, string _category, string _edition, int _stock)
{
	id = _id;
	name = _name;
	price = _price;
	author = _author;
	status = _status;
	category = _category;
	edition = _edition;
	stock = _stock;
}
string Book::getName() {
	return this->name;
}
void Book::setStock(int value)
{
	this->stock += value;
}

 unordered_map<string,Book*> Book::booksList = { {"",nullptr} };