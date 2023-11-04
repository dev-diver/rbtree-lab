#include <stdio.h>
#include "rbtree.h"
#include "helper.h"

int main(int argc, char *argv[]) {
    rbtree *tree=new_rbtree();
    printPreOrder(tree);
    rbtree_insert(tree,10);
    rbtree_insert(tree,20);
    rbtree_insert(tree,1);
    rbtree_insert(tree,30);
    rbtree_insert(tree,3);
    rbtree_insert(tree,5);
    rbtree_insert(tree,11);
    printPreOrder(tree);
    delete_rbtree(tree);
    printPreOrder(tree);
}