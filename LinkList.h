#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class LinkList : public List<T>
{
public:
    LinkList()
    {
        m_header.next = nullptr;
        m_length      = 0;

        m_step        = 1;
        m_current     = nullptr;
    }

    bool insert(const T &e) override  // O(n)
    {
        return insert(m_length, e);
    }

    bool insert(int i, const T &e) override  // O(n)
    {
        bool ret = ((0 <= i) && (i <= m_length));

        if (ret)
        {
            Node *node = create();
            if (node != nullptr)
            {
                Node *current = position(i);

                node->value = e;
                node->next = current->next;
                current->next = node;

                ++m_length;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element ...");
            }
        }

        return ret;
    }

    bool remove(int i) override  // O(n)
    {
        bool ret = ((0 <= i) && (i < m_length));

        if (ret)
        {
            Node *current = position(i);

            Node *toDel = current->next;

            if (m_current == toDel)
            {
                m_current = toDel->next;
            }

            current->next = toDel->next;

            --m_length;

            destroy(toDel);
        }

        return ret;
    }

    bool set(int i, const T &e) override  // O(n)
    {
        bool ret = ((0 <= i) && (i < m_length));

        if (ret)
        {
            position(i)->next->value = e;
        }

        return ret;
    }

    virtual T get(int i) const  // O(n)
    {
        T ret;

        if (!get(i, ret))
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element ...");
        }

        return ret;
    }

    bool get(int i, T &e) const override  // O(n)
    {
        bool ret = ((0 <= i) && (i < m_length));

        if (ret)
        {
            e = position(i)->next->value;
        }

        return ret;
    }

    int  find(const T &e) const override  // O(n)
    {
        int ret = -1;

        int i = 0;
        Node *node = m_header.next;
        while (node)
        {
            if (node->value == e)
            {
                ret = i;
                break;
            }
            else
            {
                node = node->next;
                ++i;
            }
        }

        return ret;
    }

    int length() const override // O(1)
    {
        return m_length;
    }

    void clear() override // O(n)
    {
        while (m_header.next)
        {
            Node *toDel = m_header.next;

            m_header.next = toDel->next;

            --m_length;

            destroy(toDel);
        }

        m_current = nullptr;
    }

    bool move(int i, int step = 1)  // O(n)
    {
        bool ret = ((0 <= i) && (i < m_length) && (step > 0));

        if (ret)
        {
            m_current = position(i)->next;
            m_step = step;
        }

        return ret;
    }

    bool end()  // O(1)
    {
        return (m_current == nullptr);
    }

    T current()  // O(1)
    {
        if (!end())
        {
            return m_current->value;
        }
        else
        {
             THROW_EXCEPTION(InvalidOpertionExcetion, " No value at current posotion ...");
        }
    }

    bool next()  // O(n)
    {
        int i = 0;

        while ((i < m_step) && !end())
        {
            m_current = m_current->next;
            ++i;
        }

        return (i == m_step);
    }

    ~LinkList()  // O(n)
    {
        clear();
    }

protected:
    struct Node : public Object
    {
        T value;
        Node *next;
    };

    mutable struct : public Object
    {
        char reserved[sizeof (T)];
        Node *next;
    }m_header;

    int m_length;
    int m_step;
    Node *m_current;

    Node *position(int i) const  // O(n)
    {
        Node *ret = reinterpret_cast<Node*>(&m_header);

        for (int p=0; p<i; ++p)
        {
            ret = ret->next;
        }

        return ret;
    }

    virtual Node *create()  // N(1)
    {
        return new Node();
    }

    virtual void destroy(Node *pn)  // N(1)
    {
        delete pn;
    }
};

}

#endif // LINKLIST_H
