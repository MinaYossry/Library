#ifndef DATE_H
#define DATE_H
#include <iostream>
struct Date {
	int day;
	int month;
	int year;

	Date();

	Date(int _day, int _month, int _year);

	bool operator > (const Date& other) const;

	bool operator < (const Date& other) const;

	friend std::ostream& operator<<(std::ostream& out, const Date& date);
};

#endif