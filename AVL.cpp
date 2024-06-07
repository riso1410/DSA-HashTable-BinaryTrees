#include <iostream>
#include <algorithm>

using namespace std;


class AVL_BST {

private:
    struct node {
        int value;
        string word;
        int height;
        node *left;
        node *right;
    };


    //zistenie vysky prvku v strome vola sa pri insert_node() a difference() aby sa zistila vyska dalsieho prvku
    int height_node(node *root) {

        if (root != nullptr) {
            return root->height;
        } else {
            return 0;
        }
    }

    //vytvorenie noveho prvku, vola sa pri insert_node
    node *new_node(int input, string word) {

        node *temp = new node;
        temp->value = input;
        temp->word = word;
        temp->height = 1;
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

        root->height = max(height_node(root->left), height_node(root->right)) + 1;
        temp0->height = max(height_node(temp0->left), height_node(temp0->right)) + 1;

        return temp0;
    }

    //otocenie dolava
    node *left_rotate(node *root) {


        node *temp0 = root->right;
        node *temp1 = temp0->left;

        temp0->left = root;
        root->right = temp1;

        root->height = max(height_node(root->left), height_node(root->right)) + 1;
        temp0->height = max(height_node(temp0->left), height_node(temp0->right)) + 1;

        return temp0;

    }

    int balance(node *root) {
        if (root == nullptr) {
            return 0;
        }
        return (height_node(root->left) - height_node(root->right));
    }

    //rekurzivny alg na pridavanie prvkov do stromu
    node *insert_node(node *root, int value, string word) {

        if (root == nullptr) {
            return new_node(value, word);
        } else if (value < root->value) {

            root->left = insert_node(root->left, value, word);
            root->height = max(height_node(root->left), height_node(root->right)) + 1;

            if (balance(root) > 1) {
                //left left
                if (value < root->left->value) {
                    return right_rotate(root);
                }
                //left right
                else {
                    root->left = left_rotate(root->left);
                    return right_rotate(root);
                }
            }
        } else if (value > root->value) {

            root->right = insert_node(root->right, value, word);
            root->height = max(height_node(root->left), height_node(root->right)) + 1;

            if (balance(root) < -1) {
                //right right
                if (value > root->right->value) {
                    return left_rotate(root);
                }
                    //right left
                else {
                    root->right = right_rotate(root->right);
                    return left_rotate(root);
                }
            }
        } else if (value == root->value) {
            return root;
        }
        return root;
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
                return root;
            } else if (root->value < value) {
                root = root->right;
            } else if (root->value > value) {
                root = root->left;
            }
        }
        return root;
    }

    //najmensi vacsi prvok
    node *successor_node(node *root) {

        while (root->left != nullptr) {
            root = root->left;
        }

        return root;
    }

    //rekurzivne mazanie
    node *delete_node(node *root, int value) {

        node *tmp;

        if (root == nullptr) {
            return nullptr;
        } else if (value < root->value) {
            root->left = delete_node(root->left, value);
        } else if (value > root->value) {
            root->right = delete_node(root->right, value);
        } else {
            //ak ma 2 child nody
            if ((root->left != nullptr) && (root->right != nullptr)) {
                tmp = successor_node(root->right);
                root->value = tmp->value;
                root->right = delete_node(root->right, root->value);

            }
                //ak ma aspon 1 child node
            else if ((root->left == nullptr) || (root->right == nullptr)) {

                tmp = root;
                //ak je Lchild null tak Rchild sa prida do root a naopak, ak su obe null tak sa iba vymaze
                if (root->left == nullptr) {
                    root = root->right;
                } else if (root->right == nullptr) {
                    root = root->left;
                }
                delete tmp;
            }
        }
        //ak je prazdny
        if (root == nullptr) {
            return root;
        }

        root->height = max(height_node(root->left), height_node(root->right)) + 1;

        //vybalancovanie
        if (balance(root) > 1) {
            if (balance(root->left) > 0) {
                return right_rotate(root);
            } else {
                root->left = left_rotate(root->left);
                return right_rotate(root);
            }
        }
        if (balance(root) < -1) {
            if (balance(root->right) < 0) {
                return left_rotate(root);
            } else {
                root->right = right_rotate(root->right);
                return left_rotate(root);
            }
        }

        return root;
    }

public:

    node *root;

    AVL_BST() { root = nullptr; }

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
