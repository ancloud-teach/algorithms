#include "./tree.h"

Tree::Tree(void)
{
    this->rootp = NULL;
}

Tree::~Tree(void)
{

}

struct treeNode * Tree::getRoot(void)
{
    return this->rootp;
}
void Tree::insert(struct treeNode *insp)
{
    struct treeNode * y = NULL;
    struct treeNode * x = this->rootp;
    while (x != NULL) {
        y = x;
        if (insp->key < x->key)
            x = x->leftp;
        else 
            x = x->rightp;
    }
    insp->parentp = y;
    if (NULL == y) {
        this->rootp = insp;
    } else if (insp->key < y->key) {
        y->leftp = insp;
    } else {
        y->rightp = insp;
    }
}

void Tree::inorderWalk(struct treeNode *x)
{
    if (NULL == x) 
        return ;
    this->inorderWalk(x->leftp);
    
    printf("node: %d\n", x->key);

    this->inorderWalk(x->rightp);
}

