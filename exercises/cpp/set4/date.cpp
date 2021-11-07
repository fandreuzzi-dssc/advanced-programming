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

	int is_leap() { return _year % 4 == 0 && (_year % 100 != 0 || _year % 400 == 0); }
	int n_of_days(Month m);

	Month set_next_month() {
		int nm = static_cast<int>(_month) % 12 + 1;
		if (nm == 12) { _year += 1; nm = 0; }
		return static_cast<Month>(nm);
	}

	void add(const unsigned int d, const unsigned int m, const unsigned int y) { _day += d; _temp_month = m; _year += y; wrap(); }
	void wrap();
};

int Date::n_of_days(Month m) {
	// unfortunately this doesn't work...
	// using namespace Month;

	switch(m) {
		case Month::feb : return (is_leap() ? 29 : 28);
		case Month::nov : case Month::apr : case Month::jun : case Month::sep : return 30;
		default: return 31;
	}
}

void Date::wrap() {
	while(_temp_month-- > 0) _month = set_next_month();

	int days_in_month;
	while (_day > (days_in_month=n_of_days(_month))) {
		_day -= days_in_month;
		_month = set_next_month();
	}
}

bool operator==(const Date& lhs, const Date& rhs) {
	return lhs.day() == rhs.day() && lhs.month() == rhs.month() && lhs.year() == rhs.year();
}

bool operator!=(const Date& lhs, const Date& rhs) {
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
	os << "Date(" << d.day() << "/" << static_cast<int>(d.month())+1 << "/" << d.year() << ")";
	return os;
}

int main() {
	Date d(12, Month::dec, 1999);
	std::cout << d << std::endl;

	std::cout << "Adding 20 days" << std::endl;
	d.add_days(20);
	Date d1(31, Month::dec, 1999);
	Date d2(1, Month::jan, 2000);
	std::cout << d << " " << (d == d1 ? "==" : "!=") << " " << d1 << ", " << d << " " << (d != d2 ? "!=" : "==") << " " << d2 << std::endl;

	std::cout << std::endl << "Adding 90 days" << std::endl;
	d.add_days(90);
	std::cout << d << std::endl;

	std::cout << std::endl << "Adding 25 days and 10 months and 2 years" << std::endl;
	d.add(25, 10, 2);
	std::cout << d << std::endl;

	// leap
	Date dl(15, Month::feb, 2004);
	std::cout << std::endl << dl << " is " << (dl.is_leap() ? "" : "not ") << "leap" << std::endl;
	dl.add_days(14);

	std::cout << "Adding 14 days" << std::endl;
	std::cout << dl << std::endl;

	std::cout << "Adding 12 months" << std::endl;
	dl.add_months(12);
	std::cout << dl << " is " << (dl.is_leap() ? "" : "not ") << "leap" << std::endl;
}
