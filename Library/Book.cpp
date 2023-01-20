#include "Book.h"
#include "Library.h"

Book::Book()
{
	cout << "Adding new book" << endl;
	cout << "=================================================================" << endl;
	cout << "ID: ";
	cin >> id;
	cout << "Name: ";
	cin >> title;
	cout << "Price: ";
	cin >> price;
	cout << "Author: ";
	cin >> author;
	isAvailable = true;
	cout << "Category: ";
	cin >> category;
	Library::categoryList.insert(category);
	cout << "Stock: ";
	cin >> stock;
}

Book::Book(int _id, string _title, string _author, int _publicationYear, double _price, int _stock, string _category)
{
	id = _id;
	title = _title;
	price = _price;
	author = _author;
	isAvailable = true;
	category = _category;
	stock = _stock;
	publicationYear = _publicationYear;
	Library::categoryList.insert(_category);
}

void Book::setStock(int value)
{
	this->stock += value;
	if (stock == 0)
		isAvailable = false;
	else
		isAvailable = true;

}
int Book::getStock() const
{
	return stock;
}
void Book::displayInfo() const
{

	system("CLS");
	cout << "====================================================" << endl;
	cout << "Title: " << title << endl;
	cout << "Author: " << author << endl;
	cout << "Publication Year: " << publicationYear << endl;
	cout << "Price: " << price << endl;
	cout << "Category: " << category << endl;
	cout << "====================================================" << endl;
}
string Book::getCategory() {
	return this->category;
}

int Book::getId() const { return id; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
int Book::getPublicationYear() const { return publicationYear; }
bool Book::getIsAvailable() const { return isAvailable; }
double Book::getPrice() const { return price; }

void Book::setAvailability(bool isAvailable) { this->isAvailable = isAvailable; }