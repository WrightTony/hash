#include <iostream>
#include <sstream>
#include <ctime>
#include <random>
#include "HashTable.h"

using namespace std;

int n = 10;

//calculate the square root of a given number
//code reference: https://www.youtube.com/watch?v=znuNWLiBX2A
int sqrt(int number) {

	double error = 0.00001; //define the precision of your result
    double s = number;

    while ((s - number / s) > error) //loop until precision satisfied 
    {
        s = (s + number / s) / 2;
    }
    return s;

}

//calculate the power of a given number to a given number
//code reference: https://www.youtube.com/watch?v=lNdI_7f4d68
int pow(int n, int p) {
	int temp;
	int c = 1;

	for (int i = 1; i <= p; i++) {
		temp=n;
		c=c*temp;
		//mod here when you know what going on
	}

	return c;
}

//calculate g to the r mod n
int sqrMod(int g, int r, int n) {
	return pow(g, r) % n;
}

//calculate a*g mod n
int timesMod(int a, int g, int r) {
	return (a * g) % r;
}

int orderOfG(int g, int n) {

	//create a hash table
	HashTable Ord;

	//repeat for sqrt n times
	for (int i = 0; i < sqrt(n); i++) {

		//pick a random number between 1 and n-1 
		default_random_engine  e(static_cast<unsigned int>(time(0)));
		uniform_int_distribution<int> d2(0, (n - 1));

		int r = d2(e);

		int y = sqrMod(g, r, n);

		//condition: If y = gr mod n is already a key in table Ord
		if (Ord.isInTable(y)) {
			//duplicate key found
			
			if (r - Ord.getValue(y) > 0) {
				return r - Ord.getValue(y);
			}
			else if(Ord.getValue(y) - r > 0){ 
				return Ord.getValue(y) - r;
			}

		}
		else {
			//add key y to table with value r
			Ord.insert(y, r);

		}
	}


	//duplicate key not found, assume order of g is n-1
	return n-1;
}

int findDLog(int g, int a, int n) {

	//create two hash tables
	HashTable A;
	HashTable B;

	int y;

	for (int i = 0; i < sqrt(n); i++) {

		//pick a random number r between 0 and n-1
		default_random_engine  e(static_cast<unsigned int>(time(0)));
		uniform_int_distribution<int> d2(0, (n - 1));

		int r = d2(e);

		cout << "r: " << r << endl;

		y = timesMod(a, g, n);

		cout << "y: " << y << endl;

		if (B.isInTable(y)) {
			if (B.getValue(y) - r > 0){
				return B.getValue(y) - r;
			}
			else{
				return r - B.getValue(y);
			}
		}
		else {
			//store r under key y in table A
			A.insert(y,r);
		}

		//pick a random number r between 0 and n-1
		int r2 = d2(e);

		y = sqrMod(a, g, n);

		if (A.isInTable(y)) {

			if (r2 - A.getValue(y) > 0){
				return r2 - A.getValue(y);
			}
			else if (A.getValue(y) - r2 > 0){
				return A.getValue(y) - r2;
			}
			
		}
		else {
			//store r under key y in table B
			B.insert(y, r);
		}

		cout << "End of loop rotation " << i << endl;
	}

	//if not found then return zero
	return 0;

}


int main() { //int argc, char** argv

	int g, a, n;

	//get three inputs g, a and n
	cin >> g;
	cin >> a;
	cin >> n;

	/*
	if (argc != 4) { //if there arent enough arguments
		cout << "Please enter the correct number of arguments" << endl;
		return 1;
	}
	else{
*/
		int order, log;

		order = orderOfG(g,n);

		cout << "Order of G: " << order << endl;

		log = findDLog(g,a,n);

		cout << "Log: " << log << endl;

		int output = log % order;

		if (output < 0) {
			output += order;
		}

		cout << "x = " << output << endl;
		
		return 0;
	//}


}


