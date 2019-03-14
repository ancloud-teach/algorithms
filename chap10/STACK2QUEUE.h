#ifndef _STACK2QUEUE_H_
#define _STACK2QUEUE_H_

#include <stdlib.h>
#include "LIFO-STACK.h"


/* should add lock for pthread !!! */

template <class T> 
class Stack2Queue {
public:
	/*
	 * @size, is the size of queue would be created
	 */
	Stack2Queue(int const size)
	{
		this->m_size = size;
		//this->m_queuep = (T *)malloc(sizeof(T) * size);
		this->m_A = new Stack<T>(size);
        this->m_B = new Stack<T>(size);
	}
	~Stack2Queue(void)
	{
		delete this->m_A;
        delete this->m_B;
	}

    int enqueue(T *valp)
    {
        int ret = 0;
        if (m_A->isFull()) 
            return -1;

        m_A->push(valp);
        
        return 0;
    }   

    int dequeue(T *valp)
    {
        if (this->m_A->isEmpty() && this->m_B->isEmpty()) 
            return -1;

        int ret = 0;
        if (!this->m_B->isEmpty()) {
            return this->m_B->pop(valp);
        } else {
            T last, now;
            bool bFirst = true;
            do {
                ret = this->m_A->pop(&now);
                if (ret < 0){
                    break;
                }
                if (!bFirst){
                    ret = this->m_B->push(&last);
                }
                bFirst = false;
                last = now;
            } while (ret >= 0);

            *valp = last;
            return 0;
        }
    }   
	
	
private:
	int m_size;

    Stack<T> *m_A;
    Stack<T> *m_B;
};
#endif
