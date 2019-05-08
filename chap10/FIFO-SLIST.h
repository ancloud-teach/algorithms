#ifndef _FIFO_SLIST_H_
#define _FIFO_SLIST_H_


struct fifoNode {
    struct fifoNode *nextp;
    void * datap;
};

#include "./SLIST.h"
#include "./FREE-LIST.h"

class FIFOSlist {
public:
    FIFOSlist(int const size)
    {
        this->m_size = size;
        this->m_top = 0;

        this->m_memp = new FreeList<struct fifoNode>(size);
    }

	~FIFOSlist(void)
	{
	    delete this->m_memp;
	}

    bool isEmpty(void) 
	{
		return this->m_top == 0;
	}

	bool isFull(void) 
	{
		return this->m_top >= this->m_size;
	}
	
	int enqueue(void *valp)
    {
        if (this->isFull())
            return -1;

        struct fifoNode *nodep = this->m_memp->allocateObject(true);
        nodep->datap = valp;
        m_list.insert(nodep);
        this->m_top++;

        return 0;
    }   

    void* dequeue(void)
    {
        if (this->isEmpty())
            return NULL;

        struct fifoNode* delp = this->m_list.tail();
        this->m_list.del(delp);
        this->m_top--;

        void *valp = delp->datap;
        this->m_memp->freeObject(delp);
        return valp;
    }   
	
private:
	int m_size;
    int m_top;

    SLIST<struct fifoNode> m_list;
    FreeList<struct fifoNode> *m_memp;
};

#endif
