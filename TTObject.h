#ifndef TTOBJECT_H
#define TTOBJECT_H

struct TTObject;

#include <map>
#include <string>
#include <iostream>
#include "MemAllocator.h"
#include "TTLiteral.h"
#include "RefPtr.h"

#define DEFAULT_FIELD_COUNT 4

#define TT_NIL 0x00
#define TT_OBJECT 0x01
#define TT_EXPR 0x02
#define TT_LITERAL 0x04
#define TT_ENV 0x08
#define TT_STACK_FRAME 0x10
#define TT_MOVED_OBJECT 0x20

#define IS_SOME_TYPE(a, b) (!(!((a)->type == b)))

#define IS_NIL(a) IS_SOME_TYPE(a, TT_NIL)
#define IS_OBJECT(a) IS_SOME_TYPE(a, TT_OBJECT)
#define IS_EXPR(a) IS_SOME_TYPE(a, TT_EXPR)
#define IS_LITERAL(a) IS_SOME_TYPE(a, TT_LITERAL)
#define IS_ENV(a) IS_SOME_TYPE(a, TT_ENV)
#define IS_STACK_FRAME(a) IS_SOME_TYPE(a, TT_STACK_FRAME)
#define IS_MOVED_OBJECT(a) IS_SOME_TYPE(a, TT_MOVED_OBJECT)

/**
* TTObject is any object within this VM, that can be directly interfaced from
* the language itself.
*
* This abstract object divides into multiple basic objects identified by the VM.
*
* Any other object can be described by the object flag, as specified below.
* This might cause confusion, should be understood as a custom object identified
* the same way by the VM.
*/
struct TTObject
{
    TTObject **objects;  // BEWARE, upon GC this is used as pointer to new object
    uint8_t **names;

    uint32_t count;
    uint32_t size;
    uint8_t type;

    /**
    * Type specific flags
    *
    * for EXPRESSION - see Expression.h
    */
    uint8_t flags;


    /**
    * For future stuff (GC) only!
    */
    static void _gc_COPY_copy(TTObject **ptr, MemAllocator *oldMem, MemAllocator *newMem);

    /**
    * Objects must only be created using these functions.
    */
    static RefPtr<TTObject> createObject(uint8_t type, uint32_t fieldsPreallocated);
    static RefPtr<TTObject> createObject(uint8_t type);

    static std::vector<std::pair<std::string, RefPtr<TTObject> > > laterFields;

    /**
    * Not deep copy. Cannot do that due to cycle references.
    */
    static RefPtr<TTObject> clone(RefPtr<TTObject> cloned);


    /**
    * Field operations.
    */

    /**
    * Add a new field. Will return false if it alread exists.
    */
    bool addField(const uint8_t *name, RefPtr<TTObject> object);

    /**
    * Add a new field. Will return false if it alread exists.
    * Will not allocate string, will only use the existing ones.
    */
    bool __gc_safe_addField(const uint8_t *name, RefPtr<TTObject> object);

    /**
    * Returns true if the field name exists.
    */
    bool hasField(const uint8_t *name);

    /**
    * Returns an object from field by given name or NULL if not found.
    */
    TTObject *getField(const uint8_t *name);

    /**
    * Sets an object overwriting the old one, returns false and does nothing if
    * an old one is not found.
    */
    bool setField(const uint8_t *name, RefPtr<TTObject> object);

    /**
    * Returns an object from field by given name or NULL if not found.
    */
    TTLiteral *getLiteral();

    /**
    * Sets an object overwriting the old one, returns false and does nothing if
    * an old one is not found.
    */
    bool setLiteral(RefPtr<TTLiteral> object);

    /**
    * Prints the object to a human readable format.
    */
    void print(std::ostream &os, uint32_t level, bool recursive);
};

/**
* Outputs rich object info.
*/
std::ostream &operator << (std::ostream &os, RefPtr<TTObject> &object);

#endif
