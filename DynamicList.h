#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SqlList.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class DynamicList : public SqlList<T>
{
public:
    DynamicList(int capacity)
    {
        this->m_array    = new T[capacity];
        if (this->m_array != nullptr)
        {
            this->m_capacity = capacity;
            this->m_length   = 0;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicList object ...");
        }
    }

    int capacity() const override
    {
        return m_capacity;
    }

    void resize(int capacity)
    {
        if (capacity != m_capacity)
        {
            T *array = new T[capacity];             // 注意 1
            if (array != nullptr)
            {
               int length = (this->m_length < capacity) ? this->m_length : capacity;

                for (int i = 0; i< length; ++i)
                {
                    array[i] = this->m_array[i];    // 注意 2
                }

                T *temp = this->m_array;            // 注意 3

                this->m_array    = array;
                this->m_length   = length;
                this->m_capacity = capacity;

                delete [] temp;                     // 注意 3
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No meomry to resize DynamicList object ...");
            }
        }
    }

    ~DynamicList()
    {
        delete [] this->m_array;
    }

protected:
    int m_capacity = 0;
};

}

#endif // DYNAMICLIST_H
