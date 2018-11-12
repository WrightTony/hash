#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include "HashNode.h"
#include <vector>
#include <list>

using namespace std;

enum HashTableError { OUT_OF_MEMORY, KEY_NOT_FOUND, DUPLICATE_KEY }; // extend if necessary

typedef unsigned long ulint;

class HashTable {
  typedef vector <list<HashNode> > Table;
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
	this->table = new Table(11);
	this->num = 0;
}

HashTable::HashTable(size_t) {
	this->table = new table(size_t);
	this->num 0;
}

HashTable::~HashTable() {
	table.clear();
}

HashTable::size_t size() {
	return table.size();
}

HashTable::size_t hash_function(ulint key) {
	return key % table.size();
}

HashTable::ulint getValue(ulint key) {
	int hashNum = hash_function(key);

	return table.at(hashNum)->getValue();
}

HashTable::void insert(ulint key, ulint value) {
	int hashNum = hash_function(key);

	node = new HashNode(ulint key, ulint value);

	table.at(hashNum) = node;
}

HashTable::void erase(ulint key) {
	int hashNum = hash_function(key);
}

#endif
