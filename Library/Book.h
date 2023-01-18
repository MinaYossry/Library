#pragma once
#include <unordered_map>
#include <string>

using namespace std;

class Book
{
private:
	//Book data
public:
	static unordered_map<string, Book*> bookList;
	//Book methods
};

