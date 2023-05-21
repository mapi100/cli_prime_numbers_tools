#include <iostream>
#include <vector>
#include <cmath>

// A function is used to check if the number given is a prime number
bool isPrime(long long int number) {
    if (number <= 1) {
        return false;
    }
    // Check divisibility up to the square root of the number
    for (long long int divisor = 2; divisor <= std::sqrt(number); divisor++) {
        if (number % divisor == 0) {
            return false;
        }
    }
    return true;
}

// A function is used to print all prime numbers up to a given limit
// Basically, is the Sieve of Eratosthenes algorithm
void printPrimesUpToLimit(int limit) {
    std::vector<bool> isPrime(limit + 1, true);

    for (int p = 2; p * p <= limit; p++) {
        if (isPrime[p]) {
	    // Mark multiples of p as non-prime
            for (int i = p * p; i <= limit; i += p) {
                isPrime[i] = false;
            }
        }
    }

    std::cout << "Prime numbers up to " << limit << " are:\n";
    for (int p = 2; p <= limit; p++) {
        if (isPrime[p]) {
                // Prime numbers are printed
		std::cout << p << " ";
        }
    }
    std::cout << "\n";
}

// A function is used to find the closest prime number to a given input
void findClosestPrime(long long int number) {
    if (isPrime(number)) {
        std::cout << "The number itself, " << number << ", is a prime number.\n";
        return;
    }

    long long int smallerPrime = number - 1;
    long long int largerPrime = number + 1;

    // To find the closest smaller prime of the given input
    while (!isPrime(smallerPrime)) {
        smallerPrime--;
    }

    while (!isPrime(largerPrime)) {
        largerPrime++;
    }

    // Same as above, but with a larger prime
    std::cout << "Closest prime number to " << number << " is: ";
    if (number - smallerPrime <= largerPrime - number) {
        std::cout << smallerPrime;
    } else {
        std::cout << largerPrime;
    }
    std::cout << "\n";
}

// A function to find all twin primes up to a given limit
void findTwinPrimesUpToLimit(int limit) {
    std::cout << "Twin primes up to " << limit << " are:\n";
    for (int p = 2; p <= limit - 2; p++) {
        if (isPrime(p) && isPrime(p + 2)) {
            std::cout << "(" << p << ", " << p + 2 << ") ";
        }
    }
    std::cout << "\n";
}

// Choose options are provided in order to let the user choose the mode
int main() {
    int option;
    std::cout << "Choose an option:\n";
    std::cout << "1. Print all prime numbers up to a limit.\n";
    std::cout << "2. Find the closest prime number to a given input.\n";
    std::cout << "3. Find all twin primes up to a limit.\n";
    std::cout << "Option: ";
    std::cin >> option;

    if (option == 1) {
        int limit;
        std::cout << "Enter the limit: ";
        std::cin >> limit;
        printPrimesUpToLimit(limit);
    } else if (option == 2) {
        long long int number;
        std::cout << "Enter a number: ";
        std::cin >> number;
        findClosestPrime(number);
    } else if (option == 3) {
        int limit;
        std::cout << "Enter the limit: ";
        std::cin >> limit;
        findTwinPrimesUpToLimit(limit);
    } else {
        std::cout << "Invalid option!\n";
    }

    return 0;
}
