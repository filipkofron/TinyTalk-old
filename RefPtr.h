#ifndef REFPTR_H
#define REFPTR_H

class RefPtrBase;

template <class T>
class RefPtr;

#include <cstdint>
#include "RefPtrMap.h"
#include "TTObject.h"

class RefPtrBase
{
protected:
    uintptr_t ptr;
    RefPtrBase(uintptr_t ptr, bool object);
    ~RefPtrBase();

    void setBasePtr(uintptr_t ptr);
public:
    friend class RefPtrMap;
};

template <class T>
class RefPtr : public RefPtrBase
{
public:
    RefPtr()
        : RefPtrBase((uintptr_t) NULL, isObject((T *) NULL))
    {
    }

    RefPtr(T *ptr)
        : RefPtrBase((uintptr_t) ptr, isObject(ptr))
    {
    }

    ~RefPtr()
    {

    }

    bool isObject(TTObject *object)
    {
        return true;
    }

    bool isObject(TTLiteral *object)
    {
        return false;
    }

    void setPtr(T *ptr)
    {
        setBasePtr((uintptr_t) ptr);
    }

    T *getPtr()
    {
        return (T *) ptr;
    }
};

#endif
