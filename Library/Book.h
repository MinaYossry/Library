#pragma once
#include <string>
#include <iostream>

#include<unordered_map>
using namespace std;
class Book
{
private:
	//Book data
	int id;
	string  name;
	float price;
	string author;
	bool status;
	string category;
	string edition;
	int stock;

public:
	//Book methods
	//typedef unordered_map<string, Book*> bookList;
	//static bookList booksList;

	Book();
	Book(int _id, string _name, float _price, string _author, bool _status, string _category, string _edition, int _stock);
	string getName();
	string getCategory();
	string getAuthor();
	void setStock(int value);
};
