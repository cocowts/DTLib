#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "Graph.h"
#include "Exception.h"
#include "LinkList.h"
#include "DynamicArray.h"

namespace DTLib
{

template <typename V, typename E>
class ListGraph : public Graph<V, E>
{
public:
    ListGraph(unsigned int n = 0)
    {
        for (unsigned int i=0; i<n; ++i)
        {
            addVertex();
        }
    }

    int addVertex()  // O(n)
    {
        int ret = -1;
        Vertex *v = new Vertex();

        if (v != nullptr)
        {
            m_list.insert(v);

            ret = m_list.length() - 1;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create vertex object ...");
        }

        return ret;
    }

    int addVertex(const V &value)  // O(n)
    {
        int ret = addVertex();

        if (ret >= 0)
        {
            setVertex(ret, value);
        }

        return ret;
    }

    void removeVertex()  // O(n*n)
    {
        if (m_list.length() > 0)
        {
            int index = m_list.length() - 1;
            Vertex *v = m_list.get(index);

            if (m_list.remove(index))
            {
                for (int i=(m_list.move(0), 0); !m_list.end(); ++i, m_list.next())
                {
                    int pos = m_list.current()->edge.find(Edge<E>(i, index));

                    if (pos >= 0)
                    {
                        m_list.current()->edge.remove(pos);
                    }
                }

                delete v->data;
                delete v;
            }
            else
            {
                THROW_EXCEPTION(InvalidOpertionExcetion, "No vertex in current graph ...");
            }
        }
    }

    V getVertex(int i) const override  // O(n)
    {
        V ret;

        if (!getVertex(i, ret))
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Parameter i is invalid ...");
        }

        return ret;
    }

    bool getVertex(int i, V &value) const override  // O(n)
    {
        bool ret = (0 <= i) && (i < vCount());

        if (ret)
        {
            Vertex *v = m_list.get(i);

            if (v->data != nullptr)
            {
                value = *(v->data);
            }
            else
            {
                THROW_EXCEPTION(InvalidOpertionExcetion, "No value assigned to this vertex ...");
            }
        }

        return ret;
    }

    bool setVertex(int i, const V &value) override  // O(n)
    {
        bool ret = (0 <= i) && (i < vCount());

        if (ret)
        {
            Vertex *v = m_list.get(i);
            V *data = v->data;

            if (data == nullptr)
            {
                data = new V();
            }

            if (data != nullptr)
            {
                *data = value;

                v->data = data;  // 异常安全！！！
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new vertex object ...");
            }
        }

        return ret;
    }

    SharedPointer<Array<int>> getAdjacent(int i) const override  // O(n)
    {
        DynamicArray<int> *ret = nullptr;

        if ((0 <= i) && (i < vCount()))
        {
            Vertex *v = m_list.get(i);

            ret = new DynamicArray<int>(v->edge.length());

            if (ret != nullptr)
            {
                for (int j=(v->edge.move(0), 0); !v->edge.end(); ++j, v->edge.next())
                {
                    ret->set(j, v->edge.current().e);
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret object ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Parameter i is invalid ...");
        }

        return ret;
    }

    bool isAdjacent(int i, int j) const override
    {
        return (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()) && (m_list.get(i)->edge.find(Edge<E>(i, j)) >=0);
    }

    E getEdge(int i, int j) const override  // O(n)
    {
        E ret;

        if (!getEdge(i, j, ret))
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Parameter <i, j> is invalid ...");
        }

        return ret;
    }

    bool getEdge(int i, int j, E &value) const override  // O(n)
    {
        bool ret = ((0 <= i) && (i < vCount()))
                && ((0 <= j) && (j < vCount()));

        if (ret)
        {
            Vertex *v = m_list.get(i);

            int pos = v->edge.find(Edge<E>(i, j));

            if (pos >= 0)
            {
                value = v->edge.get(pos).data;
            }
            else
            {
                THROW_EXCEPTION(InvalidOpertionExcetion, "No value assigned to this ret edge ...");
            }
        }

        return ret;
    }

    bool setEdge(int i, int j, const E &value) override  // O(n)
    {
        bool ret = ((0 <= i) && (i < vCount()))
                && ((0 <= j) && (j < vCount()));

        if (ret)
        {
            Vertex *v = m_list.get(i);
            int pos = v->edge.find(Edge<E>(i, j));

            if (pos >= 0)
            {
                ret = v->edge.set(pos, Edge<E>(i, j, value));
            }
            else
            {
                ret = v->edge.insert(0, Edge<E>(i, j, value));
            }
        }

        return ret;
    }

    bool removeEdge(int i, int j) override  // O(n)
    {
        bool ret = ((0 <= i) && (i < vCount()))
                && ((0 <= j) && (j < vCount()));

        if (ret)
        {
            Vertex *v = m_list.get(i);
            int pos = v->edge.find(Edge<E>(i, j));

            if (pos >= 0)
            {
                ret = v->edge.remove(pos);
            }
        }

        return ret;
    }

    int vCount() const override  // O(1)
    {
        return m_list.length();
    }

    int eCount() override  // O(n)
    {
        int ret = 0;

        for (m_list.move(0); !m_list.end(); m_list.next())
        {
            ret += m_list.current()->edge.length();
        }

        return ret;
    }

    int OD(int i) override  // O(n)
    {
        int ret = 0;

        if ((0 <= i) && (i < vCount()))
        {
            ret = m_list.get(i)->edge.length();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Parameter i is valid ...");
        }

        return ret;
    }

    int ID(int i) override  // O(n*n)
    {
        int ret = 0;

        if ((0 <= i) && (i < vCount()))
        {
            for (m_list.move(0); !m_list.end(); m_list.next())
            {
                LinkList<Edge<E>> &edge = m_list.current()->edge;

                for (edge.move(0); !edge.end(); edge.next())
                {
                    if (edge.current().e == i)
                    {
                        ++ret;
                        break;
                    }
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Parameter i is invalid ...");
        }

        return ret;
    }

    ~ListGraph()
    {
        while (m_list.length() > 0)
        {
            Vertex *toDel = m_list.get(0);

            m_list.remove(0);

            delete toDel->data;
            delete toDel;
        }
    }

protected:
    struct Vertex : public Object
    {
        V *data = nullptr;
        LinkList<Edge<E>> edge;
    };

    LinkList<Vertex*> m_list;

    ListGraph(const ListGraph<V, E> &) = default;
    ListGraph &operator = (const ListGraph<V, E> &) = default;
};

}

#endif // LISTGRAPH_H
