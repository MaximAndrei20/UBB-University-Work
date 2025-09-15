/*
a. Determine the first n pairs of twin numbers, where n is a given natural and non-null number.
	Two prime numbers p and q are called twin if q – p = 2.
b. Given a vector of numbers, find the longest decreasing contiguous subsequence.

*/

#include <stdio.h>

void printMenu() {
	// Prints the menu
	printf("1. Enter a vector of numbers.\n");
	printf("2. Determine the first n pairs of twin primes.\n");
	printf("3. Find the longest decreasing contiguous subsequence of the vector.\n");
	printf("0. Exit\n");
	printf("> ");
}

void readVector(int* n, int v[]) {
	/*
	:param: n - the number of elements in the vector
	:param: v - the vector of numbers
	:return: void

	Reads the vector of numbers
	*/
	printf("Enter the number of elements in the vector: ");
	int rez = scanf_s("%d", n);
	if (rez == 0) {
		printf("Invalid option. Please try again.\n");
		//Make so that the program doesn't get stuck in an infinite loop
		while (getchar() != '\n');
		return;
	}
	if (*n <= 0 || *n > 25) {
		printf("Invalid number of elements. Please try again.\n");
		return;
	}
	printf("Enter the elements of the vector: ");
	for (int i = 0; i < *n; i++) {
		int rez = scanf_s("%d", &v[i]);
		if (rez == 0) {
			printf("Invalid option. Please try again.\n");
			//Make so that the program doesn't get stuck in an infinite loop
			while (getchar() != '\n');
			return;
		}
	}
}

void printVector(int n, int v[] ) {
	/*
	Prints the vector of numbers
	*/
	if (n < 0)
		return;
	printf("The vector is: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");
}

int isPrime(int a) {
	/*
	* :param: a - the number to check if it is prime
	* :return: 1 if a is prime, 0 otherwise
	*/
	if (a < 2)
		return 0;
	if (a == 2)
		return 1;
	if (a % 2 == 0)
		return 0;
	for (int d = 3; d * d <= a; d += 2) {
		if (a % d == 0)
			return 0;
	}
	return 1;
}

void determineTwinPrimes(int n, int primes[]) {
	/*
	:param: n - the number of pairs of twin primes to determine
	:param: primes - the array where the first of each pair of twin primes will be stored

	:return: void
	*/
	int count = 0;
	int number = 2;
	while (count < n) {
		// Find the next prime number
		// Check if it is a twin prime
		// If it is, store it in the array
		// Increment the count
		// Repeat until we have n pairs of twin primes
		if (isPrime(number) && isPrime(number + 2)) {
			primes[count++] = number;
		}
		number++;
	}
}

void findLongestDecreasingContiguousSubsequence(int n, int v[], int* start, int* length) {
	/*
	:param: n - the number of elements in the vector
	:param: v - the vector of numbers
	:param: start - the index of the first element of the longest decreasing contiguous subsequence
	:param: length - the length of the longest decreasing contiguous subsequence
	:return: void
	*/
	if (n < 0)
		return;
	int currentStart = 0;
	int currentLength = 1;
	int maxLenght = 0;
	for (int i = 1; i < n; i++) {
		if (v[i] < v[i - 1])
			currentLength++;
		else {
			if (currentLength > maxLenght) {
				maxLenght = currentLength;
				*start = currentStart;
				*length = currentLength;
			}
			currentStart = i;
			currentLength = 1;
		}
	}
	// Check if the last decreasing subsequence is the longest
	if (currentLength > maxLenght) {
		maxLenght = currentLength;
		*start = currentStart;
		*length = currentLength;
	}
}

void printPrimes(int n, int primes[]) {
	/*
	:param: n - the number of pairs of twin primes to print
	:param: primes - the array where the first of each pair of twin primes is stored
	:return: void
	*/
	for (int i = 0; i < n; i++) {
		printf("(%d, %d)\n", primes[i], primes[i] + 2);
	}
}

void printPartOfVector(int start, int length, int v[]) {
	/*
	:param: start - the index of the first element of the longest decreasing contiguous subsequence
	:param: length - the length of the longest decreasing contiguous subsequence
	:param: v - the vector of numbers
	:return: void
	*/
	if (length < 0)
		return;
	printf("The longest decreasing contiguous subsequence is: ");
	for (int i = start; i < start + length; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");
}

int main() {
	// Contains the first prime number of the pair
	// So the pair is primes[i] and primes[i] + 2
	int primes[500];

	int n = -1, v[25]; 
	while (1) {
		printMenu();
		int option = 0;
		int rez = scanf_s("%d", &option);
		if (rez == 0) {
			printf("Invalid option. Please try again.\n");
			//Make so that the program doesn't get stuck in an infinite loop
			while (getchar() != '\n');
			continue;
		}
		switch (option) {
		case 1:
			readVector(&n, v);
			break;
		case 2:
		{
			// Determine the first x pairs of twin primes
			int x = 0;
			printf("Enter the number of pairs of twin primes: ");
			rez = scanf_s("%d", &x);
			if (rez == 0) {
				printf("Invalid option. Please try again.\n");
				//Make so that the program doesn't get stuck in an infinite loop
				while (getchar() != '\n');
				break;
			}
			if (x <= 0) {
				printf("Invalid number of pairs. Please try again.\n");
				break;
			}
			determineTwinPrimes(x, primes);
			printPrimes(x, primes);
			break;
		}
		case 3:
			// Find the longest decreasing contiguous subsequence of the vector
			{
				int start=0, length=-1;
				if (n < 0) {
					printf("Please enter a vector of numbers first.\n");
					break;
				}
				findLongestDecreasingContiguousSubsequence(n, v, &start, &length);
				if (length == -1) {
					printf("There is no decreasing contiguous subsequence in the vector.\n");
					break;
				}
				printPartOfVector(start, length, v);
			}
			break;
		case 4:
			// Print the vector
			printVector(n, v);
			break;
		case 0:
			return 0;
		default:
			printf("Invalid option. Please try again.\n");
		}
	}
	return 0;
}