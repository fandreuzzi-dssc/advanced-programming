#include <array>
#include <iostream>
#include <utility>

#define DEBUG 1

template <typename T, std::size_t N>
std::array<T,N> transpose(const std::array<T,N> arr, int rows);

template <typename T, std::size_t N>
void transpose_same_array(std::array<T,N> &arr, int rows);

template <typename T, std::size_t N>
void transpose_same_array_with_swap(std::array<T,N> &arr, int rows);

int main() {
	std::array<double, 12> arr{{1,2,3,4,5,6,7,8,9,10,11,12}};

	//std::array<double, 12> trnsp{transpose<double,12>(arr, 4)};
	//for (int i = 0; i < 12; i++) std::cout << trnsp[i] << std::endl;

	transpose_same_array<double, 12>(arr, 4);
	for (int i = 0; i < 12; i++) std::cout << arr[i] << std::endl;
}

template <typename T, std::size_t N>
std::array<T,N> transpose(const std::array<T,N> arr, int rows) {
	int columns = N / rows;
	#if DEBUG
	std::cout << "rows: " << rows << ", columns: " << columns << std::endl;
	#endif

	std::array<double, N> trnsp{};
	
	std::cout << "-----------------" << std::endl;
	for (int row = 0; row < rows; row++) {
		for (int column = 0; column < columns; column++) {
			#if DEBUG
			std::cout << arr[row*columns + column] << " put into index " << column*rows + row << std::endl;
			#endif
			trnsp[column*rows + row] = arr[row*columns + column];
		}
		std::cout << "row " << row << ": done!" << std::endl;
	}
		
	return trnsp;
}

template <typename T, std::size_t N>
void transpose_same_array(std::array<T,N> &arr, int rows) {
	std::array<double, N> copy{arr};
	
	int columns = N / rows;
        #if DEBUG
        std::cout << "rows: " << rows << ", columns: " << columns << std::endl;
        #endif

        std::cout << "-----------------" << std::endl;
        for (int row = 0; row < rows; row++) {
                for (int column = 0; column < columns; column++) {
                        #if DEBUG
                        std::cout << arr[row*columns + column] << " put into index " << column*rows + row << std::endl;
                        #endif
                        arr[column*rows + row] = copy[row*columns + column];
                }
                std::cout << "row " << row << ": done!" << std::endl;
        }
}

template <typename T, std::size_t N>
void transpose_same_array_with_swap(std::array<T,N> &arr, int rows) {

}
