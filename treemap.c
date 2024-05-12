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
  TreeNode *nodo = createTreeNode(key, value);
  if (tree == NULL) {
    tree->root = nodo;
    tree->current = nodo;
    return;
  }
  TreeNode *aux = tree->root;
  while (aux != NULL) {
    if (tree->lower_than(key, aux->pair->key)) {
      if (aux->left == NULL) {
        aux->left = nodo;
        nodo->parent = aux;
        tree->current = nodo;
      }
      aux = aux->left;
    }
    else if (is_equal(tree, aux->pair->key, key)) {
      aux->pair->value = value;
      tree->current = aux;
      return;
    }
    else {
      if (aux->right == NULL) {
        aux->right = nodo;
        nodo->parent = aux;
        tree->current = nodo;
      }
      aux = aux->right;
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
  /*if (node == NULL)
    return;

  if (node->left == NULL && node->right == NULL) {
    if (node->parent != NULL) {
      if (node->parent->left == node) {
        node->parent->left = NULL;
      } else {
        node->parent->right = NULL;
      }
    } else {
      tree->root = NULL;
    }
    free(node);
  } else if (node->left == NULL || node->right == NULL) {
    TreeNode *hijo;
    if (node->left != NULL) {
      hijo = node->left;
    } else {
      hijo = node->right;
    }
    if (node->parent != NULL) {
      if (node->parent->left == node) {
        node->parent->left = hijo;
      } else {
        node->parent->right = hijo;
      }
      hijo->parent = node->parent;
    } else {
      tree->root = hijo;
      hijo->parent = NULL;
    }
    free(node);
  } else {
    TreeNode *aux = minimum(node->right);
    node->pair = aux->pair;
    removeNode(tree, aux);
  }*/
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);
}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  if (tree == NULL || tree->root == NULL) return NULL;
  
  TreeNode *aux = tree->root;
  
  while (aux != NULL) {
    if (is_equal(tree, aux->pair->key, key)) {
        tree->current = aux;
        return aux->pair;
    }
    else if (tree->lower_than(key, aux->pair->key)) { //???
        aux = aux->left;
    }
    else {
      aux = aux->right;
    }
  }
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
  if (searchTreeMap(tree, key) != NULL)
    return tree->current->pair;
  
  TreeNode *aux = minimum(tree->root);
  TreeNode *menor = NULL;
  while (aux != NULL) {
    if (tree->lower_than(key, aux->pair->key)) {
      menor = aux;
      aux = aux->right;
    }
    else {
      aux = aux->left;
    }
  }
  return menor->pair;
}

Pair * firstTreeMap(TreeMap * tree) {
  TreeNode *aux = tree->root;
  if (aux == NULL) return NULL;
  tree->current = minimum(aux);
  
  return tree->current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  if(tree == NULL) 
    return NULL;
  
  TreeNode *next = tree->current;
  if(next == tree->root || next->right != NULL) {
    next = minimum(next->right);
    tree->current = next;
    return tree->current->pair;
  } 
  else if(next->right == NULL) {
    TreeNode *temp = next;
    while(next->parent != NULL) {
      temp = next;
      next = next->parent;
      if(next->left == temp) {
        tree->current = next;
        return tree->current->pair;
      }
    }
    return NULL;
  }
  return NULL;
  
}
