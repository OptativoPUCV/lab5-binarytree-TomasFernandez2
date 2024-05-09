#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;

/*typedef struct Pair {
    void * key;
    void * value;
} Pair;*/

/* definimos una función para comparar claves de tipo int
int lower_than_int(void* key1, void* key2){
    int k1 = *((int*) (key1));
    int k2 = *((int*) (key2));
    return k1<k2;
}*/

struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) 
        return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap* tree, void* key, void* value) {
    if (tree == NULL) 
        return;
    if (searchTreeMap(tree, key) != NULL) 
        return;
    TreeNode* newNode = createTreeNode(key, value);
    if (newNode == NULL) 
        return;
    TreeNode* aux = tree->root;
    TreeNode* parent = NULL;
    while (aux != NULL) {
        parent = aux;
        if (tree->lower_than(key, aux->pair->key))
            aux = aux->left;
        else
            aux = aux->right;
    }
    newNode->parent = parent;
    if (parent == NULL)
        tree->root = newNode;
    else if (tree->lower_than(key, parent->pair->key))
        parent->left = newNode;
    else
        parent->right = newNode;
    tree->current = newNode;
}

TreeNode* minimum(TreeNode* x) {
    if (x == NULL) 
        return NULL;
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap *tree, TreeNode *node) {
    if (node == NULL)
        return;

    TreeNode *parent = node->parent;

    // Caso 1: Nodo sin hijos
    if (node->left == NULL && node->right == NULL) {
        if (parent == NULL) {
            // El nodo es la raíz del árbol
            tree->root = NULL;
        } else if (parent->left == node) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(node);
    }
    // Caso 2: Nodo con un hijo
    else if (node->left == NULL || node->right == NULL) {
        TreeNode *child = (node->left != NULL) ? node->left : node->right;
        if (parent == NULL) {
            // El nodo es la raíz del árbol
            tree->root = child;
        } else if (parent->left == node) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        child->parent = parent;
        free(node);
    }
    // Caso 3: Nodo con dos hijos
    else {
        TreeNode *successor = minimum(node->right);
        node->pair->key = successor->pair->key;
        node->pair->value = successor->pair->value;
        removeNode(tree, successor);
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode* aux = tree->root;
    while(aux!=NULL){
        if(is_equal(tree,aux->pair->key,key)){
            tree->current = aux;
            return aux->pair;
        }
        else if(tree->lower_than(aux->pair->key,key)) 
            aux = aux->right;
        else
            aux = aux->left;
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
