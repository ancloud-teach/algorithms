#ifndef _LIFO_STACK_H_
#define _LIFO_STACK_H_
#include <stdlib.h>

/* should add lock for pthread !!! */

template <class T> 
class Stack {
public:
	/*
	 * @size, is the size of stack would be created
	 */
	Stack(int const size)
	{
		this->m_size = size;
		this->m_stackp = (T *)malloc(sizeof(T) * size);
		this->m_top = 0;
	}
	~Stack(void)
	{
		free(this->m_stackp);
	}
	
	bool isEmpty(void) 
	{
		return this->m_top == 0;
	}

	bool isFull(void) 
	{
		return this->m_top >= this->m_size;
	}
	
	int push(T *valp)
	{
		if (this->isFull())
			return -1;
		
		this->m_stackp[this->m_top] = *valp;
		this->m_top++;

		return this->m_top;
	}
	int pop(T *valp)
	{        
		if (this->isEmpty())
			return -1;
		this->m_top--;
		*valp = this->m_stackp[this->m_top];
        
        return this->m_top;
	}
	
private:
	T *m_stackp;
	int m_top;
	int m_size;
};

#endif

