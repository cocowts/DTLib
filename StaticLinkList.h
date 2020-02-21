#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

#include <iostream>

using namespace std;

namespace DTLib
{

template <typename T, int N>
class StaticLinkList : public LinkList<T>
{
public:
    StaticLinkList()  // O(n)
    {
        for (int i=0; i<N; ++i)
        {
            m_used[i] = 0;
        }
    }

    int capacity()  // O(1)
    {
        return N;
    }

    ~StaticLinkList()  // O(n)
    {
        this->clear();
    }

protected:
    //typedef typename LinkList<T>::Node Node;
    using Node = typename LinkList<T>::Node;

    struct SNode : public Node
    {
        void *operator new (unsigned int size, void *loc)
        {
            (void)size;

            return loc;
        }
    };

    unsigned char m_space[N * sizeof(SNode)];
    char m_used[N];

    Node *create() override  // O(n)
    {
        SNode *ret = nullptr;

        for (int i=0; i<N; ++i)
        {
            if (m_used[i] == 0)
            {
                ret = reinterpret_cast<SNode*>(m_space) + i;
                ret = new(ret)SNode;
                m_used[i] = 1;
                break;
            }
        }

        return ret;
    }

    void destroy(Node *pn) override  // O(n)
    {
        SNode *space = reinterpret_cast<SNode*>(m_space);
        SNode *psn = dynamic_cast<SNode*>(pn);

        for (int i=0; i<N; ++i)
        {
            if (psn == (space + i))
            {
                m_used[i] = 0;
                pn->~Node();
                break;
            }
        }
    }
};

}

#endif // STATICLINKLIST_H
