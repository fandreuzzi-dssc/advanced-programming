#include <string>
#include <iostream>

void prnt(std::string line, int repetitions);

int main() {
	std::string previous = "";
	int repetitions = 1;
	std::string line;

	while(std::getline(std::cin,line)) {
		if (previous == "") previous = line;
		else if (previous != line) { prnt(previous, repetitions); previous = line; repetitions = 1; }
		else repetitions++;
	}
	
	prnt(previous, repetitions);
}

void prnt(std::string line, int repetitions) {
	std::cout << repetitions << ") " << line << std::endl; 
}
