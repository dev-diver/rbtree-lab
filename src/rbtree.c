#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"
#include "helper.h"

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil =(node_t *)calloc(1,sizeof(node_t));
  node_t nilNode = {RBTREE_BLACK,0,0,0,0};
  *nil = nilNode;

  p->nil = nil;
  p->root = nil;
  return p;

}

void printPreOrder(rbtree *tree) {
  printf("프린트 시작\n");
  preOrder(tree, tree->root);
}

void preOrder(rbtree *tree, node_t* nowNode) {
  if(nowNode == tree->nil) return;

  char *color;
  if (nowNode->color==RBTREE_RED){
    color="R";
  }else{
    color="B";
  }
  char *leftColor = nowNode->left->color==RBTREE_BLACK ? "B":"R";
  char *rightColor = nowNode->right->color==RBTREE_BLACK ? "B":"R";
  
  char leftKey[10] ="o";
  char rightKey[10] ="o";
  if(nowNode->left!=tree->nil) sprintf(leftKey,"%d",nowNode->left->key);
  if(nowNode->right!=tree->nil) sprintf(rightKey,"%d",nowNode->right->key);
  printf("%s(%s)/%d(%s)\\%s(%s)\n",leftKey,leftColor,nowNode->key,color,rightKey,rightColor);
  preOrder(tree, nowNode->left);
  preOrder(tree, nowNode->right);
  return;
}

void delete_rbtree(rbtree *t) {
  //printPreOrder(t);
  postOrderDelete(t,t->root);
  free(t);
  printf("\n삭제 완료\n");
}

void postOrderDelete(rbtree *t, node_t* n){
  if(n == t->nil) return;
  postOrderDelete(t,n->left);
  postOrderDelete(t,n->right);
  printf("(%d 삭제)",n->key);
  rbtree_erase(t,n);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {

  node_t node = {RBTREE_RED,key,t->nil,t->nil,t->nil};
  node_t *newNode = (node_t *)calloc(1, sizeof(node_t));
  *newNode = node;

  node_t *x = t->root;
  node_t *y = x;

  if(t->root==t->nil) { //요소 없을 때
    t->root = newNode;
    newNode->color = RBTREE_BLACK;
  }else{
    while(x != t->nil){//자리 찾기
      y = x;
      if(key <= x->key){
        x = x->left;
      }else{
        x = x->right;
      }
    }

    if(key <= y->key){ //삽입
      y->left = newNode;
    }else{
      y->right = newNode;
    }
    newNode->parent = y;

    if(y->color == RBTREE_RED){
      rbtree_fixup(t,newNode); //RBtree 규칙 조정
    }
  }
  return t->root;
}

void rbtree_fixup(rbtree *t, node_t *n){
  while(n->parent->color == RBTREE_RED){ //부모의 색을 계속 체크
    if (n->parent == n->parent->parent->left){ //부모가 왼쪽인 경우
      node_t *uncle = n->parent->parent->right;
      if(uncle->color == RBTREE_RED){//case 1
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
      if(uncle->color == RBTREE_RED){//case 1
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
  if(y->left != t->nil){
    y->left->parent = n;
  }
  y->parent = n->parent;
  if(n->parent == t->nil){
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
  if(y->right != t->nil){
    y->right->parent = n;
  }
  y->parent = n->parent;
  if(n->parent == t->nil){
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
  if(key==t->root->key){
    return n;
  }
  while(n!=t->nil && n->key != key){
    if(key <= n->key){
      n = n->left;
    }else{
      n = n->right;
    }
  }
  return n==t->nil ? 0:n;
}

node_t *rbtree_min(const rbtree *t) {
  
  node_t *x = t->root;
  node_t *y;
  while(x!=t->nil){
    y=x;
    x=x->left;
  }
  return y;
}

node_t *rbtree_max(const rbtree *t) {
  node_t *x = t->root;
  node_t *y;
  while(x!=t->nil){
    y=x;
    x=x->right;
  }
  return y;
}

//u를 v로 교체 (u는 삭제)
void rb_transplant(rbtree* tree, node_t * u, node_t* v){
  if(u->parent == tree->nil){ //u가 루트일 때
    tree->root = v;
  }else if(u==u->parent->left){ //u 가 왼쪽 자식일 때
    u->parent->left = v;
  }else{ //u 가 오른쪽 자식일 때
    u->parent->right = v;
  }
  v->parent = u->parent;
}

int rbtree_erase(rbtree *t, node_t *p) {
  
  node_t *x; //주목 노드
  node_t *y = p;
  color_t y_ori_color = y->color;
  if (p->left==t->nil){  //left 없는 경우
    x = p->right;
    x->parent = p;//for nil;
    rb_transplant(t,p,p->right);  
  }else if(p->right == t->nil){ //right 없는 경우
    x = p->left;
    x->parent = p; //for nil;
    rb_transplant(t,p,p->left);
  }else{  //둘 다 있는 경우
    y = rbtree_minimum(t,p->right);
    y_ori_color = y->color;
    x = y->right;
    x->parent = y; //for nil
    if(y->parent == p){
      x->parent = y;
    }else{
      rb_transplant(t,y,y->right);
      y->right = p->right;
      y->right->parent = y;
    }
    rb_transplant(t,p,y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
  }
  if(y_ori_color == RBTREE_BLACK){
    rb_erase_fixup(t,x);
  }
  free(p);
  return 0;
}

void rb_erase_fixup(rbtree *tree, node_t *x){

  node_t *w; //uncle

  while(x != tree->root && x->color==RBTREE_BLACK){
    if(x == x->parent->left){//왼쪽일 때
      w = x->parent->right;
      if(w->color == RBTREE_RED){ //case1
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_BLACK;
        left_rotate(tree,x->parent);
        w = x->parent->right;  //uncle 재설정 하고 case 2,3,4
      }
      //밑에부터 uncle이 흑색인 케이스 (2,3,4)
      //case2
      if(w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        // x->parent->color = RBTREE_BLACK;
        x = x->parent;  //루프 지속
      }else{//case 3,4
        //case3
        if(w->right->color==RBTREE_BLACK){ //왼쪽 자식 안 따져도 됨(둘다 흑색 아니므로)
          w->color = RBTREE_RED;
          w->left->color = RBTREE_BLACK;
          right_rotate(tree,w);
        }//case4로 전환
        w->color = w->parent->color;
        w->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(tree,x->parent);
        x = tree->root;  //루프 종료 위해 설정
      } 
    }else{
      w = x->parent->left;
      if(w->color == RBTREE_RED){ //case1
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_BLACK;
        right_rotate(tree,x->parent);
        w = x->parent->left;  //uncle 재설정 하고 case 2,3,4
      }
      //밑에부터 uncle이 흑색인 케이스 (2,3,4)
      //case2
      if(w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        // x->parent->color = RBTREE_BLACK;
        x = x->parent;  //루프 지속
      }else{//case 3,4
        //case3
        if(w->left->color==RBTREE_BLACK){ //왼쪽 자식 안 따져도 됨(둘다 흑색 아니므로)
          w->color = RBTREE_RED;
          w->right->color = RBTREE_BLACK;
          left_rotate(tree,w);
        }//case4로 전환
        w->color = w->parent->color;
        w->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(tree,x->parent);
        x = tree->root;  //루프 종료 위해 설정
      } 
    }
  }
  x->color = RBTREE_BLACK;
}

node_t * rbtree_minimum(rbtree *t, node_t *x){
  while(x->left!=t->nil){
    x = x->left;
  }
  return x;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
