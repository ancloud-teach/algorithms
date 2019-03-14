#ifndef _FREE_LIST_H_
#define _FREE_LIST_H_

/*
 *  struct T {
        T *nextp;
        ...
    }
 */
template <class T>
class FreeList {
public:

    FreeList(size_t const size)
    {
        this->m_freep = NULL;
        for (int i=0; i<size; i++) {
            T* nodep = (T*) malloc(sizeof(T));
            nodep->nextp = this->m_freep;
            this->m_freep = nodep;
        }
    }
    ~FreeList(void)
    {
        free(this->m_freep);
        this->m_freep = NULL;
    }
    
    T * allocateObject(bool const bClr)
    {
        if (NULL == this->m_freep){
            return NULL;
        }

        T *nodep = this->m_freep;
        this->m_freep = nodep->nextp;

        if (bClr) {
            memset(nodep, 0, sizeof(T));
        }

        return nodep;
    }

    void freeObject(T *const nodep)
    {
        nodep->nextp = this->m_freep;
        this->m_freep = nodep;
    }
private:
    T *m_freep;
};

#endif
