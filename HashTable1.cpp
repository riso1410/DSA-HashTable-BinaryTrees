#include <iostream>
#include <list>
#include <string>

using namespace std;

class Hash_chaining {

    int sizeTable = 3;
    int currentSize = 0;
    list <string> *hashTable;

public:

    Hash_chaining() {

        hashTable = new list<string>[sizeTable];
    }

    int getHash(string input) {

        unsigned long long hash = 0;
        for (int i = 0; i < input.length(); i++) {
            hash += (int) input.at(i);
            hash *= (i * i * hash);
        }
        return hash % sizeTable;
    }

    double table_load() {
        return (double) currentSize / sizeTable;
    }

    void resize(int newSize) {

        list <string> *newHashTable = new list<string>[newSize];

        int temp = sizeTable;
        sizeTable = newSize;

        for (int i = 0; i < temp; i++) {
            for (auto item: hashTable[i]) {
                newHashTable[getHash(item)].push_back(item);
            }
        }
        delete[] hashTable;
        hashTable = newHashTable;
    }

    void insert(string input) {
        hashTable[getHash(input)].push_back(input);
        currentSize++;

        if (table_load() > 0.7) {
            resize(sizeTable * 2);
            // po zvacseni 0.35
        }
        if (table_load() < 0.3) {
            resize(sizeTable / 2);
        }
    }

    void search(string input) {

        int hash = getHash(input);
        for (auto i = hashTable[hash].begin(); i != hashTable[hash].end(); i++) {
            if (*i == input) {
                //cout << input << " was found" << endl;
                return;
            }
        }
    }

    void remove(string input) {
        int hash = getHash(input);

        for (auto i = hashTable[hash].begin(); i != hashTable[hash].end(); i++) {
            if (*i == input) {
                hashTable[hash].erase(i);
                currentSize--;
                return;
            }
        }

        if (table_load() > 0.7) {
            resize(sizeTable * 2);
            // po zvacseni 0.35
        }
        if (table_load() < 0.3) {
            resize(sizeTable / 2);
        }
    }

    void display() {
        for (int y = 0; y < sizeTable; y++) {
            cout << y << ": ";
            for (auto i = hashTable[y].begin(); i != hashTable[y].end(); i++) {
                cout << *i << " ";
            }
            cout << endl;
        }
    }
};