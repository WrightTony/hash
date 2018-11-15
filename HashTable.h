#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include "HashNode.h"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

enum HashTableError { OUT_OF_MEMORY, KEY_NOT_FOUND, DUPLICATE_KEY }; // extend if necessary

typedef unsigned long ulint;

class HashTable {
  typedef vector <list<HashNode>> Table;
  Table *table; // size of table is stored in the Table data structure
  size_t num;   // number of entries in the HashTable;

public:
  HashTable();       // constructor, initializes table of size 1;
  HashTable(size_t); // constructor, requires size of table as arg
  ~HashTable();      // deconstructor

  size_t size(); // returns size of the hash table (number of buckets)
  size_t hash_function(ulint);  // the table's hash function
  ulint getValue(ulint);    // find and return data associated with key

  void insert(ulint,ulint); // insert data associated with key into table
  void erase(ulint);        // remove key and associated data from table

  void rehash(size_t); // sets a new size for the hash table, rehashes the hash table 

  void printTable(); // prints the elements in the table
  unsigned long findLoadFactor(); //returns the load factor value
  bool isInTable(ulint);

};

HashTable::HashTable() {

	try{
		//initialise values
		this->table = new Table(11);
		this->num = 0;
	}catch( HashTableError&e){
		cerr << "Not enough memory for a new table" << '\n';
		throw(OUT_OF_MEMORY);
	}
	
}

HashTable::HashTable(size_t tableSize) {

	this->table = new Table(tableSize);
	this->num = 0;
}

HashTable::~HashTable() {
	delete table;
}

size_t HashTable::size() {
	return table->size();
}

size_t HashTable::hash_function(unsigned long key) {
	return key % table->size();
}

unsigned long HashTable::getValue(unsigned long key) {

	//find which bucket to look in
	int hashNum = hash_function(key);

	try{
	//initialise the iterator
	list<HashNode> ::iterator it;

	//iterate through the list at the found bucket number
	for (it = table->at(hashNum).begin(); it != table->at(hashNum).end(); ++it){
		//condition if the key is the same as the key given
		if (it->getKey() == key){
			//return the value at the node found
			return it->getValue();
		}
	}
	}catch(HashTableError&e){
		cout << "Key not found error" << endl;
		throw KEY_NOT_FOUND;
	}

	return 0;
}

void HashTable::insert(unsigned long key, unsigned long value) {


	//condition, if the load factor is too high
	if (findLoadFactor() > 0.9){
		//make a new table that is the next biggest prime

		//double the size of the current table
		int newSize = table->size() * 2;

		//initialise checks
		bool found = false;
		bool breakCheck = false;

		//loop until the next biggest prime is found
		while (!found){

			//make sure break is false at the start of the 
			breakCheck = false;

			//this for loop will check the number to see if there are any factors
			//if there are it will break, meaning it is not a prime
			for(int i = 2; i <= newSize / 2; ++i){

			      if(newSize % i == 0) //if a factor is found
			      {
			          breakCheck = true;
			          break;
			      }
		  	}

		  	//if there was no factor found, the numeber is a prime
		  	if (!breakCheck) found = true;

		  	//if it wasn't a prime, increase the number being checked by 1 and repeat
		  	if (!found) newSize++;
		}

	rehash(newSize);

	}

	//find which bucket to put the new node into
	int hashNum = hash_function(key);

	//create a new node
	HashNode node(key, value);

	//add node to the list at position given by key
	table->at(hashNum).push_back(node);

	//increase num count
	this->num++;
	
}

void HashTable::erase(unsigned long key) {
	//find the bucket number
	int hashNum = hash_function(key);

	//initialise the iterator
	list<HashNode>::iterator it;

	//loop through the list in the bucket found
	for (it = table->at(hashNum).begin(); it != table->at(hashNum).end(); ++it){
		//condition, if the key of the current node is the same as the key given
		if (it->getKey() == key){
			//erase the current node
			table->at(hashNum).erase(it);
			//brake once done deleting
			break;
		}

		//if it is at the last node in the list and it has not yet
		//found one with a matching key, this means there are no nodes
		//with the key given in the table
		if (it == table->at(hashNum).end()){
			//throw exception KEY_NOT_FOUND;
		}
	}
	//decrease num count
	this->num--;

}

void HashTable::rehash(size_t newSize){

	//initialise temp
	Table* temp;

	//store the current table in temp
	temp = this->table;

	//create new table, assign the new table to replace the old one
	this->table = new Table(newSize);


	//loop for number of elements in the hash table
	for (size_t i = 0; i < temp->size(); i++){
		
		//intitialse iterator
		list<HashNode> ::iterator it;

		//loop through each element in each list
		for(it = temp->at(i).begin(); it != temp->at(i).end(); ++it){
			//insert each element back into the table
			insert(it->getKey(), it->getValue());
		}
	}
}

//load factor, total elements/num of buckets
unsigned long HashTable::findLoadFactor(){
	return num / table->size();
}

bool HashTable::isInTable(unsigned long key){
	//find which bucket to look in
	int hashNum = hash_function(key);

	//initialise the iterator
	list<HashNode> ::iterator it;

	//iterate through the list at the found bucket number
	for (it = table->at(hashNum).begin(); it != table->at(hashNum).end(); ++it){
		//condition if the key is the same as the key given
		if (it->getKey() == key){
			//return the value at the node found
			return true;
		}
	}

	return false;
}

void HashTable::printTable(){
	

	for (size_t i = 0; i < table->size(); i++){

		//intitialse iterator
		list<HashNode> ::iterator it;

		//loop through each element in each list
		for(it = table->at(i).begin(); it != table->at(i).end(); ++it){
			//insert each element back into the table
			cout << "Bucket num " << i << " Key " << it->getKey()<<endl;
		}
	}
}

#endif
