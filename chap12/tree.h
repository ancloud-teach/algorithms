#ifndef _TREE_H_
#define _TREE_H_
#include <unistd.h>
#include <stdint.h>
#include "../init.h"

struct treeNode {
    uint32_t key;
    struct treeNode *leftp;
    struct treeNode *rightp;
    struct treeNode *parentp;

    void * datap;
};

class Tree {
public:
    
    Tree(void);
    ~Tree(void);
    struct treeNode * getRoot(void);    
    void inorderWalk(struct treeNode *x);
    void insert(struct treeNode *insp);
    struct treeNode * search(struct treeNode *x, uint32_t const key);
    struct treeNode * min(struct treeNode *x);
    struct treeNode * max(struct treeNode *x);
    struct treeNode * successor(struct treeNode *x);
    struct treeNode * predecessor(struct treeNode *x);
    
    struct treeNode * del(struct treeNode * delp);

private:
    struct treeNode *m_rootp;

    void transplant(struct treeNode *dstp, struct treeNode *srcp);
};
#endif

