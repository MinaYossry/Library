#include "Book.h"
#include "Library.h"

Book::Book(const unordered_map<string, Book*>& booksList, unordered_set<string> &categoryList)
{
	cout << "Adding new book" << endl;
	cout << "=================================================================" << endl;
	cout << "ID: ";
	id = Library::getValidInt();
	while (!isUnique(id, booksList))
	{
		cout << "Please enter unique ID: ";
		id = Library::getValidInt();
	}
	do
	{
		cout << "Name: ";
		getline(cin >> ws, title);
	} while (booksList.find(title) != booksList.end());
	cout << "Price: ";
	price = Library::getValidDouble();
	cout << "Author: ";
	getline(cin >> ws, author);
	cout << "Publication Year: ";
	publicationYear = Library::getValidInt();
	isAvailable = true;
	cout << "Category: ";
	getline(cin >> ws, category);
	categoryList.insert(category);
	cout << "Stock: ";
	stock = Library::getValidInt();;
}

Book::Book(int _id, string _title, string _author, int _publicationYear, double _price, int _stock, string _category, unordered_set<string>& categoryList)
{
	id = _id;
	title = _title;
	price = _price;
	author = _author;
	isAvailable = true;
	category = _category;
	stock = _stock;
	publicationYear = _publicationYear;
	categoryList.insert(_category);
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
bool Book::isUnique(int _id, const unordered_map<string, Book*>& booksList) const
{
	for (const auto& book : booksList)
	{
		if (book.second->getId() == _id)
			return false;
	}
	return true;
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