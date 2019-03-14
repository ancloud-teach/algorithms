#ifndef _SLIST_H_
#define _SLIST_H_

/* 
 * the singly llinked struct
 * @{key, nextp} 
 */
template <class T>
class SLIST {
public:
    SLIST(void)
    {
        this->m_headp = NULL;
        this->m_tailp = NULL;
    }
    ~SLIST(void);

    T* search(int const key)
    {
        T *nodep = this->m_headp;
        while (nodep !=NULL && nodep->key != key)
            nodep = nodep->nextp;
        return nodep;
    }

    T * insert(T * const newp)
    {
        if (this->m_headp == NULL) {
            this->m_tailp = newp;
        } else {
            newp->nextp = this->m_headp;
        }
        this->m_headp = newp;
        
        return newp;
    }

    T * del(T * const delp)
    {
        T * prevp = NULL;
        T * nowp = this->m_headp;
        while (nowp!=NULL && nowp != delp){
            prevp = nowp;
            nowp = nowp->nextp;
        }
            
        if (nowp != NULL) {
            if (nowp == this->m_headp){
                this->m_headp = nowp->nextp;
            } else {
                prevp->nextp = nowp->nextp;
                if (nowp == this->m_tailp) {
                    this->m_tailp = prevp;
                }
            }
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
};

#endif
