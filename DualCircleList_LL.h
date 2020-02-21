#ifndef DUALCIRCLELIST_LL_H
#define DUALCIRCLELIST_LL_H

#include "LinuxList.h"
#include "DualLinkList.h"

namespace DTLib
{

template <typename T>
class DualCircleList_LL : public DualLinkList<T>
{
public:
    DualCircleList_LL()
    {
        this->m_length = 0;
        this->m_step = 1;
        m_current = nullptr;

        INIT_LIST_HEAD(&m_header);
    }

    bool insert(const T &e)
    {
        return insert(this->m_length, e);
    }

    bool insert(int i, const T &e) override
    {
        bool ret = true;
        Node *node = new Node();

        i = i % (this->m_length + 1);

        if (node != nullptr)
        {
            node->value = e;

            list_add_tail(&node->head, position(i)->next);

            ++this->m_length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memeory to create node object ...");
        }

        return ret;
    }

    bool remove(int i) override
    {
        bool ret = true;

        i = mod(i);

        ret = ((0 <= i) && (i < this->m_length));

        if (ret)
        {
            list_head *toDel = position(i)->next;

            if (toDel == m_current)
            {
                m_current = toDel->next;
            }

            list_del(toDel);

            --this->m_length;

            delete list_entry(toDel, Node, head);
        }

        return ret;
    }

    bool set(int i, const T &e) override
    {
        bool ret = true;

        i = mod(i);

        ret = ((0 <= i) && (i < this->m_length));

        if (ret)
        {
           list_entry(position(i)->next, Node, head)->value = e;
        }

        return ret;
    }

    T get(int i) const
    {
        T ret;

        if (!get(i, ret))
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Invalid parameter i to get element ...");
        }

        return ret;
    }

    bool get(int i, T &e) const override
    {
        bool ret = true;

        i = mod(i);

        ret = ((0 <= i) && (i < this->m_length));

        if (ret)
        {
           e = list_entry(position(i)->next, Node, head)->value;
        }

        return ret;
    }

    int  find(const T &e) const override
    {
        int ret = -1;
        int i = 0;
        list_head *slider = nullptr;

        list_for_each(slider, &m_header)
        {
            if (list_entry(slider, Node, head)->value == e)
            {
                ret = i;
                break;
            }

            ++i;
        }

        return ret;
    }

    int length() const override
    {
        return this->m_length;
    }

    void clear() override // O(n)
    {
        while (this->m_length > 0)
        {
            remove(0);
        }

        m_current = nullptr;
    }

    bool move(int i, int step = 1) override  // O(n)
    {
        bool ret = (step > 0);

        i = mod(i);

        ret = ret && ((0 <= i) && (i < this->m_length));

        if (ret)
        {
            this->m_current = position(i)->next;
            this->m_step = step;
        }

        return ret;
    }

    bool end() override // O(1)
    {
        return ((m_current == nullptr) || (this->m_length == 0));
    }

    T current() override // O(1)
    {
        if (!end())
        {
            return list_entry(m_current, Node, head)->value;
        }
        else
        {
             THROW_EXCEPTION(InvalidOpertionExcetion, " No value at current posotion ...");
        }
    }

    bool next() override // O(n)
    {
        int i = 0;

        while ((i < this->m_step) && !end())
        {
            if (m_current != &m_header)
            {
                m_current = m_current->next;
                ++i;
            }
            else
            {
                m_current = m_current->next;
            }
        }

        if (m_current == &m_header)
        {
            m_current = m_current->next;
        }

        return (i == this->m_step);
    }

    bool pre() override
    {
        int i = 0;

        while ((i < this->m_step) && !end())
        {
            if (m_current != &m_header)
            {
                m_current = m_current->prev;
                ++i;
            }
            else
            {
                m_current = m_current->prev;
            }
        }

        if (m_current == &m_header)
        {
            m_current = m_current->prev;
        }

        return (i == this->m_step);
    }

    ~DualCircleList_LL()
    {
        clear();
    }

protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };

    list_head m_header;
    list_head *m_current;

    list_head *position(int i) const
    {
        list_head *ret = const_cast<list_head*>(&m_header);

        for (int p=0; p<i; ++p)
        {
            ret = ret->next;
        }

        return ret;
    }

    int mod(int i) const
    {
        return (this->m_length == 0) ? 0 : (i % this->m_length);
    }
};

}

#endif // DUALCIRCLELIST_LL_H
