#include <vector>
#include <iostream>
#include <string>

int main() {
	std::vector<double> temperatures;
	for(std::string line; std::getline(std::cin,line);) temperatures.emplace_back(std::stod(line));
	int n = temperatures.size();
	
	//mean
	double sum = 0;
	for(int i = 0; i < n; i++) sum += temperatures.at(i);
	std::cout << "Mean: " << sum / n << std::endl;

	//median
	std::sort( temperatures.begin(), temperatures.end() );
	double median;
	if (n % 2 == 0) {
		median = (temperatures.at((n-1)/2) + temperatures.at((n+1)/2)) / 2;
	} else {
		median = temperatures.at(n/2);
	}
	std::cout << "Median: " << median << std::endl;
}
