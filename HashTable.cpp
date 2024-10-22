// Filename: HashTable.cpp

#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;
    std::vector<bool> deleted;
    int currentSize;
    int tableSize;
    const float LOAD_FACTOR = 0.8;

    // Check if a number is prime
    bool isPrime(int n) const {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // Find the next prime number greater than or equal to n
    int nextPrime(int n) const {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    // Hash function: key mod table size
    int hash(int key) const {
        return key % tableSize;
    }

    // Quadratic probing function
    int probe(int key, int i) const {
        return (hash(key) + i * i) % tableSize;
    }

    // Rehash the table when load factor exceeds threshold
    void rehash() {
        std::vector<int> oldTable = table;
        std::vector<bool> oldDeleted = deleted;
        int oldSize = tableSize;

        // Update table size to next prime number at least twice the current size
        tableSize = nextPrime(2 * tableSize);
        table.assign(tableSize, -1);
        deleted.assign(tableSize, false);
        currentSize = 0;

        // Re-insert existing keys into the new table
        for (int i = 0; i < oldSize; ++i) {
            if (oldTable[i] != -1 && !oldDeleted[i]) {
                insert(oldTable[i]);
            }
        }
    }

    // Calculate current load factor
    float loadFactor() const {
        return static_cast<float>(currentSize) / tableSize;
    }

public:
    // Constructor: Initialize hash table with a given size (adjusted to next prime)
    HashTable(int size) {
        tableSize = nextPrime(size);
        table.assign(tableSize, -1);
        deleted.assign(tableSize, false);
        currentSize = 0;
    }

    // Insert a key into the hash table
    void insert(int key) {
        if (search(key) != -1) {
            std::cout << "Duplicate key insertion is not allowed" << std::endl;
            return;
        }

        // Rehash if load factor exceeds threshold
        if (loadFactor() > LOAD_FACTOR) {
            rehash();
        }

        int i = 0;
        int idx = probe(key, i);
        while (table[idx] != -1 && !deleted[idx]) {
            i++;
            if (i >= tableSize) {  // Corrected termination condition
                std::cout << "Max probing limit reached!" << std::endl;
                return;
            }
            idx = probe(key, i);
        }

        // Insert the key
        table[idx] = key;
        deleted[idx] = false;
        currentSize++;
    }

    // Remove a key from the hash table
    void remove(int key) {
        int i = 0;
        int idx = probe(key, i);
        while (table[idx] != -1) {  // Corrected loop condition
            if (table[idx] == key && !deleted[idx]) {
                table[idx] = -1;
                deleted[idx] = true;
                currentSize--;
                return;
            }
            i++;
            if (i >= tableSize) {  // Corrected termination condition
                std::cout << "Element not found" << std::endl;
                return;
            }
            idx = probe(key, i);
        }
        std::cout << "Element not found" << std::endl;
    }

    // Search for a key in the hash table; return index or -1 if not found
    int search(int key) const {
        int i = 0;
        int idx = probe(key, i);
        while (table[idx] != -1) {  // Corrected loop condition
            if (table[idx] == key && !deleted[idx]) {
                return idx;
            }
            i++;
            if (i >= tableSize) {  // Corrected termination condition
                return -1;
            }
            idx = probe(key, i);
        }
        return -1;
    }

    // Print the current state of the hash table
    void printTable() const {
        for (int i = 0; i < tableSize; i++) {
            if (table[i] != -1 && !deleted[i]) {
                std::cout << table[i] << " ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }
};
