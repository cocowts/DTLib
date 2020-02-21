#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"

namespace DTLib
{

template<typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T *p = nullptr) : Pointer<T>(p)
    {
    }

    SmartPointer(const SmartPointer &obj) : Pointer<T>(nullptr)
    {
        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer&>(obj).m_pointer = nullptr;
    }

    SmartPointer &operator= (const SmartPointer &obj)
    {
        if (this != &obj)
        {
            T *pointer = this->m_pointer;

            this->m_pointer = obj.m_pointer;
            const_cast<SmartPointer&>(obj).m_pointer = nullptr;

            delete pointer;
        }

        return *this;
    }

    ~SmartPointer()
    {
        delete this->m_pointer;
    }
};

}

#endif // SMARTPOINTER_H
