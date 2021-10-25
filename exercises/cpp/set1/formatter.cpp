#include <string>
#include <iostream>

int process_line(std::string line, int threshold);

int main(int argc, char** argv) {
	int threshold = std::stoi(argv[1]);

	for(std::string line; std::getline(std::cin,line);) {
		if (line.length() < threshold) std::cout << line << std::endl;
		else {
			if (process_line(line, threshold) == -1) return 1;	
		}
	}
}

int process_line(std::string line, int threshold) {
	int i;
        for (i = threshold - 1; i > -1 && line[i] != ' ' && line[i] != '\n'; i--) {}
        if (i == -1) return -1;
	
	std::cout << line.substr(0, i) << std::endl;

	int n_of_sublines = process_line(line.substr(i+1), threshold);
	if (n_of_sublines == -1) return -1;
	else return n_of_sublines + 1;
}
