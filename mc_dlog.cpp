#include <iostream>
#include <sstream>
#include <ctime>
#include <random>
#include "HashTable.h"

using namespace std;

int n = 10;

//calculate the square root of a given number
//code reference: https://www.youtube.com/watch?v=znuNWLiBX2A
unsigned long sqrt(unsigned long n) {
	for (i = 0.01; i*i < n; i = i + 0.01);
	return i;
}

//calculate the power of a given number to a given number
//code reference: https://www.youtube.com/watch?v=lNdI_7f4d68
unsigned long pow(unsigned long n, int p) {
	int temp;
	int c = 1;

	for (i = 1; i <= p; i++) {
		temp=n;
		c=c*temp;
	}

	return c;
}

//calculate g to the r mod n
unsigned long sqrMod(int g, int r, int n) {
	return pow(g, r) % n;
}

//calculate a*g mod n
unsigned long timesMod(int a, int g, int r) {
	return a * g % r;
}

unsigned long orderOfG() {

	//create a hash table
	HashTable Ord;

	int r = 0;

	//repeat for sqrt n times
	for (int i = 0; i < sqrt(n); i++) {

		//pick a random number between 1 and n-1 
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(1, n - 1);
		r = distribution(generator);

		//condition: If y = gr mod n is already a key in table Ord
		if (findInTable(Ord, sqrMod(g, r, n)) {
			//duplicate key found
			
			if (r - Ord[hash_function(y)] > 0) {
				return r - Ord[hash_function(y)];
			}
			else if (Ord[hash_function(y)] - r > 0) {
				return Ord[hash_function(y)] - r;
			}

		}
		else {
			//add key y to table with value r
			Ord.insert(y, r);

		}
	}

	//duplicate key not found, assume order of g is n-1


}

unsigned long findDLog() {

	//create two hash tables
	HashTable A;
	HashTable B;

	int r = 0;

	for (int i = 0; i < sqrt(n); i++) {

		//pick a random number r between 0 and n-1
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(1, n - 1);
		r = distribution(generator);

		if (findInTable(B, timesMod(a, g, n)) {
			return B[hash_function(y)] - r;
		}
		else {
			//store r under key y in table A
		}

		//pick a random number r between 0 and n-1
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(1, n - 1);
		r = distribution(generator);

		if (findInTable(A, timesMod(a, g, n)) {
			return r - A[hash_function(y)];
		}
		else {
			//store r under key y in table B
		}
			
			
	}
}


int main() {

	//get three inputs g, a and n
	cin >> g;
	cin >> a;
	cin >> n;

	output = findDLog() % orderOfG();

	if (output < 0) {
		output += orderOfG();
	}

	cout << "x = " << output << endl;
	
	return 0;
}


