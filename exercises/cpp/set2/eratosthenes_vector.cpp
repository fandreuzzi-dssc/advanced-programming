#include <iostream>
#include <vector>

void sieve(std::vector<int> &array, int N);

int main() {
	int N;
	std::cout << "N? -> ";
	std::cin >> N;

	std::vector<int> primes(N-1);
	for (int i = 2; i < N+1; i++) primes[i-2] = i;

	sieve(primes, N);

	for (int i = 2; i < N+1; i++) if (primes[i-2] != 0) std::cout << i << std::endl;
}

void sieve(std::vector<int> &array, int N) {
	int p = 2;
	while(p <= N) {
		for (int k = 2; k*p < N+1; k++) array[k*p - 2] = 0;
		for (p += 1; p < N+1 && array.at(p-2) == 0; p++) {}
	}	
}
