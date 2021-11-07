#include <iostream>

enum class Month { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

class Date {
	Month _month;
	int _day;
	int _year;

	// used to store the number of months to be added
	int _temp_month = 0;
public:
	Date(int d, Month m, int y) {
		_day = d;
		_month = m;
		_year = y;
		wrap();
	}

	int year() const { return _year; }
	int day() const { return _day; }
	Month month() const { return _month; }

	void add_days(const unsigned int n) { add(n,0,0); }
	void add_months(const unsigned int n) { add(0,n,0); }
	void add_years(const unsigned int n) { add(0,0,n); }

	Month set_next_month() {
		int nm = static_cast<int>(_month) % 12 + 1;
		if (nm == 12) _year += 1;
		return static_cast<Month>(nm);
	}

	void add(const unsigned int d, const unsigned int m, const unsigned int y) { _day += d; _temp_month = m; _year += y; wrap(); }
	void wrap();

	void print() const { std::cout << "Date(" << _day << "/" << static_cast<int>(_month)+1 << "/" << _year << ")" << std::endl; }
};

int n_of_days(Month m) {
	// unfortunately this doesn't work...
	// using namespace Month;
	switch(m) {
		case Month::feb : return 28;
		case Month::nov : case Month::apr : case Month::jun : case Month::sep : return 30;
		default: return 31;
	}
}

void Date::wrap() {
	int days_in_month;
	while (_day > (days_in_month=n_of_days(_month))) {
		_day -= days_in_month;
		_month = set_next_month();
	}
	while(_temp_month-- > 0) _month = set_next_month();
}

int main() {
	Date d(12, Month::dec, 1999);
	d.print();

	std::cout << std::endl << "Adding 90 days" << std::endl;
	d.add_days(90);
	d.print();

	std::cout << std::endl << "Adding 25 days and 10 months and 2 years" << std::endl;
	d.add(25, 10, 2);
	d.print();
}
