#include "Book.h"

vector<Book> Book::collection;

Book::Book(int id, string title, string author, string publisher, int publicationYear, double price)
    : id(id), title(title), author(author), publisher(publisher), publicationYear(publicationYear), price(price)
{
    isAvailable = true;
    collection.push_back(*this);
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