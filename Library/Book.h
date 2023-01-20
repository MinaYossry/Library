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
	Book();
    Book(int _id, string _title, string _author, int _publicationYear, double _price, int _stock, string _category);

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
};
