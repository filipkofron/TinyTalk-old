#include "RefPtrMap.h"

#define REF_PTR_MAX_VALS (8192 * 32) // must be 2 to the power of n !!!

#define CALC_INDEX(ptr, size) ((int) ((((uint16_t *) &refPtr)[0] * 3389) ^ (((uint16_t *) &refPtr)[1] * 2039 + 1))  & (size - 1))

RefPtrMap::RefPtrMap()
{
    std::cout << "RefPtrMap constructor" << std::endl;
#ifdef HASHMAP_FAST
    vals = new RefPtrBase *[REF_PTR_MAX_VALS];
    memset(vals, 0, sizeof(RefPtrBase *) * REF_PTR_MAX_VALS);
#endif
}

RefPtrMap::~RefPtrMap()
{
#ifdef HASHMAP_FAST
    delete [] vals;
#endif
}

void RefPtrMap::reg_threadunsafe(RefPtrBase *refPtr)
{
#ifdef HASHMAP_FAST
    // TODO: Check endian during compile time!
    int index = CALC_INDEX(refPtr, REF_PTR_MAX_VALS);
    int stop = index;
    while(vals[index])
    {
        index = (int) ((index + 1) % REF_PTR_MAX_VALS);
        if(index == stop)
        {
            std::cerr << "RefPTRMAP Out of slots!" << std::endl;
            KILL;
        }
    }

    vals[index] = refPtr;
#else
    refs.insert(refPtr);
#endif
}

void RefPtrMap::reg(RefPtrBase *refPtr)
{
    lock.lock();
#ifdef HASHMAP_FAST
    // TODO: Check endian during compile time!
    int index = CALC_INDEX(refPtr, REF_PTR_MAX_VALS);
    int stop = index;
    while(vals[index])
    {
        index = (int) ((index + 1) % REF_PTR_MAX_VALS);
        if(index == stop)
        {
            std::cerr << "RefPTRMAP Out of slots!" << std::endl;
            KILL;
        }
    }

    vals[index] = refPtr;
#else
    refs.insert(refPtr);
#endif
    lock.unlock();
}

void RefPtrMap::unreg(RefPtrBase *refPtr)
{
    lock.lock();
#ifdef HASHMAP_FAST
    // TODO: Check endian during compile time!, use full size!
    int index = CALC_INDEX(refPtr, REF_PTR_MAX_VALS);
    int stop = index;
    while(vals[index] != refPtr)
    {
        index = (index + 1) % REF_PTR_MAX_VALS;
        if(index == stop)
        {
            std::cerr << "RefPTRMAP slot not found!" << std::endl;
            KILL;
        }
    }
    vals[index] = NULL;
    RefPtrBase *temp;
    stop = ++index;
    while(vals[index])
    {
        temp = vals[index];
        vals[index] = NULL;
        reg_threadunsafe(temp);

        index = (index + 1) % REF_PTR_MAX_VALS;
        if(index == stop)
        {
            std::cerr << "RefPTRMAP slot is FULL!" << std::endl;
            KILL;
        }
    }
#else
    refs.erase(refPtr);
#endif
    lock.unlock();
}

std::vector<RefPtrBase *> RefPtrMap::collectRoots()
{
    std::vector<RefPtrBase *> ptrs;

#ifdef HASHMAP_FAST
    for(size_t i = 0; i < REF_PTR_MAX_VALS; i++)
    {
        if(vals[i])
        {
            ptrs.push_back(vals[i]);
        }
    }
#else
    for(auto ptr : refs)
    {
        ptrs.push_back(ptr);
    }
#endif


    return ptrs;
}

void RefPtrMap::updateRoots()
{
#ifdef HASHMAP_FAST
    for(size_t i = 0; i < REF_PTR_MAX_VALS; i++)
    {
        if(vals[i] && MemAllocator::getCurrent()->isInside(vals[i]->ptr))
        {
            vals[i]->ptr = *(uintptr_t *) vals[i]->ptr;
        }
    }
#else
    for(auto ptr : refs)
    {
        if(!MemAllocator::getCurrent()->isInside(ptr->ptr))
        {
            std::cerr << "RefPtrMap::updateRoots(): Error: ptr: " << (unsigned long) ptr->ptr << " not inside the new memory!!!" << std::endl;
            *(int *) NULL = 0;
        }
        ptr->ptr = *(uintptr_t *) ptr->ptr;
    }
#endif
}
