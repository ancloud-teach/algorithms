#ifndef _LIFO_SLIST_H_
#define _LIFO_SLIST_H_

#include "./SLIST.h"

template <class T>
class LIFOSlist {
public:
    LIFOSlist(int const size)
    {
        this->m_size = size;
        this->m_top = 0;
    }

	~LIFOSlist(void)
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
	
	T * push(T *valp)
	{
		if (this->isFull())
			return NULL;

        m_list.insert(valp);
		this->m_top++;

		return valp;
	}
	T * pop(void)
	{        
		if (this->isEmpty())
			return NULL;
        T *valp = this->m_list.head();
        this->m_list.del(valp);
		this->m_top--;
        
        return valp;
	}
	
private:
    int m_top;
	int m_size;

    SLIST<T> m_list;
};

#endif
