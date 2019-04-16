#include "./tree.h"

Tree::Tree(void)
{
    this->m_rootp = NULL;
}

Tree::~Tree(void)
{

}

struct treeNode * Tree::getRoot(void)
{
    return this->m_rootp;
}
void Tree::insert(struct treeNode *insp)
{
    struct treeNode * y = NULL;
    struct treeNode * x = this->m_rootp;
    while (x != NULL) {
        y = x;
        if (insp->key < x->key)
            x = x->leftp;
        else 
            x = x->rightp;
    }
    insp->parentp = y;
    if (NULL == y) {
        this->m_rootp = insp;
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
struct treeNode * Tree::search(struct treeNode *x, uint32_t const key)
{    
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

struct treeNode * Tree::min(struct treeNode *x)
{
    if (NULL == x)
        return NULL;
    
    while (NULL != x->leftp) {
        x = x->leftp;
    }
    return x;
}

struct treeNode * Tree::max(struct treeNode *x)
{
    if (NULL == x)
        return NULL;
    
    while (NULL != x->rightp) {
        x = x->rightp;
    }
    return x;
}

/*
 * find the node, whose key > x->key and the node is the min key 
 */
struct treeNode * Tree::successor(struct treeNode *x)
{
    if (NULL == x)
        return NULL;
    
    if (NULL != x->rightp)
        return this->min(x->rightp);

    struct treeNode *parentp= x->parentp;
    while (NULL!= parentp && x == parentp->rightp){
        x = parentp;
        parentp = x->parentp;
    }

    return parentp;
}

struct treeNode * Tree::predecessor(struct treeNode *x)
{
    if (NULL == x)
        return NULL;
    
    if (NULL != x->leftp)
        return this->max(x->leftp);

    struct treeNode *parentp= x->parentp;
    while (NULL!= parentp && x == parentp->leftp){
        x = parentp;
        parentp = x->parentp;
    }

    return parentp;
}


void Tree::transplant(struct treeNode *dstp, struct treeNode *srcp)
{
    if (NULL == dstp->parentp){
        this->m_rootp = srcp;
    } else if (dstp == dstp->parentp->leftp) {
        dstp->parentp->leftp = srcp;
    } else {
        dstp->parentp->rightp = srcp;
    }
    if (NULL != srcp){
        srcp->parentp = dstp->parentp;
    }    
}
struct treeNode * Tree::del(struct treeNode * delp)
{
    if (NULL == delp->leftp) {
        this->transplant(delp, delp->rightp);
    } else if (NULL == delp->rightp) {
        this->transplant(delp, delp->leftp);
    } else {
        struct treeNode *y = this->min(delp->rightp);
        if (y->parentp != delp) {
            this->transplant(y, y->rightp);
            y->rightp = delp->rightp;
            y->rightp->parentp = y;
        }
        this->transplant(delp, y);
        y->leftp = delp->leftp;
        y->leftp->parentp = y;
    }
    return delp;
}