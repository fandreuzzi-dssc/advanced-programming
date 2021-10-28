#include <iostream>
#include <utility>
#include <array>

template <std::size_t N>
void dutch(std::array<int, N> &arr, int pivot);

int main(int argc, char **argv) {
	if (argc == 1) {
		std::cout << "Pivot not supplied" << std::endl;
		return 0;
	}
	
	const int N = 30;
	std::array<int, N> arr{{3,1,4,1,5,5,9,2,6,5,3,9,1,2,4,5,9,8,3,4,5,1,3,1,7,6,5,4,2,3}};
	dutch<N>(arr, std::stoi(argv[1]));
	for (int i=0; i < N; i++) std::cout << arr[i] << " ";
}

template <std::size_t N>
void dutch(std::array<int, N> &arr, int pivot) {
	//exclusive
	int less_upper_limit = 0;
	//inclusive
	int great_lower_limit = 0;

	//this counter starts from the upper limit of the
	//array, we use it to find unvisited cells to swap
	//values greater than the pivot
	int j = N-1;

	for (int i=0; i<N && i!=j;) {
		if (arr[i] == pivot) {
			great_lower_limit++;
			i++;
		} else if(arr[i] < pivot) {
			//we swap the first equal item with arr[i]
			std::swap(arr[less_upper_limit], arr[i]);

			less_upper_limit++;
			great_lower_limit++;
			i++;			
		} else {
			//we swap arr[i] with the last unvisited item
			//of the array, which still needs to be evaluated
			std::swap(arr[i], arr[j--]);
		}
	}
}
