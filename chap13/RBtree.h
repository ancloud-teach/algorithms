#ifndef _RBTREE_H_
#define _RBTREE_H_
#include <unistd.h>
#include <stdint.h>
#include "../init.h"
#include "../chap12/tree/tree.h"

#define RBTREE_MIN_SIZE         4
class RBtree {
public:
    
    RBtree(void);
    ~RBtree(void);

    struct treeNode * getRoot(void);
    struct treeNode * search(struct treeNode *x, uint32_t const key);
    struct treeNode * min(struct treeNode *x);
    struct treeNode * max(struct treeNode *x);
    struct treeNode * successor(struct treeNode *x);
    struct treeNode * predecessor(struct treeNode *x);
    void inorderWalk(struct treeNode *x, void (* print)(void *datap)=NULL);
    void insert(struct treeNode *insp);    
    struct treeNode * del(struct treeNode * nodep);

private:
    void insertFixup(struct treeNode *z);
    void leftRotate(struct treeNode *x);
    void rightRotate(struct treeNode *x);
    void printNode(struct treeNode * x);
    void transplant(struct treeNode *dstp, struct treeNode *srcp);
    void delFixUp(struct treeNode *nodep, struct treeNode *parentp);

    struct treeNode *m_rootp;
    struct treeNode *m_NILp;
    struct treeNode *m_tmp;
    int m_size;
};
#endif


