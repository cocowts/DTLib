#ifndef STAITCSTACK_H
#define STAITCSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace DTLib
{

template <typename T, int N>
class StaticStack : public Stack<T>
{
public:
    StaticStack() = default;

    int capacity() const  // O(1)
    {
        return N;
    }

    void push(const T &e) override  // O(1)
    {
        if (m_size < N)
        {
            m_space[m_top + 1] = e;

            ++m_top;
            ++m_size;
        }
        else
        {
            THROW_EXCEPTION(InvalidOpertionExcetion, "No enough space to push StaticStack ...");
        }
    }

    void pop() override  // O(1)
    {
        if (m_size > 0)
        {
            --m_top;
            --m_size;
        }
        else
        {
            THROW_EXCEPTION(InvalidOpertionExcetion, "No element to pop StaticStack ...");
        }
    }

    T top() const override  // O(1)
    {
        if (m_size > 0)
        {
            return m_space[m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidOpertionExcetion, "No element in current StaticStack ...");
        }
    }

    void clear() override  // O(1)
    {
        m_top = -1;
        m_size = 0;
    }

    int size() const override  // O(1)
    {
        return m_size;
    }

    ~StaticStack()  // O(1)
    {
        clear();
    }

protected:
    T m_space[N];
    int m_top = -1;
    int m_size = 0;
};

}

#endif // STAITCSTACK_H
