#pragma once
#include <string>
#include <vector>

using namespace std;

class Book
{
private:
    int id;
    string title;
    string author;
    string publisher;
    int publicationYear;
    bool isAvailable;
    double price;
    static vector<Book> collection;

public:
    Book(int id, string title, string author, string publisher, int publicationYear, double price);

    int getId() const;
    string getTitle() const;
    string getAuthor() const;
    string getPublisher() const;
    int getPublicationYear() const;
    bool getIsAvailable() const;
    double getPrice() const;
    static vector<Book>& getCollection();
    void setAvailability(bool isAvailable);
};