#include <iostream>

int main() {
	double amount;
	std::string unit;

	std::cin >> amount >> unit;

	if (unit == "in") std::cout << amount * 0.01 * 2.54 << std::endl;
	else if (unit == "m") std::cout << amount * 39.37 << std::endl;
}
