#ifndef LIST_H
#define LIST_H

#include "Object.h"

namespace DTLib
{

template<typename T>
class List : public Object
{
public:
    List() {}
    virtual bool insert(const T &e) = 0;
    virtual bool insert(int i, const T &e) = 0;
    virtual bool remove(int i) = 0;
    virtual bool set(int i, const T &e) = 0;
    virtual bool get(int i, T &e) const = 0;
    virtual int  find(const T &e) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;

protected:
    List(const List&);
    List<T> &operator= (const List&);
};

}

#endif // LIST_H
