#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


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
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap *new = (TreeMap *)malloc(sizeof(TreeMap));
  if (!new) {
    EXIT_FAILURE;  
  }
  new->lower_than = lower_than;
  new->root = NULL;
  new->current = NULL;
  
  return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  TreeNode *aux = createTreeNode(key, value);
  if (tree->root == NULL) {
    aux = tree->root;
    aux = tree->current;
    return;
  }
  TreeNode *y = NULL;
  TreeNode *x = tree->root;
  while (x != NULL) {
    y = x;
    if (tree->lower_than(key, x->pair->key)) {
      x = x->left;
    }
    
  }
 
}

TreeNode * minimum(TreeNode * x){
  while (x->left != NULL) {
    x = x->left;
  }
  return x; 
}

void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
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
