#include <string.h>

#include "./RBtree.h"

RBtree::RBtree(void)
{
    this->m_rootp = NULL;
    this->m_size = 0;
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
        printf("same(0x%x): %lld\t(par=%lld(0x%x), left=%lld(0x%x), right=%lld(0x%x), next=%lld(0x%x)\n", (uint32_t)samep, samep->key,
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

/*
 * @lastp: it must be NULL if call the fun first.
 *
 * return the result; if it is NULL, means had already walked all tree node
 */
struct treeNode * RBtree::inorderWalk(struct treeNode *lastp)
{
    struct treeNode *nodep = NULL;
    
    if (NULL == lastp) {
        nodep = this->min(m_rootp);
        return nodep;
    } else {
        return this->successor(lastp);
    }
}

int RBtree::checkWalk(struct treeNode *nodep, int blackNum)
{
    if (nodep == m_NILp)
        return 0;

    if (nodep->color == BLACK) {
        blackNum++;
    }
    
    checkWalk(nodep->leftp, blackNum);

    checkWalk(nodep->rightp, blackNum);

    if (nodep->color == RED) {
        if (nodep->leftp->color != BLACK ) {
            printf("the node(%lld) color is RED, but the left(%lld) is NOT BLACK\n",
                nodep->key, nodep->leftp->key);
            return -2;
        }
        if (nodep->rightp->color != BLACK ) {
            printf("the node(%lld) color is RED, but the right(%lld) is NOT BLACK\n",
                nodep->key, nodep->rightp->key);
            return -3;
        }
    }
    if (nodep->leftp==m_NILp && nodep->rightp==m_NILp) {
        printf("node(%lld) black color num=%d\n", nodep->key,blackNum);
    }
    
    return 0;
}
int RBtree::check(void)
{
    if (m_rootp->color != BLACK) {
        return -1;
    }

    return checkWalk(this->getRoot(), 0);
}

void RBtree::printNode(struct treeNode * x)
{
    printf("%s\tnode(0x%x): %lld(%s)\t(%4lld's %c child, \tpar=0x%x(%lld), left=0x%x(%lld), right=0x%x(%lld), next=0x%x)--\n", 
                x==m_rootp?"Root":"",
                (uint32_t)x, x->key, x->color==RED?"R":"BL",
                x->parentp->key, (x==x->parentp->leftp)?'L':'R',
                (uint32_t)x->parentp, x->parentp->key,
                (uint32_t)x->leftp, x->leftp->key,
                (uint32_t)x->rightp, x->rightp->key,
                (uint32_t)x->nextp);
}

struct treeNode * RBtree::getRoot(void)
{
    return this->m_rootp;
}

int RBtree::size(void)
{
    return m_size;
}


struct treeNode * RBtree::search(struct treeNode *x, uint64_t const key)
{    
    while (x != m_NILp) {
        if (key == x->key)
            break;
        
        if (key < x->key)
            x = x->leftp;
        else 
            x = x->rightp;
    }

    if (m_NILp == x) 
        return NULL;
    else
        return x;
}

struct treeNode * RBtree::min(struct treeNode *x)
{
    if (NULL == x)
        return NULL;
    
    while (m_NILp != x->leftp) {
        x = x->leftp;
    }
    return x;
}

struct treeNode * RBtree::max(struct treeNode *x)
{
    if (m_NILp == x)
        return NULL;
    
    while (m_NILp != x->rightp) {
        x = x->rightp;
    }
    return x;
}

/*
 * find the node, whose key > x->key and the node is the min key 
 */
struct treeNode * RBtree::successor(struct treeNode *x)
{
    if (m_NILp == x)
        return NULL;
    
    if (m_NILp != x->rightp)
        return this->min(x->rightp);

    struct treeNode *parentp= x->parentp;
    while (m_NILp!= parentp && x == parentp->rightp){
        x = parentp;
        parentp = x->parentp;
    }

    return parentp;
}

struct treeNode * RBtree::predecessor(struct treeNode *x)
{
    if (m_NILp == x)
        return NULL;
    
    if (m_NILp != x->leftp)
        return this->max(x->leftp);

    struct treeNode *parentp= x->parentp;
    while (m_NILp!= parentp && x == parentp->leftp){
        x = parentp;
        parentp = x->parentp;
    }

    return parentp;
}

struct treeNode* RBtree::insert(uint64_t key, void *datap)
{      
    struct treeNode * z = (struct treeNode*)malloc(sizeof(struct treeNode));
    if (NULL == z)
        return NULL;
    memset(z, 0, sizeof(struct treeNode));
    z->key = key;
    z->datap =datap;
    
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

    return z;
}

void RBtree::insertFixup(struct treeNode *z)
{    
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


void RBtree::transplant(struct treeNode *dstp, struct treeNode *srcp)
{
    if (m_NILp == dstp->parentp){
        this->m_rootp = srcp;
    } else if (dstp == dstp->parentp->leftp) {
        dstp->parentp->leftp = srcp;
    } else {
        dstp->parentp->rightp = srcp;
    }
    srcp->parentp = dstp->parentp;    
}

void * RBtree::del(uint64_t lID)
{
    struct treeNode *nodep = this->search(this->m_rootp, lID);
    if (NULL == nodep) {
        return NULL;
    }
    return this->del(nodep);
}

void * RBtree::del(struct treeNode * nodep)
{
    struct treeNode *parentp=NULL, *childp=NULL;
    enum RBColor color;

    if (nodep->leftp != m_NILp && nodep->rightp != m_NILp) {
        struct treeNode *replacep = nodep;
        
        replacep = this->min(nodep->rightp);
        childp = replacep->rightp;
        parentp = replacep->parentp;
        color = replacep->color;
        
        this->transplant(nodep, replacep);

        if (parentp == nodep) {
            parentp = replacep;
        } else {
            if (childp != m_NILp)
                childp->parentp = parentp;
            parentp->leftp = childp;
            replacep->rightp = nodep->rightp;
            nodep->rightp->parentp = replacep;
        }

        replacep->color = nodep->color;
        replacep->leftp = nodep->leftp;
        nodep->leftp->parentp = replacep;

        if (color == BLACK) {
            this->delFixUp(childp, parentp);
        }

        goto DEL;
    }
    
    if (nodep->leftp != m_NILp){
        childp = nodep->leftp;
    } else {
        childp = nodep->rightp;
    }

    parentp = nodep->parentp;
    color = nodep->color;
    
    if (childp != m_NILp) {
        childp->parentp = parentp;
    }
    
    if (parentp == m_NILp) {
        m_rootp = childp;
    } else {
        if (nodep == parentp->leftp) {
            parentp->leftp = childp;
        } else {
            parentp->rightp = childp;
        }
    }

    if (color ==BLACK) {
        this->delFixUp(childp, parentp);
    }

DEL:
    void *datap = nodep->datap;
    free(nodep);

    m_size--;
    return datap; 
}

void RBtree::delFixUp(struct treeNode *nodep, struct treeNode *parentp)
{
    struct treeNode *brother;
    
    while((nodep!=m_NILp || nodep->color == BLACK) && nodep != m_rootp) {
        if (nodep == parentp->leftp) {
            brother = parentp->rightp;

            if (brother->color == RED) {
                //- case 1:
                brother->color = BLACK;
                parentp->color = RED;
                this->leftRotate(parentp);
                brother = parentp->rightp;
            }
            
            if ((brother->leftp!=m_NILp && brother->leftp->color==BLACK) &&
                (brother->rightp!=m_NILp && brother->rightp->color==BLACK) ) {
                //- case 2
                brother->color = RED;
                nodep = parentp;
                parentp = nodep->parentp;
            } else {
                if (brother->rightp!=m_NILp && brother->rightp->color==BLACK) {
                    //- case 3
                    brother->leftp->color = BLACK;
                    brother->color = RED;
                    this->rightRotate(brother);
                    brother = parentp->rightp;
                }

                //- case 4
                brother->color = parentp->color;
                parentp->color = BLACK;
                brother->rightp->color = BLACK;
                this->leftRotate(parentp);
                nodep = m_rootp;
                break;
            }
        } else  {
            brother = parentp->leftp;

            if (brother->color == RED) {
                //- case 1:
                brother->color = BLACK;
                parentp->color = RED;
                this->rightRotate(parentp);
                brother = parentp->leftp;
            }
            if ((brother->leftp!=m_NILp && brother->leftp->color==BLACK) &&
                (brother->rightp!=m_NILp && brother->rightp->color==BLACK) ) {
                //- case 2
                brother->color = RED;
                nodep = parentp;
                parentp = nodep->parentp;
            } else {
                if (brother->leftp!=m_NILp && brother->leftp->color==BLACK) {
                    //- case 3
                    brother->rightp->color = BLACK;
                    brother->color = RED;
                    this->leftRotate(brother);
                    brother = parentp->leftp;
                }

                //- case 4
                brother->color = parentp->color;
                parentp->color = BLACK;
                brother->leftp->color = BLACK;
                this->rightRotate(parentp);
                nodep = m_rootp;
                break;
            }
        }

        if (nodep != m_NILp){
            nodep->color = BLACK;
        }
    }
}
