#include <iostream>

template <typename T>
T* create_array(std::size_t length);

template <typename T>
void prnt(T* array, std::size_t length, int reverse);

int main() {
	std::size_t length;
	std::cin >> length;

	int* arr = create_array<int>(length);
	for (int i = 0; i < length; i++) std::cin >> arr[i];

	std::cout << "Printing array in reverse order" << std::endl;
	prnt<int>(arr, length, 1);

	double* arr2 = create_array<double>(length);
        for (int i = 0; i < length; i++) std::cin >> arr2[i];

        std::cout << "Printing array in reverse order" << std::endl;
        prnt<double>(arr2, length, 1);
}

template <typename T>
T* create_array(std::size_t length) {
        return new T[length];
}

template <typename T>
void prnt(T* array, std::size_t length, int reverse) {
	for (int i=reverse ? length - 1 : 0; i < length && i > -1; i += reverse ? -1 : 1) std::cout << array[i] << std::endl;
}
