#include "Date.h"
#include "Library.h"

Date::Date()
{
	cout << "Enter date: " << endl;
	do {
		cout << "Day: ";
		day = Library::getValidInt();
	} while (day < 1 || day > 31);
	do {

		cout << "Month: ";
		month = Library::getValidInt();
	} while (month < 1 || month > 12);
	do {

		cout << "Year: ";
		year = Library::getValidInt();
	} while (year < 2000 || year > 2025);
}


Date::Date(int _day, int _month, int _year)
	: day{ _day }, month{ _month }, year{ _year } {}

bool Date::operator>(const Date& other) const
{
    if (year > other.year) {
        return true;
    }
    else if (year == other.year) {
        if (month > other.month) {
            return true;
        }
        else if (month == other.month) {
            return day > other.day;
        }
    }
    return false;
}

bool Date::operator<(const Date& other) const
{
    if (year < other.year) {
        return true;
    }
    else if (year == other.year) {
        if (month < other.month) {
            return true;
        }
        else if (month == other.month) {
            return day < other.day;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, const Date& date)
{
	out << date.day << "/" << date.month << "/" << date.year;
	return out;
}
