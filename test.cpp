#include <iostream>
#include <cstdlib>
#include <chrono>
#include <fstream>
#include <string>
#include "AVL.cpp"
#include "Splay.cpp"
#include "HashTable1.cpp"
#include "HashTable2.cpp"
#include <vector>

using namespace std;
using namespace std::chrono;

void AVL_start() {

    AVL_BST tree;
    string randomS;
    int number, size = 25000, check = 0, flag = 1;
    vector<int> integers;
    vector<string> strings;
    srand((unsigned) time(0));
    ofstream results;

    //---------------------------------------------------------------------------------------------
    for (int i = 0; i < 10000000; ++i) {
        number = rand() * rand();
        integers.push_back(number);
    }
    //---------------------------------------------------------------------------------------------
    for (int i = 0; i < 10000000; ++i) {

        char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        int len = rand() % (11 - 5) + 5;
        randomS.reserve(len);

        for (int j = 0; j < len; ++j) {
            randomS += characters[rand() % (sizeof(characters) - 1)];
        }

        strings.push_back(randomS);
        randomS = "";
    }
    //---------------------------------------------------------------------------------------------
    results.open("C:\\Users\\riso\\CLionProjects\\DSA1\\results.txt", ios::app);

    if (!results.is_open()) {
        cout << "File did not open" << endl;
        return;
    }
    //---------------------------------------------------------------------------------------------
    while (size <= 5000000) {

        //check = 0;

        auto start_insert = high_resolution_clock::now();

        while (check != size) {
            tree.insert(integers[check], strings[check]);
            check++;
        }

        auto stop_insert = high_resolution_clock::now();
        auto duration_insert = duration_cast<nanoseconds>(stop_insert - start_insert);

        //results << duration_insert.count() / 25000 << endl;
        //---------------------------------------------------------------------------------------------

        check = 0;
        auto start_search = high_resolution_clock::now();

        while (check != size) {
            tree.search(integers[check]);
            check++;
        }

        auto stop_search = high_resolution_clock::now();
        auto duration_search = duration_cast<nanoseconds>(stop_search - start_search);

        results << duration_search.count() / size << endl;
/*
        //---------------------------------------------------------------------------------------------


        check = 0;

        auto start_remove = high_resolution_clock::now();

        while (check != size) {
            tree.remove(integers[check]);
            check++;
        }

        auto stop_remove = high_resolution_clock::now();
        auto duration_remove = duration_cast<nanoseconds>(stop_remove - start_remove);

        results << duration_remove.count() / size << endl;
*/
        //flag++;
        size += 25000;
    }

    //tree.preorder();
    results << "############" << endl;
    results.close();
}

void Splay_start() {

    Splay_BST tree;
    string randomS;
    int number, size = 25000, check = 0, flag = 1;
    vector<int> integers;
    vector<string> strings;
    srand((unsigned) time(0));
    ofstream results;

    //---------------------------------------------------------------------------------------------
    for (int i = 0; i < 1000000; ++i) {
        number = rand() * rand();
        integers.push_back(number);
    }
    //---------------------------------------------------------------------------------------------
    for (int i = 0; i < 1000000; ++i) {

        char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        int len = rand() % (11 - 5) + 5;
        randomS.reserve(len);

        for (int j = 0; j < len; ++j) {
            randomS += characters[rand() % (sizeof(characters) - 1)];
        }

        strings.push_back(randomS);
        randomS = "";
    }
    //---------------------------------------------------------------------------------------------
    results.open("C:\\Users\\riso\\CLionProjects\\DSA1\\results.txt", ios::app);

    if (!results.is_open()) {
        cout << "File did not open" << endl;
        return;
    }
    //---------------------------------------------------------------------------------------------
    while (size <= 1000000) {

        check = 0;

        auto start_insert = high_resolution_clock::now();

        while (check != size) {
            tree.insert(integers[check], strings[check]);
            check++;
        }

        auto stop_insert = high_resolution_clock::now();
        auto duration_insert = duration_cast<nanoseconds>(stop_insert - start_insert);

        //results << duration_insert.count() / 25000 << endl;
/*
        //---------------------------------------------------------------------------------------------
        check = 0;
        auto start_search = high_resolution_clock::now();

        while (check != size) {
            tree.search(integers[check]);
            check++;
        }

        auto stop_search = high_resolution_clock::now();
        auto duration_search = duration_cast<nanoseconds>(stop_search - start_search);

        //results << duration_search.count() / size << endl;
*/
        //---------------------------------------------------------------------------------------------

        check = 0;

        auto start_remove = high_resolution_clock::now();

        while (check != size) {
            tree.remove(integers[check]);
            check++;
        }

        auto stop_remove = high_resolution_clock::now();
        auto duration_remove = duration_cast<nanoseconds>(stop_remove - start_remove);

        results << duration_remove.count() / size << endl;

        flag++;
        size = 25000 * flag;
    }
    tree.preorder();
    results << "############" << endl;
    results.close();
}

void Hash_start() {

    string str, randomS;
    vector<string> strings;
    int size = 25000, check = 0, random;
    //cout << "Enter the size of table\n";
    //cin >> size;
    srand((unsigned) time(0));

    Hash_chaining table;

    ofstream results;

    results.open("C:\\Users\\riso\\CLionProjects\\DSA1\\results.txt", ios::app);

    if (!results.is_open()) {
        cout << "File did not open" << endl;
        return;
    }
    //---------------------------------------------------------------------------------------------
    while (size <= 1000000) {

        //---------------------------------------------------------------------------------------------
        for (int i = 0; i < size; ++i) {

            char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

            int len = rand() % (11 - 5) + 5;
            randomS.reserve(len);

            for (int j = 0; j < len; ++j) {
                randomS += characters[rand() % (sizeof(characters) - 1)];
            }

            strings.push_back(randomS);
            randomS = "";
        }
        //---------------------------------------------------------------------------------------------

        auto start_insert = high_resolution_clock::now();

        while (check != size) {
            random = (rand() * rand()) % strings.size();
            table.insert(strings[random]);
            check++;
        }

        auto stop_insert = high_resolution_clock::now();
        auto duration_insert = duration_cast<nanoseconds>(stop_insert - start_insert);

        results << duration_insert.count() / 25000 << endl;

        //---------------------------------------------------------------------------------------------
/*
        check = 0;
        auto start_search = high_resolution_clock::now();

        while (check != size) {
            random = (rand() * rand()) % strings.size();
            table.search(strings[random]);
            strings[random].erase();
            check++;
        }

        auto stop_search = high_resolution_clock::now();
        auto duration_search = duration_cast<nanoseconds>(stop_search - start_search);

        results << duration_search.count() / size << endl;

        //---------------------------------------------------------------------------------------------

        check = 0;
        auto start_remove = high_resolution_clock::now();

        while (check != size) {
            random = (rand() * rand()) % strings.size();
            table.remove(strings[random]);
            strings[random].erase();
            check++;
        }

        auto stop_remove = high_resolution_clock::now();
        auto duration_remove = duration_cast<nanoseconds>(stop_remove - start_remove);

        results  << duration_remove.count() / size << endl;

        */
        size += 25000;
    }

    results << "############" << endl;
    results.close();
}

void Hash2_start() {

    string str, randomS, to_insert;
    vector<string> strings;
    int size = 25000, check = 0,flag = 1;
    //cout << "Enter the size of table\n";
    //cin >> size;
    srand((unsigned) time(0));

    Hash_linear table;

    ofstream results;

    results.open("C:\\Users\\riso\\CLionProjects\\DSA1\\results.txt", ios::app);

    if (!results.is_open()) {
        cout << "File did not open" << endl;
        return;
    }
    //---------------------------------------------------------------------------------------------
    while (size <= 1000000) {

        //---------------------------------------------------------------------------------------------
        for (int i = 0; i < size; ++i) {

            char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

            int len = rand() % (11 - 5) + 5;
            randomS.reserve(len);

            for (int j = 0; j < len; ++j) {
                randomS += characters[rand() % (sizeof(characters) - 1)];
            }

            strings.push_back(randomS);
            randomS = "";
        }
        //---------------------------------------------------------------------------------------------

        auto start_insert = high_resolution_clock::now();

        check = 0;

        while (check != size) {
            table.insert(strings.at(check));
            check++;
        }

        auto stop_insert = high_resolution_clock::now();
        auto duration_insert = duration_cast<nanoseconds>(stop_insert - start_insert);

        //results << duration_insert.count() / 25000 << endl;

        //---------------------------------------------------------------------------------------------
/*
        check = 0;
        auto start_search = high_resolution_clock::now();

        while (check != size) {
            table.search(strings.at(check));
            check++;
        }

        auto stop_search = high_resolution_clock::now();
        auto duration_search = duration_cast<nanoseconds>(stop_search - start_search);

        results << duration_search.count() / size << endl;

        //---------------------------------------------------------------------------------------------

        check = 0;
        auto start_remove = high_resolution_clock::now();

        while (check != size) {
            table.remove(strings.at(check));
            strings.at(check).erase();
            check++;
        }

        auto stop_remove = high_resolution_clock::now();
        auto duration_remove = duration_cast<nanoseconds>(stop_remove - start_remove);

        results  << duration_remove.count() / size << endl;

        //Hash_linear();
        //flag++;
        */
        size += 25000;
    }
    //table.display();
    results << "############" << endl;
    results.close();

}

int main() {

    int input;

    while (true) {
        cout << "Press 1 for AVL tree\nPress 2 for Splay tree\nPress 3 for Chaining table\nPress 4 for Linear probing table"
             << endl;
        cin >> input;

        switch (input) {

            case 1:
                AVL_start();
                break;

            case 2:
                Splay_start();
                break;

            case 3:
                Hash_start();
                break;

            case 4:
                Hash2_start();
                break;

            default:
                cout << "Invalid input" << endl;
                return 0;
        }
    }
}
