#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "LinkList.h"

namespace DTLib
{

template <typename T>
class GTreeNode : public TreeNode<T>
{
public:
    LinkList<GTreeNode<T>*> child;

    GTreeNode() = default;

    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T> *ret = new GTreeNode<T>();

        if (ret != nullptr)
        {
            ret->m_flag = true;
        }

        return ret;
    }

protected:
    GTreeNode(const GTreeNode<T>&) = default;
    GTreeNode<T>& operator = (const GTreeNode<T>&) = default;
};

}

#endif // GTREENODE_H
