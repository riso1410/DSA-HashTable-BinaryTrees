#include <iostream>
#include <algorithm>

using namespace std;


class Splay_BST {

    struct node {
        int value;
        string word;
        node *left;
        node *right;
    };

    //vytvorenie noveho prvku, vola sa pri insert_node
    node *new_node(int input, string word) {

        node *temp = new node;
        temp->word = word;
        temp->value = input;
        temp->left = nullptr;
        temp->right = nullptr;

        return temp;

    }

    //otocenie doprava
    node *right_rotate(node *root) {

        node *temp0 = root->left;
        node *temp1 = temp0->right;

        temp0->right = root;
        root->left = temp1;

        return temp0;
    }

    //otocenie dolava
    node *left_rotate(node *root) {

        node *temp0 = root->right;
        node *temp1 = temp0->left;

        temp0->left = root;
        root->right = temp1;

        return temp0;

    }

    node *splaying(node *root, int value) {

        //ak je strom prazdny alebo je hodnota uz v roote
        if (!root|| root->value == value)
            return root;

        //lava vetva
        if (root->value > value) {
            //ak nie je v strome
            if (!root->left)
                return root;

            //left-left
            if (root->left->value > value) {
                root->left->left = splaying(root->left->left, value);
                root = right_rotate(root);

            }
            //left-right
            else if (root->left->value < value) {
                root->left->right = splaying(root->left->right, value);
                //rotacia pre root
                if (root->left->right)
                    root->left = left_rotate(root->left);
            }
            //rotacia pre root
            if (!root->left) {
                return root;
            }
            return right_rotate(root);
        }

        //prava vetva
        else {
            //ak nie je v strome
            if (!root->right)
                return root;

            //right-left
            if (root->right->value > value) {
                root->right->left = splaying(root->right->left, value);

                //rotacia pre root
                if (root->right->left)
                    root->right = right_rotate(root->right);

            }
            //right-right
            else if (root->right->value < value) {
                root->right->right = splaying(root->right->right, value);
                root = left_rotate(root);
            }

            //rotacia pre root
            if (!root->right) {
                return root;
            }
            return left_rotate(root);

        }
    }

    //pridavanie prvkov do stromu
    node *insert_node(node *root, int value, string word) {

        if (root == nullptr) {
            return new_node(value, word);
        }

        //splayovanie
        root = splaying(root, value);

        if (value == root->value) {
            return root;
        }

        node *new_root = new_node(value, word);

        //pripojenie rootu pod novy root
        if (root->value > value) {
            new_root->right = root;
            new_root->left = root->left;
            root->left = nullptr;
        }

        else {
            new_root->left = root;
            new_root->right = root->right;
            root->right = nullptr;
        }

        return new_root;
    }

    //vypis postupuje z rootu nasledne dolava kym sa da a potom prechadza doprava
    void print_tree_preorder(node *root) {

        if (root != nullptr) {
            cout << root->value << ": " << root->word << endl;
            print_tree_preorder(root->left);
            print_tree_preorder(root->right);
        }
    }

    //iterativny sposob na najdenie prvku v strome
    node *search_node(node *root, int value) {

        while (root != nullptr) {

            if (root->value == value) {
                //cout << word << endl;
                return splaying(root, value);
            } else if (root->value < value) {
                root = root->right;
            } else if (root->value > value) {
                root = root->left;
            }
        }

        return root;
    }

    //rekurzivne mazanie
    node *delete_node(node *root, int value) {
        node *tmp;

        if (root == nullptr) {
            return nullptr;
        }

        root = splaying(root, value);

        if (root->value != value) {
            return root;
        }

        //no right child
        if (root->right == nullptr) {
            tmp = root->left;
            delete root;
            return tmp;
        }
        //no left child
        else if (root->left == nullptr) {
            tmp = root->right;
            delete root;
            return tmp;
        }
        //both children
        else {
            tmp = root;
            root = splaying(root->left, value);
            root->right = tmp->right;
            delete tmp;
            return root;
        }
    }

public:

    node *root;

    Splay_BST() { root = nullptr; }

    void insert(int input, string word) {
        //cout << input << endl;
        root = insert_node(root, input, word);
    }

    void preorder() {
        print_tree_preorder(root);
    }

    void search(int input) {
        search_node(root, input);
    }

    void remove(int input) {
        root = delete_node(root, input);
    }
};