#include <map>
#include <unordered_map>
#include <cctype>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
#include <sstream>
#include <iterator>

#define DEBUG 0
#define PRINT_VECTORS 0
#define CMP_DETAILS 0

template <typename T>
struct UniqueStruct {
	std::vector<T> items;
	std::vector<int> count;
};

template <typename T>
int cmp(const UniqueStruct<T>& self, const UniqueStruct<T>& other);

template <typename T>
UniqueStruct<T> unique_withvec(const std::vector<T> *vec);

template <typename T, typename M>
UniqueStruct<T> unique_withmap(const std::vector<T> *vec, M m);

template <typename T>
void print(std::vector<T> vec);

template <typename T>
void print(UniqueStruct<T> *unique);

std::vector<std::string> split(const std::string &s, char delim);

int alpha(char c);
void lowercase(std::string *data);

int main() {
	std::string line;
	std::vector<std::string> store;

        while(std::getline(std::cin,line)) {
		for (auto word : split(line, ' ')) {
			word.erase(std::remove_if(word.begin(), word.end(), alpha), word.end());
			lowercase(&word);
#if DEBUG
			std::cout << word << ": " << word.length() << std::endl;
#endif
			if (word.length() > 0) store.push_back(word);
#if DEBUG
			else std::cout << " ---- Skipped" << std::endl;
#endif
		}
	}

#if PRINT_VECTORS
	std::cout << "Repeating everything: " << std::endl;
	print(store);
#endif

	using namespace std::chrono;

	auto t0 = high_resolution_clock::now();
	auto unique_vec = unique_withvec(&store);
	auto t1 = high_resolution_clock::now();

	std::cout << "Without repetitions [vector] (" << duration_cast<milliseconds>(t1-t0).count() << " ms)" << std::endl;
#if PRINT_VECTORS
	print(&unique_vec);
#endif

	std::map<std::string, int> m;
	t0 = high_resolution_clock::now();
        auto unique_map = unique_withmap(&store, m);
        t1 = high_resolution_clock::now();

        std::cout << "Without repetitions [map] (" << duration_cast<milliseconds>(t1-t0).count() << " ms)" << std::endl;
#if PRINT_VECTORS
        print(&unique_map);
#endif

	std::unordered_map<std::string, int> m2;
	t0 = high_resolution_clock::now();
        auto unique_umap = unique_withmap(&store, m2);
        t1 = high_resolution_clock::now();

        std::cout << "Without repetitions [umap] (" << duration_cast<milliseconds>(t1-t0).count() << " ms)" << std::endl;
#if PRINT_VECTORS
        print(&unique_umap);
#endif

#if PRINT_VECTORS
	std::cout << "The original vector should not have been modified:" << std::endl;
	print(store);
#endif

	std::string cmp_res_mv = cmp<std::string>(unique_vec,unique_map) ? "==" : "!=";
	std::cout << "[vec] " << cmp_res_mv << " [map]" << std::endl;

	return 0;
}

template <typename T>
UniqueStruct<T> unique_withvec(const std::vector<T> *vec) {
	std::vector<T> copy = *vec;
	std::sort(copy.begin(), copy.end());

	std::vector<T> unique;
	std::vector<int> items_count;

	auto current = *copy.begin();
	int count = 1;
	for(int i = 1; i < copy.size(); i++) {
		auto pt = copy.at(i);
		if (pt != current) {
			unique.push_back(current);
			items_count.push_back(count);

			current = pt;
			count = 1;
		} else count++;
	}
	unique.push_back(current);
	items_count.push_back(count);

	return UniqueStruct<T>{unique, items_count};
}

template <typename T, typename M>
UniqueStruct<T> unique_withmap(const std::vector<T> *vec, M m) {
	for(auto pt : *vec) {
		if (m.count(pt)) m[pt]++;
		else m[pt] = 1;
       	}

	std::vector<T> keys;
        std::vector<int> counts;
       	for(auto it = m.begin(); it != m.end(); ++it) {
               	keys.push_back(it->first);
                counts.push_back(it->second);
       	}
        return UniqueStruct<T>{keys, counts};
}

template <typename T>
void print(std::vector<T> vec) {
	for(int i = 0; i < vec.size() -1; i++) std::cout << vec.at(i) << ", ";
	std::cout << vec.at(vec.size()-1) << std::endl;
}

template <typename T>
void print(UniqueStruct<T> *unique) {
        for(int i = 0; i < unique->items.size() -1; i++) std::cout << unique->items.at(i) << "(" << unique->count.at(i) << ")" << ", ";
	int last = unique->items.size()-1;
        std::cout << unique->items.at(last) << "(" << unique->count.at(last) << ")" << std::endl;
}

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

int alpha(char c) {
	return !std::isalpha(c);
}

void lowercase(std::string *data) {
	std::transform(data->begin(), data->end(), data->begin(), [](unsigned char c){ return std::tolower(c); });
}

template <typename T>
int cmp(const UniqueStruct<T>& self, const UniqueStruct<T>& other) {
        if (other.items.size() != self.items.size()) {
#if CMP_DETAILS
		std::cout << self.items.size() << " != " << other.items.size() << std::endl;
#endif
		return 0; 
	}

	int i;
	for (i = 0; i < self.items.size(); i++) {
#if CMP_DETAILS
		std::cout << self.items.at(i) << "/" << other.items.at(i) << " --- " << self.count.at(i) << "/" << other.count.at(i) << std::endl;
#endif
		if (self.items.at(i) != other.items.at(i) || self.count.at(i) != other.count.at(i)) return 0;
	}
        return 1;
}
