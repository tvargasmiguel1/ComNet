#include "Routes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Function to initialize a route node with a copied key and value for safe memory management
struct Route * initializeRoute(char* key, char* value) {
    struct Route * temp = (struct Route *) malloc(sizeof(struct Route));
    if (temp == NULL) {
        perror("Failed to allocate memory for route");
        return NULL;
    }

    temp->key = strdup(key);
    if (temp->key == NULL) {
        free(temp);
        perror("Failed to duplicate key");
        return NULL;
    }

    temp->value = strdup(value);
    if (temp->value == NULL) {
        free(temp->key);
        free(temp);
        perror("Failed to duplicate value");
        return NULL;
    }

    temp->left = temp->right = NULL;
    return temp;
}

// Function to perform an inorder traversal of the BST and print the key-value pairs
void inorder(struct Route* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%s -> %s \n", root->key, root->value);
        inorder(root->right);
    }
}

// Helper function to insert a new node into the BST
struct Route * addRouteHelper(struct Route * root, char* key, char* value) {
    if (root == NULL) {
        return initializeRoute(key, value);
    }

    int cmp = strcmp(key, root->key);
    if (cmp == 0) {
        printf("============ WARNING ============\n");
        printf("A Route For \"%s\" Already Exists\n", key);
    } else if (cmp > 0) {
        root->right = addRouteHelper(root->right, key, value);
    } else {
        root->left = addRouteHelper(root->left, key, value);
    }
    return root;
}

struct Route * addRoute(struct Route * root, char* key, char* value) {
    return addRouteHelper(root, key, value);
}

// Function to search for a route in the BST
struct Route * search(struct Route * root, char* key) {
    while (root != NULL) {
        int cmp = strcmp(key, root->key);
        if (cmp == 0) {
            return root;
        } else if (cmp > 0) {
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return NULL;
}
