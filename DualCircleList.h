#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "DualLinkList.h"

namespace DTLib
{

template <typename T>
class DualCircleList : public DualLinkList<T>
{
public:
    bool insert(const T &e) override  // O(n)
    {
        return insert(this->m_length, e);
    }

    bool insert(int i, const T &e) override  // O(n)
    {
        bool ret = true;
        i = i % (this->m_length + 1);

        ret = DualLinkList<T>::insert(i, e);

        if (ret && (i == 0))
        {
            last_to_first();
        }

        return ret;
    }

    bool remove(int i) override // O(n)
    {
        bool ret = true;
        i = mod(i);

        if (i == 0)
        {
            Node *toDel = this->m_header.next;

            if (toDel != nullptr)
            {
                this->m_header.next = toDel->next;

                --this->m_length;

                if (this->length() > 0)
                {
                    last_to_first();

                    if (this->m_current == toDel)
                    {
                        this->m_current = this->m_current->next;
                    }
                }
                else
                {
                    this->m_header.next = nullptr;
                    this->m_current = nullptr;
                }

                this->destroy(toDel);
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = DualLinkList<T>::remove(i);
        }

        return ret;
    }

    bool set(int i, const T &e) override  // O(n)
    {
        return DualLinkList<T>::set(mod(i), e);
    }

    T get(int i) const override  // O(n)
    {
        return DualLinkList<T>::get(mod(i));
    }

    bool get(int i, T &e) const override  // O(n)
    {
        return DualLinkList<T>::get(mod(i), e);
    }

    int find(const T &e) const // O(n)
    {
        int ret = -1;

        Node *slider = this->m_header.next;

        for (int i=0; i<this->m_length; ++i)
        {
            if (slider->value == e)
            {
                ret = i;
                break;
            }

            slider = slider->next;
        }

        return ret;
    }

    void clear() override  // O(n)
    {
        while (this->m_length > 1)
        {
            remove(1);  // 注意：为了效率，没有调用 remove(0)！
        }

        if(this->m_length == 1)
        {
            Node *toDel = this->m_header.next;

            this->m_header.next = nullptr;
            this->m_current = nullptr;
            this->m_length = 0;

            this->destroy(toDel);
        }
    }

    bool move(int i, int step = 1)
    {
        return DualLinkList<T>::move(mod(i), step);
    }

    bool end()  // O(n)
    {
        return ((this->m_length == 0) || (this->m_current == nullptr));
    }

    ~DualCircleList()  // O(n)
    {
        clear();
    }

protected:
    using Node = typename DualLinkList<T>::Node;

    Node *last() const // O(n)
    {
        return this->position(this->m_length - 1)->next;
    }

    void last_to_first() const // O(1)
    {
        Node *pfirst = this->m_header.next;
        Node *plast = this->last();

        plast->next = pfirst;
        pfirst->pre =plast;
    }

    int mod(int i) const // O(1)
    {
        return (this->m_length == 0) ? 0 : (i % this->m_length);
    }
};

}

#endif // DUALCIRCLELIST_H
