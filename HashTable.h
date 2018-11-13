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

  // extend if necessary
};

HashTable::HashTable() {
	//initialise values
	this->table = new Table(11);
	this->num = 0;
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

	int hashNum = hash_function(key);

	list<HashNode> ::iterator it;

	for (it = table->at(hashNum).begin(); it != table->at(hashNum).end(); ++it){
		if (it->getKey() == key){
			return it->getValue();
		}
	}

	return KEY_NOT_FOUND;
}

void HashTable::insert(unsigned long key, unsigned long value) {

	int hashNum = hash_function(key);

	HashNode node(key, value);

	table->at(hashNum).push_back(node);

	//increase num by 1
}

void HashTable::erase(unsigned long key) {
	int hashNum = hash_function(key);

	list<HashNode> ::iterator it;

	for (it = table->at(hashNum).begin(); it != table->at(hashNum).end(); ++it){
		if (it->getKey() == key){
			table->at(hashNum).erase(it);
		}
	}

}

void HashTable::rehash(size_t newSize){

	Table* temp;

	temp = this->table;

	//create new table
	this->table = new Table(newSize);

	//loop for number of elements in the hash table
	for (size_t i = 0; i < temp->size(); i++){
		//take the first element in the table

		list<HashNode> ::iterator it;

		//loop through each element in each list
		for(it = temp->at(i).begin(); it != temp->at(i).end(); ++it){
			insert(it->getKey(), it->getValue());
		}
	}
}

#endif
