#ifndef _FREE_LIST_H_
#define _FREE_LIST_H_

#if 0
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
        T * nodep = this->m_freep;
        while (nodep != NULL) {
            T * nextp = nodep->nextp;
            free(nodep);
            nodep = nextp;
        }
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
#else
template <class T>
class FreeList {
public:

    FreeList(size_t const size)
    {
        this->m_size = size;
        this->m_used = 0;
        this->m_freePos = 0;
        
        this->m_nextp = (int *)malloc(sizeof(int) * size);
        this->m_prevp = (int *)malloc(sizeof(int) * size);
        this->m_datap = (T *)malloc(sizeof(T) * size);

        memset(this->m_datap, 0, sizeof(T) * size);

        for (int i=0; i < this->m_size-1; i++) {
            this->m_nextp[i] = i+1;
            this->m_prevp[this->m_size-1-i] = this->m_size-2-i;
        }
        this->m_nextp[this->m_size-1] = ARRAY_NIL;
        this->m_prevp[0] = ARRAY_NIL;
    }
    ~FreeList(void)
    {
        free(this->m_nextp);
        free(this->m_prevp);
        free(this->m_datap);
    }
    
    T * allocateObject(bool const bClr)
    {
        if (this->m_used >= this->m_size){
            return NULL;
        }

        T *nodep = & (this->m_datap[this->m_freePos]);
        int nextPos = this->m_nextp[this->m_freePos];
        this->m_nextp[this->m_freePos] = ARRAY_NIL;
        this->m_prevp[this->m_freePos] = ARRAY_NIL;
        this->m_freePos = nextPos;
        this->m_used++;
        if (this->m_used >= this->m_size){
            this->m_freePos = ARRAY_NIL;
        }
        
        if (bClr) {
            memset(nodep, 0, sizeof(T));
        }

        return nodep;
    }

    void freeObject(T *const nodep)
    {
        int i = 0;
        for (i=0; i<this->m_size; i++) {
            if (&this->m_datap[i] == nodep) 
                break;
        }
        if (i >= this->m_size)
            return ;
        if (this->m_freePos != ARRAY_NIL) {
            this->m_nextp[i] = this->m_freePos;
            this->m_prevp[this->m_freePos] = i;
        }        
        this->m_freePos = i;

        this->m_used--;
    }
private:
    int *m_nextp;
    int *m_prevp;
    T *m_datap;

    int m_size;
    int m_used;
    int m_freePos;
};

#endif

#endif
