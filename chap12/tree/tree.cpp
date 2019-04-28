#include <stdio.h>
#include "./tree.h"
#include <Lib/define/global_define.h>

Tree::Tree(void)
{
    this->m_rootp = NULL;
    this->m_size = 0;
    APLOG("------ m size=%d\n", m_size);
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
        if (insp->key == x->key){
            while (NULL != x->nextp) {
                x = x->nextp;                
            }
            x->nextp = insp;
            insp->parentp = x;
            return ;
        } else if (insp->key < x->key)
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
    this->m_size++;
}

void Tree::inorderWalk(struct treeNode *x, void (* print)(void *datap))
{
    if (NULL == x) 
        return ;
    this->inorderWalk(x->leftp, print);

    printf("node(0x%x): %d color=%s\t(par=0x%x, left=0x%x, right=0x%x, next=0x%x)--\n", (uint32_t)x, x->key, x->color==RED?"Red":"Black",
            (uint32_t)x->parentp, (uint32_t)x->leftp, (uint32_t)x->rightp, (uint32_t)x->nextp);
    if (NULL != print)    
        print(x->datap);
    struct treeNode *samep = x->nextp;
    while (NULL != samep) {
        printf("same(0x%x): %d\t(par=0x%x, left=0x%x, right=0x%x, next=0x%x)\n", (uint32_t)samep, samep->key,
            (uint32_t)samep->parentp, (uint32_t)samep->leftp, (uint32_t)samep->rightp, (uint32_t)samep->nextp);
        if (NULL != print)    
            print(samep->datap);
        
        samep =samep->nextp;
    }

    this->inorderWalk(x->rightp, print);
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
    if (delp->nextp != NULL) {
        struct treeNode *nextp = delp->nextp;
        
        nextp->leftp = delp->leftp;
        nextp->rightp = delp->rightp;
        nextp->parentp = delp->parentp;
        if (NULL != delp->leftp) {
            delp->leftp->parentp = nextp;
        } 
        if (NULL != delp->rightp) {
            delp->rightp->parentp = nextp;
        }
        
        //APLOG("nextp=0x%x\n", (uint32_t)nextp);
        if (NULL == delp->parentp){
            this->m_rootp = nextp;
        } else if (delp == delp->parentp->leftp){
            //APLOG("left\n");
            delp->parentp->leftp = nextp;
        }
        else if (delp == delp->parentp->rightp){
            delp->parentp->rightp =nextp;
            //APLOG("right. par=0x%d, par->righ=0x%x, next=0x%x\n", delp->parentp, delp->parentp->rightp, nextp);
        } else {
            delp->parentp->nextp = nextp;
        }
        this->m_size--;
        return delp;
    }
    
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
    this->m_size--;
    return delp;
}