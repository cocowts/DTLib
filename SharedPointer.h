#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "Pointer.h"
#include "Exception.h"

#include <cstdlib>

namespace DTLib
{

template <typename T>
class SharedPointer : public Pointer<T>
{
public:
    SharedPointer(T *p = nullptr)
    {
        if (p != nullptr)
        {
            m_ref = static_cast<int*>(malloc(sizeof(int)));

            if (m_ref)
            {
                this->m_pointer = p;

                *(this->m_ref) = 1;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create SharedPointer object ...");
            }
        }

    }

    SharedPointer(const SharedPointer<T> &obj) : Pointer<T> (nullptr)
    {
        assign(obj);
    }

    SharedPointer &operator= (const SharedPointer &obj)
    {
        if (this != &obj)
        {
            clear();

            assign(obj);
        }

        return *this;
    }

    void clear()
    {
        int *ref = this->m_ref;
        T *toDel = this->m_pointer;

        this->m_ref = nullptr;
        this->m_pointer = nullptr;

        if (ref)
        {
            --(*ref);

            if (*ref == 0)
            {
                free(ref);
                delete toDel;
            }
        }
    }

    ~SharedPointer()
    {
        clear();
    }

protected:
    int *m_ref = nullptr;

    void assign(const SharedPointer &obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;

        if (this->m_ref)
        {
            ++(*this->m_ref);
        }
    }
};

template <typename T>
bool operator== (const SharedPointer<T> &lhs, const SharedPointer<T> &rhs)
{
    return (lhs.get() == rhs.get());
}

template <typename T>
bool operator!= (const SharedPointer<T> &lhs, const SharedPointer<T> &rhs)
{
    return  !(lhs == rhs);
}


}

#endif // SHAREDPOINTER_H
