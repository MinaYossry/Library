#pragma once
#include <vector>


#include <string>
#include <iostream>

#include<unordered_map>
using namespace std;
class Book
{
private:
	//Book data
	string category;
	int stock;

    int id;
    string title;
    string author;
    int publicationYear;
    bool isAvailable;
    double price;

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
	Book();
	string getCategory();
	void setStock(int value);
};
