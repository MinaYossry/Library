#include "Book.h"

Book::Book()
{
	cout << "Adding new book" << endl;
	cout << "=================================================================" << endl;
	cout << "ID: ";
	cin >> id;
	cout << "Name: ";
	cin >> name;
	cout << "Price: ";
	cin >> price;
	cout << "Author: ";
	cin >> author;
	status = true;
	cout << "Category: ";
	cin >> category;
	cout << "Edition: ";
	cin >> edition;
	cout << "Stock: ";
	cin >> stock;
}

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
string Book::getCategory() {
	return this->category;
}
string Book::getAuthor() {
	return this->author;
}


Book::Book(int id, string title, string author, string publisher, int publicationYear, double price)
    : id(id), title(title), author(author), publisher(publisher), publicationYear(publicationYear), price(price)
{
    isAvailable = true;
}

int Book::getId() const { return id; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getPublisher() const { return publisher; }
int Book::getPublicationYear() const { return publicationYear; }
bool Book::getIsAvailable() const { return isAvailable; }
double Book::getPrice() const { return price; }
vector<Book>& Book::getCollection() {
    return collection;
}
void Book::setAvailability(bool isAvailable) { this->isAvailable = isAvailable; }