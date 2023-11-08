#include <stdio.h>
#include "rbtree.h"
#include "helper.h"

int main(int argc, char *argv[]) {
    rbtree *tree=new_rbtree();
    int arr[10] = {3,1,5,0,10,2147483647,20,7,1,100};
    for(int i=0; i<10; i++){
        rbtree_insert(tree,arr[i]);
    }

    for (int i = 0; i < 10; i++) {
        node_t *p = rbtree_find(tree, arr[i]);
        // printf("arr[%d] = %d\n", i, arr[i]);
        rbtree_erase(tree, p);
        printPreOrder(tree);
    }
}