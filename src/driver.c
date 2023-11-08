#include <stdio.h>
#include "rbtree.h"
#include "helper.h"

int main(int argc, char *argv[]) {
    rbtree *tree=new_rbtree();
    rbtree_insert(tree,10);
    rbtree_insert(tree,5);
    rbtree_insert(tree,6);
    printPreOrder(tree); 
    rbtree_erase(tree,rbtree_find(tree,5));
    printPreOrder(tree);
}