#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "hashf.hpp"


std::string* createHashTable(std::ifstream &in, int tableSize) {
	std::string *hashTable = new std::string[tableSize];

	for (int i = 0; i < tableSize; i++) {
		hashTable[i] = "";
	}

	while (!in.eof()) {
		std::string word;
		in >> word;
		int hash = hashf(word.c_str());
		int index = hash % tableSize;

		bool added = false;
		for (int i = 0; i < tableSize; i++) {
			if (hashTable[(index + i) % tableSize] == "") {
				hashTable[(index + i) % tableSize] = word;
				added = true;
				break;
			}
		}

		if (!added) {
			std::cout << "Hashtable is full";
		}
	}

	return hashTable;
}

int main() {
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	
	int hashTableSize = 20;
	std::string* hashTable = createHashTable(in, hashTableSize);

	for (int i = 0; i < hashTableSize; i++) {
		out << i << ": " << hashTable[i] << std::endl;
	}

	delete[] hashTable;

	return 0;
}

