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

private:
    struct treeNode *rootp;
};
#endif

