#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "SharedPointer.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "LinkStack.h"
#include "Sort.h"

namespace DTLib
{

template <typename E>
struct Edge : public Object
{
    int b;
    int e;
    E data;

    Edge(int i=-1, int j=-1)  : b(i), e(j)
    {
    }

    Edge(int i, int j, const E &value) : b(i), e(j), data(value)
    {
    }

    bool operator == (const Edge &obj)
    {
        return (b == obj.b) && (e == obj.e);
    }

    bool operator != (const Edge &obj)
    {
        return !(*this == obj);
    }

    bool operator < (const Edge &obj)
    {
        return (data < obj.data);
    }

    bool operator > (const Edge &obj)
    {
        return (data > obj.data);
    }
};

template <typename V, typename E>
class Graph : public Object
{
public:
    virtual V getVertex(int i) const = 0;
    virtual bool getVertex(int i, V &value) const = 0;
    virtual bool setVertex(int i, const V &value) = 0;
    virtual SharedPointer<Array<int>> getAdjacent(int i) const = 0;
    virtual bool isAdjacent(int i, int j) const = 0;
    virtual E getEdge(int i, int j) const = 0;
    virtual bool getEdge(int i, int j, E &value) const = 0;
    virtual bool setEdge(int i, int j, const E &value) = 0;
    virtual bool removeEdge(int i, int j) = 0;
    virtual int vCount() const = 0;
    virtual int eCount() = 0;
    virtual int OD(int i) = 0;
    virtual int ID(int i) = 0;
    virtual int TD(int i)
    {
        return OD(i) + ID(i);
    }

    bool asUndirected()
    {
        bool ret = true;

        for (int i=0; i<vCount() && ret; ++i)
        {
            for (int j=0; j<vCount() && ret; ++j)
            {
                if (isAdjacent(i, j))
                {
                    ret = isAdjacent(j, i) && (getEdge(i, j) == getEdge(j, i));
                }
            }
        }

        return ret;
    }

    SharedPointer<Array<int>> BFS(int i)
    {
        DynamicArray<int> *ret = nullptr;

        if ((0 <= i) && (i < vCount()))
        {
            LinkQueue<int> q;
            LinkQueue<int> r;
            DynamicArray<bool> visited(vCount());

            for (int j=0; j<visited.length(); ++j)
            {
                visited[j] = false;
            }

            q.add(i);

            while (q.length() > 0)
            {
                int v = q.front();

                q.remove();

                if (!visited[v])
                {
                    SharedPointer<Array<int>> aj = getAdjacent(v);

                    for (int j=0; j<aj->length(); ++j)
                    {
                        q.add((*aj)[j]);
                    }

                    r.add(v);

                    visited[v] = true;
                }
            }

            ret = toArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Parameter i is invalid ...");
        }

        return ret;
    }

#ifdef DFS_R
    SharedPointer<Array<int>> DFS(int i)  // 递归版深度优先遍历
    {
        DynamicArray<int> *ret = nullptr;

        if ((0 <= i) && (i < vCount()))
        {
            LinkQueue<int> r;
            DynamicArray<bool> visited(vCount());

            for (int j=0; j<vCount(); ++j)
            {
                visited[j] = false;
            }

            DFP(i, visited, r);

            ret = toArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Parameter i is invalid ...");
        }

        return ret;
    }
#else
    SharedPointer<Array<int>> DFS(int i)
    {
        DynamicArray<int> *ret = nullptr;

        if ((0 <= i) && (i < vCount()))
        {
            LinkStack<int> s;
            LinkQueue<int> r;
            DynamicArray<bool> visited(vCount());

            for (int j=0; j<visited.length(); ++j)
            {
                visited[j] = false;
            }

            s.push(i);

            while (s.size() > 0)
            {
                int v = s.top();

                s.pop();

                if (!visited[v])
                {
                    SharedPointer<Array<int>> aj = getAdjacent(v);

                    for (int j=aj->length()-1; j>=0; --j)
                    {
                        s.push((*aj)[j]);
                    }

                    r.add(v);

                    visited[v] = true;
                }
            }

            ret = toArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Parameter i is invalid ...");
        }

        return ret;
    } 

#endif

    SharedPointer<Array<Edge<E>>> prim(const E &LIMIT, const bool MINIMUM = true)
    {
        LinkQueue<Edge<E>> ret;

        if (asUndirected())
        {
            DynamicArray<int> adjVex(vCount());
            DynamicArray<bool> mark(vCount());
            DynamicArray<E> cost(vCount());
            SharedPointer<Array<int>> aj = nullptr;
            bool end = false;
            int v = 0;

            for (int i=0; i<vCount(); ++i)
            {
                adjVex[i] = -1;
                mark[i] = false;
                cost[i] = LIMIT;
            }

            mark[v] = true;

            aj = getAdjacent(v);

            for (int i=0; i<aj->length(); ++i)
            {
                cost[(*aj)[i]] = getEdge(v, (*aj)[i]);
                adjVex[(*aj)[i]] = v;
            }

            for (int i=0; i<vCount() && !end; ++i)
            {
                E m = LIMIT;
                int k = -1;

                for (int j=0; j<vCount(); ++j)
                {
                    if (!mark[j] && (MINIMUM ? (m > cost[j]) : (m < cost[j])))
                    {
                        m = cost[j];
                        k = j;
                    }
                }

                end = (k == -1);

                if (!end)
                {
                    ret.add(Edge<E>(adjVex[k],k, getEdge(adjVex[k],k)));

                    mark[k] = true;

                    aj = getAdjacent(k);

                    for (int j=0; j<aj->length(); ++j)
                    {
                        if (!mark[(*aj)[j]] && (MINIMUM ? (getEdge(k, (*aj)[j]) < cost[(*aj)[j]]) : (getEdge(k, (*aj)[j]) > cost[(*aj)[j]])))
                        {
                            cost[(*aj)[j]] = getEdge(k, (*aj)[j]);

                            adjVex[(*aj)[j]] = k;
                        }
                    }
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOpertionExcetion, "Prim operator is for undirected grap only ...");
        }

        if (ret.length() != (vCount() - 1))
        {
            THROW_EXCEPTION(InvalidOpertionExcetion, "No enough edge for prim operation ...");
        }

        return toArray(ret);
    }

    SharedPointer<Array<Edge<E>>> Kruskal( const bool MINIMUM = true)
    {
        LinkQueue<Edge<E>> ret;
        DynamicArray<int> p(vCount());
        SharedPointer<Array<Edge<E>>> edges = getUndirectedEdges();

        for (int i=0; i<p.length(); ++i)
        {
            p[i] = -1;
        }

        Sort::Shell(*edges, MINIMUM);

        for (int i=0; (i<edges->length()) && (ret.length() < (vCount()-1)); ++i)
        {
            int b = find(p, (*edges)[i].b);
            int e = find(p, (*edges)[i].e);

            if (b != e)
            {
                p[e] = b;

                ret.add((*edges)[i]);
            }
        }

        if (ret.length() != vCount() - 1)
        {
            THROW_EXCEPTION(InvalidOpertionExcetion, "No enough edges for Kruskal operation ...");
        }

        return toArray(ret);
    }

    SharedPointer<Array<int>> dijkstra(int i, int j, const E &LIMIT)
    {
        LinkQueue<int> ret;

        if ((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()))
        {
            DynamicArray<E> dist(vCount());
            DynamicArray<int> path(vCount());
            DynamicArray<bool> mark(vCount());

            for (int k=0; k<vCount(); ++k)
            {
                mark[k] = false;
                path[k] = -1;

                dist[k] = isAdjacent(i, k) ? (path[k]=i, getEdge(i, k)) : LIMIT;
            }

            mark[i] = true;

            for (int k=0; k<vCount(); ++k)
            {
                E m = LIMIT;
                int u = -1;

                for (int w=0; w<vCount(); ++w)
                {
                    if (!mark[w] && dist[w] < m)
                    {
                        m = dist[w];
                        u = w;
                    }
                }

                if (u == -1)
                {
                    break;
                }

                mark[u] = true;

                for (int w=0; w<vCount(); ++w)
                {
                    if (!mark[w] && isAdjacent(u, w) && (dist[u] + getEdge(u, w) < dist[w]))
                    {
                        dist[w] = dist[u] + getEdge(u, w);
                        path[w] = u;
                    }
                }
            }

            LinkStack<int> s;

            s.push(j);

            for (int k=path[j]; k!=-1; k=path[k])
            {
                s.push(k);
            }

            while (s.size() > 0)
            {
                ret.add(s.top());

                s.pop();
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOpertionExcetion, "Parameter <i, j> is invalid ...");
        }

        if (ret.length() < 2)
        {
            THROW_EXCEPTION(ArithmeticExcption, "This is no path from i to j ...");
        }

        return toArray(ret);
    }

    SharedPointer<Array<int>> floyd(int x, int y, const E &LIMIT)
    {
        LinkQueue<int> ret;

        if ((0 <= x) && (x < vCount())  && (0 <= y) && (y < vCount()))
        {
            DynamicArray<DynamicArray<E>> dist(vCount());
            DynamicArray<DynamicArray<int>> path(vCount());

            for (int k=0; k<vCount(); ++k)
            {
                dist[k].resize(vCount());
                path[k].resize(vCount());
            }

            for (int i=0; i<vCount(); ++i)
            {
                for (int j=0; j<vCount(); ++j)
                {
                    dist[i][j] = isAdjacent(i, j) ? (path[i][j] = j, getEdge(i, j)) : LIMIT;
                }
            }

            for (int k=0; k<vCount(); ++k)
            {
                for (int i=0; i<vCount(); ++i)
                {
                    for (int j=0; j<vCount(); ++j)
                    {
                        if (dist[i][j] > (dist[i][k] + dist[k][j]))
                        {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            path[i][j] = path[i][k];
                        }
                    }
                }
            }

            while ((x != -1) && (x != y))
            {
                ret.add(x);
                x = path[x][y];
            }

            if (x != -1)
            {
                ret.add(x);
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterExcetion, "Parameter <x, y> is invalid ...");
        }

        if (ret.length() < 2)
        {
            THROW_EXCEPTION(ArithmeticExcption, "This is no path from x to y ...");
        }

        return toArray(ret);
    }


protected:
    template <typename T>
    DynamicArray<T>* toArray(LinkQueue<T> &queue)
    {
        DynamicArray<T> *ret = new DynamicArray<T>(queue.length());

        if (ret != nullptr)
        {
            for (int i=0; i<ret->length(); ++i, queue.remove())
            {
                ret->set(i, queue.front());
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret obj ...");
        }

        return ret;
    }

#ifdef DFS_R
    void DFP(int i, DynamicArray<bool> &visited, LinkQueue<int>& queue)
    {
        if (!visited[i])
        {
            queue.add(i);

            visited[i] = true;

            SharedPointer<Array<int>> aj = getAdjacent(i);

            for (int j=0; j<aj->length(); ++j)
            {
                DFP((*aj)[j], visited, queue);
            }
        }
    }

#endif

    int find(Array<int> &p, int v)
    {
        while (p[v] != -1)
        {
            v = p[v];
        }

        return v;
    }

    SharedPointer<Array<Edge<E>>> getUndirectedEdges()
    {
        DynamicArray<Edge<E>> *ret = nullptr;

        if (asUndirected())
        {
            LinkQueue<Edge<E>> queue;

            for (int i=0; i<vCount(); ++i)
            {
                for (int j=0; j<vCount(); ++j)
                {
                    if (isAdjacent(i, j))
                    {
                        queue.add(Edge<E>(i, j, getEdge(i, j)));
                    }
                }
            }

            ret = toArray(queue);
        }
        else
        {
            THROW_EXCEPTION(InvalidOpertionExcetion, "This function is for undirected graph only ...");
        }

        return ret;
    }
};

}

#endif // GRAPH_H
