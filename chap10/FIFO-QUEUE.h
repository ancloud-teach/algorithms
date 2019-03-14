#ifndef _FIFO_QUEUE_H_
#define _FIFO_QUEUE_H_

#include <stdlib.h>

/* should add lock for pthread !!! */

template <class T> 
class Queue {
public:
	/*
	 * @size, is the size of queue would be created
	 */
	Queue(int const size)
	{
		this->m_size = size;
		this->m_queuep = (T *)malloc(sizeof(T) * size);
		this->m_head = 0;
        this->m_tail = 0;
	}
	~Queue(void)
	{
		free(this->m_queuep);
	}

    int enqueue(T *valp)
    {
        if ( (m_tail+1)%m_size == m_head ) {
            //- it is full
            return -1;
        }
        m_queuep[m_tail] = *valp;
        m_tail = (m_tail+1)%m_size;

        return 0;
    }   

    int dequeue(T *valp)
    {
        if ( m_tail == m_head ) {
            //- it is empty
            return -1;
        }
        *valp = m_queuep[m_head];
        m_head = (m_head+1)%m_size;

        return 0;
    }   
	
	
private:
	T *m_queuep;
	int m_size;
    int m_head;
    int m_tail;
};
#endif
