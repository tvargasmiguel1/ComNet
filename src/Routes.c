#include "Routes.h" 
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 

// Function to initialize a route node with the given key and value
struct Route * initializeRoute(char* key, char* value) {
    // Allocate memory for a new route node
    struct Route * temp = (struct Route *) malloc(sizeof(struct Route));

    // Set the key and value fields of the route node
    temp->key = key;
    temp->value = value;

    // Initialize left and right child pointers to NULL
    temp->left = temp->right = NULL;

    // Return the initialized route node
    return temp;
}

// Function to perform an inorder traversal of the binary search tree rooted at root and print the key-value pairs of each route
void inorder(struct Route* root) {
    if (root != NULL) {
        // Recursively traverse the left subtree
        inorder(root->left);
        
        // Print the key-value pair of the current route node
        printf("%s -> %s \n", root->key, root->value);
        
        // Recursively traverse the right subtree
        inorder(root->right);
    }
}

// Function to add a new route with the given key and value to the binary search tree rooted at root
struct Route * addRoute(struct Route * root, char* key, char* value) {
    if (root == NULL) {
        // If the tree is empty, create a new route node and return it
        return initializeRoute(key, value);
    }

    // Compare the key of the new route with the key of the current route
    if (strcmp(key, root->key) == 0) {
        // If the keys are equal, print a warning message
        printf("============ WARNING ============\n");
        printf("A Route For \"%s\" Already Exists\n", key);
    } else if (strcmp(key, root->key) > 0) {
        // If the new key is greater than the current key, recursively add the route to the right subtree
        root->right = addRoute(root->right, key, value);
    } else {
        // If the new key is less than the current key, recursively add the route to the left subtree
        root->left = addRoute(root->left, key, value);
    }

    // Return the root of the modified binary search tree
    return root;
}

// Function to search for a route with the given key in the binary search tree rooted at root
struct Route * search(struct Route * root, char* key) {
    if (root == NULL) {
        // If the tree is empty or the key is not found, return NULL
        return NULL;
    } 

    // Compare the key of the current route with the given key
    if (strcmp(key, root->key) == 0) {
        // If the keys are equal, return the current route
        return root;
    } else if (strcmp(key, root->key) > 0) {
        // If the given key is greater than the current key, recursively search the right subtree
        return search(root->right, key);
    } else if (strcmp(key, root->key) < 0) {
        // If the given key is less than the current key, recursively search the left subtree
        return search(root->left, key);
    }

    // Return the found route
    return root;
}
