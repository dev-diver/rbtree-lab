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
  
  char leftKey[10] ="o";
  char rightKey[10] ="o";
  if(n->left!=0) sprintf(leftKey,"%d",n->left->key);
  if(n->right!=0) sprintf(rightKey,"%d",n->right->key);
  printf("%s/(%s %d)\\%s\n",leftKey,color,n->key,rightKey);
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
  node_t *y = x;

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

    if(y->color == RBTREE_RED){
      rbtree_fixup(t,newNode);
    }
  }
  return t->root;
}

void rbtree_fixup(rbtree *t, node_t *n){
  while(n->parent!=0 && n->parent->color == RBTREE_RED){ //부모의 색을 계속 체크
    if (n->parent == n->parent->parent->left){ //부모가 왼쪽인 경우
      node_t *uncle = n->parent->parent->right;
      if(uncle!=0 && uncle->color == RBTREE_RED){//case 1
        uncle->color = RBTREE_BLACK;
        n->parent->color = RBTREE_BLACK;
        n->parent->parent->color = RBTREE_RED;
        n = n->parent->parent;
      }else{ //case2,3
        if(n == n->parent->right){ //case2
          n = n->parent;
          left_rotate(t,n);
        }
        n->parent->color = RBTREE_BLACK;
        n->parent->parent->color = RBTREE_RED;
        right_rotate(t,n->parent->parent);
        //case3
      }
    }else{ //부모가 왼쪽인 경우
      node_t *uncle = n->parent->parent->left;
      if(uncle!=0 && uncle->color == RBTREE_RED){//case 1
        uncle->color = RBTREE_BLACK;
        n->parent->color = RBTREE_BLACK;
        n->parent->parent->color = RBTREE_RED;
        n = n->parent->parent;
      }else{ //case2,3
        if(n == n->parent->left){ //case2
          n = n->parent;
          right_rotate(t,n);
        }
        n->parent->color = RBTREE_BLACK;
        n->parent->parent->color = RBTREE_RED;
        left_rotate(t,n->parent->parent);
        //case3
      }
    }
  }
  t->root->color = RBTREE_BLACK;

}

void left_rotate(rbtree *t, node_t *n){
  node_t *y = n->right;
  n->right = y->left;
  if(y->left != 0){
    y->left->parent = n;
  }
  y->parent = n->parent;
  if(n->parent == 0){
    t->root = y;
  }else if(n == n->parent->left){
    n->parent->left = y;
  }else{
    n->parent->right = y;
  }
  y->left = n;
  n->parent = y;
}

void right_rotate(rbtree *t, node_t *n){
  node_t *y = n->left;
  n->left = y->right;
  if(y->right != 0){
    y->right->parent = n;
  }
  y->parent = n->parent;
  if(n->parent == 0){
    t->root = y;
  }else if(n == n->parent->right){
    n->parent->right = y;
  }else{
    n->parent->left = y;
  }
  y->right = n;
  n->parent = y;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *n = t->root;
  while(n!=0 && n->key != key){
    if(key <= n->key){
      n = n->left;
    }else{
      n = n->right;
    }
  }
  return n;
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
