#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

class HashTable {
private:
    std::vector<int> table;
    std::vector<bool> deleted;
    int currentSize;
    int tableSize;
    float LOAD_FACTOR = 0.8;
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }
    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }
    int hash(int key) {
        return key % tableSize;
    }

    int probe(int key, int i) {
        return (hash(key) + i * i) % tableSize;
    }

    void rehash() {
        std::vector<int> oldTable = table;
        std::vector<bool> oldDeleted = deleted;
        int oldSize = tableSize;

        tableSize = nextPrime(2 * tableSize);
        table.clear();
        deleted.clear();
        table.resize(tableSize, -1);
        deleted.resize(tableSize, false);
        currentSize = 0;

        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != -1 && !oldDeleted[i]) {
                insert(oldTable[i]);
            }
        }
    }

    float loadFactor() const {
        return static_cast<float>(currentSize) / tableSize;
    }

public:
    HashTable(int size) {
        tableSize = nextPrime(size);  // Initialize with prime size
        table.resize(tableSize, -1);  // -1 indicates an empty slot
        deleted.resize(tableSize, false);  // False indicates no deletion
        currentSize = 0;
    }

    void insert(int key) {
        if (search(key) != -1) {
            std::cout << "Duplicate key insertion is not allowed" << std::endl;
            return;
        }

        if (loadFactor() >= LOAD_FACTOR) {
            rehash();
        }

        int i = 0;
        int idx = probe(key, i);
        while (table[idx] != -1 && !deleted[idx]) {
            i++;
            if (i >= tableSize) {
                std::cout << "Max probing limit reached!" << std::endl;
                return;
            }
            idx = probe(key, i);
        }
        table[idx] = key;
        deleted[idx] = false;
        currentSize++;
    }

    int search(int key) {
        int i = 0;
        int idx = probe(key, i);
        while (table[idx] != -1 || deleted[idx]) {
            if (table[idx] == key && !deleted[idx]) {
                return idx;
            }
            i++;
            if (i > tableSize) return -1;  
            idx = probe(key, i);
        }
        return -1;  
    }

    void remove(int key) {
        int i = 0;
        int idx = probe(key, i);
        while (table[idx] != -1 || deleted[idx]) {
            if (table[idx] == key && !deleted[idx]) {
                table[idx] = -1;  
                deleted[idx] = true;  
                currentSize--;
                return;
            }
            i++;
            if (i > tableSize) {
                std::cout << "Element not found" << std::endl;
                return;
            }
            idx = probe(key, i);
        }
        std::cout << "Element not found" << std::endl;
    }

    void printTable() {
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
