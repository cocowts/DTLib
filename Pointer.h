#ifndef POINTER_H
#define POINTER_H

#include "Object.h"

namespace DTLib
{

template <typename T>
class Pointer : public Object
{
public:
    Pointer(T *p = nullptr) : m_pointer(p)
    {
    }

    T *operator-> ()
    {
        return m_pointer;
    }

    const T *operator-> () const
    {
        return m_pointer;
    }

    T &operator* ()
    {
        return *m_pointer;
    }

    const T &operator* () const
    {
        return *m_pointer;
    }

    bool isNull() const
    {
        return (m_pointer == nullptr);
    }

    T *get() const
    {
        return m_pointer;
    }

protected:
    T *m_pointer = nullptr;
};

}

#endif // POINTER_H
