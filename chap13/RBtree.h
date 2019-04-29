#ifndef _RBTREE_H_
#define _RBTREE_H_
#include <unistd.h>
#include <stdint.h>
#include "../init.h"
#include "../chap12/tree/tree.h"

#define RBTREE_MIN_SIZE         4
class RBtree:public Tree {
public:
    
    RBtree(void);
    ~RBtree(void);

    void inorderWalk(struct treeNode *x, void (* print)(void *datap)=NULL);
    void insert(struct treeNode *insp);    
    //struct treeNode * del(struct treeNode * delp);

private:
    void insertFixup(struct treeNode *z);
    void leftRotate(struct treeNode *x);
    void rightRotate(struct treeNode *x);
    void printNode(struct treeNode * x);

    struct treeNode *m_NILp;
    struct treeNode *m_tmp;
};
#endif


