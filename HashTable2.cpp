#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Hash_linear {

    int sizeTable = 3;
    int currentSize = 0;
    vector<string> hashTable;

public:

    Hash_linear() {
        hashTable.clear();
        sizeTable = 3;
        for (int i = 0; i < sizeTable; ++i) {
            hashTable.push_back(string());
        }
    }



    unsigned long long getHash(string input) {

        unsigned long long hash = 0;
        for (int i = 0; i < input.length(); i++) {
            hash += input.at(i);
            hash *= (i * 3 * 7);
        }
        return hash % sizeTable;
    }

    double table_load() {
        return (double) currentSize / sizeTable;
    }

    void resize(int newSize) {

        vector<string> newHashTable;
        for (int i = 0; i < newSize; ++i) {
            newHashTable.push_back(string());
        }

        int tmp = sizeTable;
        sizeTable = newSize;

        for (int i = 0; i < tmp; i++) {
            if (hashTable[i] != string()) {

                unsigned long long hash = getHash(hashTable[i]);

                while (newHashTable[hash] != string()) {
                    hash = (hash + 1) % sizeTable;
                }
                newHashTable[hash] = hashTable[i];
            }
        }
        hashTable.clear();
        hashTable = newHashTable;
    }

    void insert(string input) {

        currentSize++;

        if (table_load() > 0.7) {
            resize(sizeTable * 2);
            // po zvacseni 0.35
        }
        if (table_load() < 0.3) {
            resize(sizeTable / 2);
        }

        unsigned long long hash = getHash(input);

        while (hashTable[hash] != string()) {
            hash = (hash + 1) % sizeTable;
        }

        hashTable[hash] = input;
    }

    void search(string input) {

        unsigned long long hash = getHash(input);

        if (hashTable[hash] == input){
            //cout << input << " was found" << endl;
            return;
        }

        for (; (hash + 1) != hash ; hash = (hash + 1) % sizeTable) {
            if (hashTable[hash] == input){
                //cout << " was found" << endl;
                return;
            }
        }

        //cout << input << " was not found" << endl;
    }

    void remove(string input) {

        unsigned long long hash = getHash(input);

        if (hashTable[hash] == input){
            hashTable[hash] = string();
            currentSize--;

            if (table_load() < 0.3) {
                resize(sizeTable / 2);
            }
            return;
        }

        for (; (hash + 1) != hash ; hash = (hash + 1) % sizeTable) {
            if (hashTable[hash] == input){
                hashTable[hash] = string();
                currentSize--;

                if (table_load() < 0.3) {
                    resize(sizeTable / 2);
                }
                return;
            }
        }
    }

    void display() {
        for (int y = 0; y < sizeTable; y++) {
            cout << y << ": " << hashTable[y] << endl;
        }
        cout << "Table: " << sizeTable << endl;
        cout << "Elements: " << currentSize << endl;
    }
};
