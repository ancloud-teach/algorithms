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
    
    printf("node(0x%X): %d\n", (uint32_t)x, x->key);

    this->inorderWalk(x->rightp);
}

/*
struct treeNode * Tree::search(struct treeNode *x, uint32_t const key)
{
    if (NULL == x || key == x->key)
        return x;

    if (key < x->key)
        return this->search(x->leftp, key);
    else 
        return this->search(x->rightp, key);
}
*/
struct treeNode * Tree::search(uint32_t const key)
{
    struct treeNode *x = this->rootp;
    
    while (x != NULL) {
        if (key == x->key)
            break;
        
        if (key < x->key)
            x = x->leftp;
        else 
            x = x->rightp;
    }

    return x;
}

struct treeNode * Tree::min(void)
{
    if (NULL == this->rootp)
        return NULL;
    
    struct treeNode *nodep = this->rootp;
    while (NULL != nodep->leftp) {
        nodep = nodep->leftp;
    }
    return nodep;
}

struct treeNode * Tree::max(void)
{
    if (NULL == this->rootp)
        return NULL;
    
    struct treeNode *nodep = this->rootp;
    while (NULL != nodep->rightp) {
        nodep = nodep->rightp;
    }
    return nodep;
}


