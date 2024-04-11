#include <stdlib.h>
#include <string.h>

// Define a structure for a node in the binary search tree
struct Route {
    char* key;          // Key (route) stored in the node
    char* value;        // Value associated with the key
    struct Route *left; // Pointer to the left child node
    struct Route *right;// Pointer to the right child node
};

// Function declarations

// Function to initialize a route node with given key and value
struct Route * initializeRoute(char* key, char* value);

// Function to add a new route to the BST
struct Route * addRoute(struct Route * root, char* key, char* value);

// Function to search for a route in the BST
struct Route * search(struct Route * root, char * key);

// Function to perform an inorder traversal of the BST
void inorder(struct Route * root);