#ifndef STATICLIST_H
#define STATICLIST_H

#include "SqlList.h"

namespace DTLib
{

template <typename T, int N>
class StaticList : public SqlList<T>
{
public:
    StaticList()
    {
        this->m_array = m_space;
        this->m_length = 0;
    }

    int capacity() const override
    {
        return N;
    }

protected:
    T m_space[N];
};

}

#endif // STATICLIST_H
