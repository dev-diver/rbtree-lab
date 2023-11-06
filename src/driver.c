#include <stdio.h>
#include "rbtree.h"
#include "helper.h"

int main(int argc, char *argv[]) {
    rbtree *tree=new_rbtree();
    rbtree_insert(tree,10);
    rbtree_insert(tree,5);
    rbtree_insert(tree,6);
    // printPreOrder(tree); 
    // printf("값 찾기: %d\n",rbtree_find(tree,10)->key);
}