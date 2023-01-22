#ifndef BOOK_H
#define BOOK_H

#include <vector>
#include <unordered_set>

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
	Book(const unordered_map<string, Book*>& booksList, unordered_set<string>& categoryList);
    Book(int _id, string _title, string _author, int _publicationYear, double _price, int _stock, string _category, unordered_set<string>& categoryList);

    int getId() const;
    string getTitle() const;
    string getAuthor() const;
    int getPublicationYear() const;
    bool getIsAvailable() const;
    double getPrice() const;
    void setAvailability(bool isAvailable);
	string getCategory();
    void setStock(int value);
    int getStock() const;
    void displayInfo() const;
    bool isUnique(int _id, const unordered_map<string, Book*>& booksList) const;
};

#endif