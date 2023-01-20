#pragma once
struct Date {
	int day;
	int month;
	int year;
	Date(int _day = 0, int _month = 0, int _year = 0)
		: day{ _day }, month{ _month }, year{ _year } {}
};

