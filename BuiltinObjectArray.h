#ifndef BUILTINOBJECTARRAY_H
#define BUILTINOBJECTARRAY_H

#include "Builtin.h"

class BuiltinObjectArraySize : public Builtin
{
public:
    virtual TTObject *invoke(TTObject *dest, std::vector<std::string> &argNames, std::vector<TTObject *> values);
};

class BuiltinObjectArrayAt : public Builtin
{
public:
    virtual TTObject *invoke(TTObject *dest, std::vector<std::string> &argNames, std::vector<TTObject *> values);
};

class BuiltinObjectArrayAtSet : public Builtin
{
public:
    virtual TTObject *invoke(TTObject *dest, std::vector<std::string> &argNames, std::vector<TTObject *> values);
};

class BuiltinObjectArrayEmpty : public Builtin
{
public:
    virtual TTObject *invoke(TTObject *dest, std::vector<std::string> &argNames, std::vector<TTObject *> values);
};

class BuiltinObjectArrayToString : public Builtin
{
public:
    virtual TTObject *invoke(TTObject *dest, std::vector<std::string> &argNames, std::vector<TTObject *> values);
};

#endif