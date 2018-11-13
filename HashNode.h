#ifndef MY_HASH_NODE
#define MY_HASH_NODE

using namespace std;

class HashNode {
  unsigned long key;   // The hash node's key
  unsigned long value; // The key's associated data

  

public:

  // Add constructors, destructor if necessary
	HashNode();
	HashNode(unsigned long key, unsigned long value);
	
  	unsigned long getKey() { return key; }
  	unsigned long getValue() { return value; }
  	void assign(unsigned long key, unsigned long value); 

  // extend if necessary
};

HashNode::HashNode(){
	this->key = 0;
	this->value = 0;
}

HashNode::HashNode(unsigned long key, unsigned long value){
	assign(key, value);
}

void HashNode::assign(unsigned long key, unsigned long value) {
	this->key = key;
	this->value = value;
}


#endif
