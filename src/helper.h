#ifndef _HELPER_H_
#define _HELPER_H_

#include "rbtree.h"

void printPreOrder(rbtree *);
void preOrder(rbtree *,node_t *);
void postOrderDelete(rbtree *, node_t *);
void rbtree_fixup(rbtree *, node_t *);
void right_rotate(rbtree *, node_t *);
void left_rotate(rbtree *, node_t *);

#endif //_HELPER_H_