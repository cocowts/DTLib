#ifndef SQLLIST_H
#define SQLLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class SqlList : public List<T>
{
public:
    bool insert(const T &e) override // O(1)
    {
        return insert(m_length, e);
    }

    bool insert(int i, const T &e) override  // O(n)
    {
        bool ret = ((0 <= i) && (i <= m_length));  // 注：目标位置可以为m_length,表示尾部插入
        ret = ret && (m_length < capacity());

        if (ret)
        {
            for (int p = m_length - 1; p >= i; --p)
            {
                m_array[p + 1] = m_array[p];
            }

            m_array[i] = e;
            ++m_length;
        }

        return ret;
    }

    bool remove(int i) override  // O(n)
    {
        bool ret = ((0 <= i) && (i < m_length));

        if (ret)
        {
            for (int p = i + 1; p < m_length; ++p)
            {
                m_array[p - 1] = m_array[p];
            }

            --m_length;
        }

        return ret;
    }

    bool set(int i, const T &e) override  // O(1)
    {
        bool ret = ((0 <= i) && (i < m_length));

        if (ret)
        {
            m_array[i] = e;
        }

        return ret;
    }

    bool get(int i, T &e) const override  // O(1)
    {
        bool ret = ((0 <= i) && (i < m_length));

        if (ret)
        {
            e = m_array[i];
        }

        return ret;
    }

    int  find(const T &e) const override  // O(n)
    {
        int ret = -1;

        for (int i=0; i<m_length; ++i)
        {
            if(m_array[i] == e)
            {
                ret = i;
                break;
            }
        }

        return ret;
    }

    int length() const  // O(1)
    {
        return m_length;
    }

    void clear()  // O(1)
    {
        m_length = 0;
    }

    T &operator[] (int i)  // O(1)
    {
        if ((0 <= i) && (i < m_length))
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
        }
    }

    T operator[] (int i) const  // O(1)
    {
        return (const_cast<SqlList&>(*this))[i];
    }

    virtual int capacity() const = 0;
protected:
    T *m_array   = nullptr;
    int m_length = 0;
};

}

#endif // SQLLIST_H
