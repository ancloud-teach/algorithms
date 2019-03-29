#ifndef _SLIST_H_
#define _SLIST_H_
#include <pthread.h>
#include "../init.h"


/* 
 * the singly llinked struct
 * @{key, nextp} 
 */
template <class T>
class SLIST {
public:
    SLIST(bool bThreadSafe = true)
    {
        this->m_headp = NULL;
        this->m_tailp = NULL;
        this->m_bThreadSafe = bThreadSafe;
    }
    ~SLIST(void);

    T* search(int const key)
    {
        if (this->m_bThreadSafe) {
            pthread_rwlock_rdlock(&this->m_lock);
        }
        
        T *nodep = this->m_headp;
        while (nodep !=NULL && nodep->key != key)
            nodep = nodep->nextp;

        if (this->m_bThreadSafe) {
            pthread_rwlock_unlock(&this->m_lock);
        }
        return nodep;
    }

    T * insert(T * const newp)
    {        
        if (this->m_bThreadSafe) {
            pthread_rwlock_wrlock(&this->m_lock);
        }
         
        if (this->m_headp == NULL) {
            this->m_tailp = newp;
        } else {
            newp->nextp = this->m_headp;
        }
        this->m_headp = newp;

        if (this->m_bThreadSafe) {
            pthread_rwlock_unlock(&this->m_lock);
        }
        return newp;
    }

    T * del(T * const delp)
    {
        if (NULL == this->m_headp)
            return NULL;

        if (this->m_bThreadSafe) {
            pthread_rwlock_wrlock(&this->m_lock);
        }
        
        T * prevp = NULL;
        T * nowp = this->m_headp;
     
        do {
            if (nowp == delp)
                break;
            prevp = nowp;
            nowp = nowp->nextp;
        } while (1);
            
        if (nowp != NULL) {
            if (nowp == this->m_headp){
                this->m_headp = nowp->nextp;
            } else {
                prevp->nextp = nowp->nextp;
            }
            if (nowp == this->m_tailp) {
                this->m_tailp = prevp;
            }
        } 
        if (this->m_bThreadSafe) {
            pthread_rwlock_unlock(&this->m_lock);
        }

        return nowp;
    }

    T * head(void)
    {
        return this->m_headp;
    }
    T * tail(void)
    {
        return this->m_tailp;
    }
private:
    T *m_headp;
    T *m_tailp;
    bool m_bThreadSafe;
    pthread_rwlock_t m_lock;
};

#endif
