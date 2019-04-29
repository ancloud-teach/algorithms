#include <string.h>

#include "./RBtree.h"

RBtree::RBtree(void):Tree()
{
    m_NILp = (struct treeNode*)malloc(sizeof(struct treeNode));
    memset(m_NILp, 0, sizeof(struct treeNode));
    m_NILp->color = BLACK;

    this->m_rootp = m_NILp;
}

RBtree::~RBtree(void)
{
    free(m_NILp);
}

void RBtree::inorderWalk(struct treeNode *x, void (* print)(void *datap))
{
    if (NULL == x || m_NILp == x) 
        return ;
    this->inorderWalk(x->leftp, print);

    this->printNode(x);
    
    if (NULL != print)    
        print(x->datap);
    struct treeNode *samep = x->nextp;
    while (NULL != samep) {
        printf("same(0x%x): %d\t(par=%d(0x%x), left=%d(0x%x), right=%d(0x%x), next=%d(0x%x)\n", (uint32_t)samep, samep->key,
            samep->parentp->key,(uint32_t)samep->parentp, 
            samep->leftp->key,  (uint32_t)samep->leftp, 
            samep->rightp->key, (uint32_t)samep->rightp, 
            samep->nextp->key,  (uint32_t)samep->nextp);
        if (NULL != print)    
            print(samep->datap);
        
        samep =samep->nextp;
    }

    this->inorderWalk(x->rightp, print);
}

void RBtree::printNode(struct treeNode * x)
{
    printf("%s\tnode(0x%x): %d(%s)\t(%4d's %c child, \tpar=0x%x, left=0x%x, right=0x%x, next=0x%x)--\n", 
                x==m_rootp?"Root":"",
                (uint32_t)x, x->key, x->color==RED?"R":"BL",
                x->parentp->key, (x==x->parentp->leftp)?'L':'R',
                (uint32_t)x->parentp, (uint32_t)x->leftp, (uint32_t)x->rightp, (uint32_t)x->nextp);

}


void RBtree::insert(struct treeNode *z)
{        
    z->parentp = m_NILp;
    
    struct treeNode *y = m_NILp;
    struct treeNode *x = this->m_rootp;
    while(x != m_NILp) {
        y = x;
        if (z->key < x->key) {
            x = x->leftp;
        } else {
            x = x->rightp;
        }
    }
    
    z->parentp = y;
    if (y == m_NILp) {
        m_rootp = z;
    } else if (z->key < y->key){
        y->leftp = z;
    } else {
        y->rightp = z;
    }
    z->leftp = m_NILp;
    z->rightp = m_NILp;
    z->color = RED;
    this->insertFixup(z);

    this->m_size++;
}

void RBtree::insertFixup(struct treeNode *z)
{
    struct treeNode *parentp;
    
    while (z->parentp->color == RED) {
        if (z->parentp == z->parentp->parentp->leftp) {
            struct treeNode *y = z->parentp->parentp->rightp;
            if (y->color == RED) {
                z->parentp->color = BLACK;
                y->color = BLACK;
                z->parentp->parentp->color = RED;
                z = z->parentp->parentp;
            } else {
                if (z == z->parentp->rightp) {                
                    //parentp = z->parentp;
                    //this->leftRotate(parentp);
                    //z = parentp;
                    z = z->parentp;
                    this->leftRotate(z);
                    
                } else {
                    z->parentp->color = BLACK;
                    z->parentp->parentp->color = RED;
                    this->rightRotate(z->parentp->parentp);
                }
            }
        } else {
            struct treeNode *y = z->parentp->parentp->leftp;
            if (y->color == RED) {
                z->parentp->color = BLACK;
                y->color = BLACK;
                z->parentp->parentp->color = RED;
                z = z->parentp->parentp;
            } else {
                if (z == z->parentp->leftp) {
                    //parentp = z->parentp;
                    //this->rightRotate(parentp);
                    //z = parentp;
                    z = z->parentp;
                    this->rightRotate(z);
                } else {           
                    z->parentp->color = BLACK; //------??????????-------
                    z->parentp->parentp->color = RED;
                    this->leftRotate(z->parentp->parentp);
                }
            }
        }
    }

    m_rootp->color = BLACK;
}

void RBtree::leftRotate(struct treeNode *x)
{
    struct treeNode *y = x->rightp;
    x->rightp = y->leftp;
    if (y->leftp != m_NILp) {
        y->leftp->parentp = x;
    }
    y->parentp = x->parentp;
    if (x->parentp == m_NILp) {
        m_rootp = y;
    } else if (x == x->parentp->leftp) {
        x->parentp->leftp = y;
    } else {
        x->parentp->rightp = y;
    }
    y->leftp = x;
    x->parentp = y;
}

#if 1
void RBtree::rightRotate(struct treeNode *x)
{
    struct treeNode *y = x->leftp;
    x->leftp = y->rightp;
    if (y->rightp != m_NILp) {
        y->rightp->parentp = x;
    }
    y->parentp = x->parentp;
    if (x->parentp == m_NILp) {
        m_rootp = y;
    } else if (x == x->parentp->rightp) {
        x->parentp->rightp = y;
    } else {
        x->parentp->leftp = y;
    }
    y->rightp = x;
    x->parentp = y;
}
#else
void RBtree::rightRotate(struct treeNode *y)
{
    struct treeNode *x = y->leftp;
    y->leftp = x->rightp;
    if (x->rightp != m_NILp) {
        x->rightp->parentp = y;
    }
    x->parentp = y->parentp;
    if (y->parentp == m_NILp) {
        m_rootp = x;
    } else if (y == y->parentp->rightp) {
        y->parentp->rightp = x;
    } else {
        y->parentp->leftp = x;
    }
    x->rightp = y;
    y->parentp = x;
}
#endif

/*
struct treeNode * RBtree::del(struct treeNode * delp)
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
*/
