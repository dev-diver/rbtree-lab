#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"
#include "helper.h"

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  
  p->nil = 0;
  p->root = 0;
  return p;

}

void printPreOrder(rbtree *tree) {
  printf("프린트 시작\n");
  preOrder(tree->root);
}

void preOrder(node_t* n) {
  if(n == 0) return;

  char *color;
  if (n->color==RBTREE_RED){
    color="RED";
  }else{
    color="BLK";
  }
  printf("(%s %d)\n",color,n->key);
  preOrder(n->left);
  preOrder(n->right);
  return;
}

void delete_rbtree(rbtree *t) {
  postOrderDelete(t->root);
  free(t);
  printf("\n삭제 완료\n");
}

void postOrderDelete(node_t* n){
  if(n == 0) return;
  postOrderDelete(n->left);
  postOrderDelete(n->right);
  printf("(%d 삭제)",n->key);
  free(n);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {

  node_t *newNode = (node_t *)calloc(1, sizeof(node_t));
  newNode->color = RBTREE_RED;
  newNode->key = key;
  newNode->parent = 0;
  newNode->left = 0;
  newNode->right = 0;

  node_t *x = t->root;
  node_t *y;

  if(t->root==0) {
    t->root = newNode;
    newNode->color = RBTREE_BLACK;
  }else{
    while(x != 0){
      y = x;
      if(key <= x->key){
        x = x->left;
      }else{
        x = x->right;
      }
    }
    if(key <= y->key){
      y->left = newNode;
    }else{
      y->right = newNode;
    }
    newNode->parent = y;
    
  }

  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
