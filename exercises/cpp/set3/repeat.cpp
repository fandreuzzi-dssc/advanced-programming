#include <set>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>

template <typename T>
std::vector<T> unique_withset(std::vector<T> vec);

template <typename T>
std::vector<T> unique_withsort(std::vector<T> vec);

template <typename T>
std::vector<T> unique_withunique(std::vector<T> vec);

template <typename T>
void print(std::vector<T> vec);

int main() {
	std::string line;
	std::vector<std::string> store;

        while(std::getline(std::cin,line)) {
		store.push_back(line);
	}

	std::cout << "Repeating everything: " << std::endl;
	print(store);

	clock_t begin = clock();
	std::vector<std::string> unique = unique_withsort(store);
	clock_t end = clock();

	std::cout << "Without repetitions [sort] (" << double(end - begin)/CLOCKS_PER_SEC << " ms)" << std::endl;
	print(unique);

	//

	begin = clock();
        unique = unique_withunique(store);
	end = clock();

	std::cout << "Without repetitions [unique] (" << double(end - begin)/CLOCKS_PER_SEC << " ms)" << std::endl;
        print(unique);

	//

	begin = clock();
        unique = unique_withset(store);
	end = clock();

	std::cout << "Without repetitions [set] (" << double(end - begin)/CLOCKS_PER_SEC << " ms)" << std::endl;
        print(unique);

	std::cout << "The original vector should not have been modified:" << std::endl;
	print(store);

	return 0;
}

template <typename T>
std::vector<T> unique_withset(std::vector<T> vec) {
	std::set<T> s( vec.begin(), vec.end() );
	std::vector<T> unique;
	unique.assign( s.begin(), s.end() );
	return unique;
}

template <typename T>
std::vector<T> unique_withsort(std::vector<T> vec) {
	std::vector<T> copy = vec;
	std::sort(copy.begin(), copy.end());

	std::vector<T> unique;

	auto current = *copy.begin();
	unique.push_back(current);

	for(auto pt : copy) {
		if (pt != current) {
			current = pt;
			unique.push_back(current);
		}
	}

	return unique;
}

template <typename T>
std::vector<T> unique_withunique(std::vector<T> vec) {
        std::vector<T> copy = vec;
        std::sort(copy.begin(), copy.end());
	auto last = std::unique(copy.begin(), copy.end());
	copy.erase(last, copy.end());
	return copy;
}

template <typename T>
void print(std::vector<T> vec) {
	for(int i = 0; i < vec.size() -1; i++) std::cout << vec.at(i) << ", ";
	std::cout << vec.at(vec.size()-1) << std::endl;
}
