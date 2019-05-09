#ifndef _TREE_H_
#define _TREE_H_
#include <unistd.h>
#include <stdint.h>

enum RBColor {
    BLACK=0,
    RED
};
struct treeNode {
    uint32_t key;
    struct treeNode *leftp;
    struct treeNode *rightp;
    struct treeNode *nextp;
    struct treeNode *parentp;

    enum RBColor color;

    void * datap;
};


class Tree {
public:
    
    Tree(void);
    ~Tree(void);
    struct treeNode * getRoot(void);    
    void inorderWalk(struct treeNode *x, void (* print)(void *datap));
    struct treeNode * inorderWalk(struct treeNode *lastp);
    void insert(struct treeNode *insp);
    struct treeNode * search(struct treeNode *x, uint32_t const key);
    struct treeNode * min(struct treeNode *x);
    struct treeNode * max(struct treeNode *x);
    struct treeNode * successor(struct treeNode *x);
    struct treeNode * predecessor(struct treeNode *x);
    
    struct treeNode * del(struct treeNode * delp);

protected:
    struct treeNode *m_rootp;
    uint32_t m_size;

    void transplant(struct treeNode *dstp, struct treeNode *srcp);
};
#endif

