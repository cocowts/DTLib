#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class DynamicArray : public Array<T>
{
public:
    DynamicArray(int length = 0)  // O(1)
    {
        init(new T[length], length);
    }

    DynamicArray(const DynamicArray<T> &obj)  // O(n)
    {
        init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
    }

    DynamicArray<T> &operator= (const DynamicArray<T> &obj)  // O(n)
    {
        if (this != &obj)
        {
            update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
        }

        return *this;
    }

    int length() const  // O(1)
    {
        return m_length;
    }

    void resize(int length)  // O(n)
    {
        if (length != m_length)
        {
            update(copy(this->m_array, this->m_length, length), length);
        }
    }

    ~DynamicArray()  // O(1)
    {
        delete []  this->m_array;
    }

protected:
    int m_length = 0;

    T *copy(T *array, int length, int newLength)  // O(n)
    {
        T *ret = new T[newLength];

        if (ret != nullptr)
        {
            int size = (length < newLength) ? length : newLength;
            for (int i=0; i<size; ++i)
            {
                ret[i] = array[i];
            }
        }

        return ret;
    }

    void update(T *array, int length)  // O(1)
    {
        if (array != nullptr)
        {
            T *temp = this->m_array;
            this->m_array = array;
            this->m_length = length;
            delete [] temp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to update DynmicArray object ...");
        }
    }

    void init(T *array, int length)  // O(1)
    {
        if (array != nullptr)
        {
            this->m_array = array;
            this->m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough to init DynamicArray object ...");
        }
    }
};

}

#endif // DYNAMICARRAY_H
