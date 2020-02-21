#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "Queue.h"
#include "Exception.h"

namespace DTLib
{

template <typename T, int N>
class StaticQueue : public Queue<T>
{
public:
    StaticQueue() = default;

    int capacity() const  // O(1)
    {
        return N;
    }

    void add(const T &e) override  // O(1)
    {
        if (m_length < N)
        {
            m_space[m_rear] = e;
            m_rear = (m_rear + 1) % N;
            ++m_length;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "No space in current StaticQueue ...");
        }
    }

    void remove() override  // O(1)
    {
        if (m_length > 0)
        {
            m_front = (m_front + 1) % N;
            --m_length;
        }
        else
        {
            THROW_EXCEPTION(InvalidOpertionExcetion, "No element in current StaticQueue ...");
        }
    }

    T front() const override  // O(1)
    {
        if (m_length > 0)
        {
           return m_space[m_front];
        }
        else
        {
            THROW_EXCEPTION(InvalidOpertionExcetion, "No element in current StaticQueue ...");
        }
    }

    void clear() override  // O(1)
    {
        m_length = 0;
        m_front  = 0;
        m_rear   = 0;
    }

    int length() const override  // O(1)
    {
        return m_length;
    }

    ~StaticQueue()  // O(1)
    {
        clear();
    }

protected:
    T m_space[N];
    int m_front  = 0;
    int m_rear   = 0;
    int m_length = 0;
};

}

#endif // STATICQUEUE_H
