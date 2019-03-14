#ifndef _FIFO_SLIST_H_
#define _FIFO_SLIST_H_

#include "./SLIST.h"

template <class T>
class FIFOSlist {
public:
    FIFOSlist(int const size)
    {
        this->m_size = size;
        this->m_top = 0;
    }

	~FIFOSlist(void)
	{
	}

    bool isEmpty(void) 
	{
		return this->m_top == 0;
	}

	bool isFull(void) 
	{
		return this->m_top >= this->m_size;
	}
	
	T* enqueue(T *valp)
    {
        if (this->isFull())
            return NULL;
        
        m_list.insert(valp);
        this->m_top++;

        return valp;
    }   

    T* dequeue(void)
    {
        if (this->isEmpty())
            return NULL;

        T* delp = this->m_list.tail();
        this->m_list.del(delp);
        this->m_top--;
        
        return delp;
    }   
	
private:
	int m_size;
    int m_top;

    SLIST<T> m_list;
};

#endif
