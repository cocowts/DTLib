#ifndef DUALSTATICLINKLIST_H
#define DUALSTATICLINKLIST_H

#include "DualLinkList.h"

#include <cstdlib>

namespace  DTLib
{

template <typename T, int N>
class DualStaticLinkList : public DualLinkList<T>
{
public:
    DualStaticLinkList()  // O(n)
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

    ~DualStaticLinkList()  // O(n)
    {
        this->clear();
    }

protected:
    using Node = typename DualLinkList<T>::Node;

    struct SNode : public Node
    {
        void *operator new(unsigned int size, void *loc)  // O(1)
        {
            (void)size;

            return loc;
        }
    };

    unsigned char m_space[sizeof(SNode) * N];
    char m_used[N];

    Node *create()  // O(n)
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

    void destroy(Node *pn) // O(n)
    {
        SNode *space = reinterpret_cast<SNode*>(m_space);
        SNode *psn = dynamic_cast<SNode*>(pn);

        for (int i=0; i<N; ++i)
        {
            if (psn == (space + i))
            {
                m_used[i] = 0;
                psn->~Node();
                break;
            }
        }
    }
};

}

#endif // DUALSTATICLINKLIST_H
