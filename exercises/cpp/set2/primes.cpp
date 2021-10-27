#include <iostream>

int main() {
	int primes[100] = {0};
	primes[0] = 2;	

	int primes_counter = 1;
	for (int i=3; i < 100; i+=2) {
		int is_prime = 1;
		for (int j = 3; j < i / 2 && is_prime; j+=2) is_prime *= i % j != 0;
		if (is_prime) primes[primes_counter++] = i;
	}

	for (int i = 0; i < primes_counter; i++) std::cout << primes[i] << std::endl;
}
