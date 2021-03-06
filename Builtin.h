#ifndef BUILTIN_H
#define BUILTIN_H

class Builtin;

#include <vector>
#include <string>
#include "TTObject.h"

#define BUILTIN_CHECK_ARGS_COUNT(x, y) \
    if (argNames.size() != x || values.size() != y)\
    {\
        std::cerr << "[Builtin]: Error: " << __PRETTY_FUNCTION__ << " function accepts " << x << " arguments and " << y << "values" << std::endl;  \
        KILL; \
    }\
    do {} while(false)

#define BUILTIN_CHECK_LITERAL(x) \
    if (values[x]->type != TT_LITERAL) \
    { \
        std::cerr << "[Builtin]: Error: " << __PRETTY_FUNCTION__ << " builtin function cannot use anything else than TT_LITERAL." << std::endl; \
        KILL; \
    } \
    do {} while(false)

#define BUILTIN_CHECK_EXPRESSION(x) \
    if (values[x]->type != TT_EXPR) \
    { \
        std::cerr << "[Builtin]: Error: " << __PRETTY_FUNCTION__ << " builtin function cannot use anything else than TT_EXPR." << std::endl; \
        KILL; \
    } \
    do {} while(false)

#define BUILTIN_CHECK_INTEGER(x) \
    if (values[x]->getLiteral()->type != LITERAL_TYPE_INTEGER) \
    { \
        std::cerr << "[Builtin]: Error: " << __PRETTY_FUNCTION__ << " function can only use integers now." << std::endl; \
        KILL; \
    } \
    do {} while(false)

#define BUILTIN_CHECK_STRING(x) \
    if (values[x]->getLiteral()->type != LITERAL_TYPE_STRING) \
    { \
        std::cerr << "[Builtin]: Error: " << __PRETTY_FUNCTION__ << " function can only use strings now." << std::endl; \
        KILL; \
    } \
    do {} while(false)

#define BUILTIN_CHECK_BYTE_ARRAY(x) \
    if (values[x]->getLiteral()->type != LITERAL_TYPE_BYTE_ARRAY) \
    { \
        std::cerr << "[Builtin]: Error: " << __PRETTY_FUNCTION__ << " function can only use byte array now." << std::endl; \
        KILL; \
    } \
    do {} while(false)

#define BUILTIN_CHECK_LITERAL_SIZE(x, size) \
    if (values[x]->getLiteral()->length != size) \
    { \
        std::cerr << "[Builtin]: Error: " << __PRETTY_FUNCTION__ << " invalid literal size. expected: " << size << " got: " << values[x]->getLiteral()->length << std::endl; \
        KILL; \
    } \
    do {} while(false)

class Builtin
{
public:
    virtual RefPtr<TTObject> invoke(RefPtr<TTObject> dest, std::vector<std::string> &argNames, std::vector<RefPtr<TTObject> > values, RefPtr<TTObject> env, RefPtr<TTObject> thiz) = 0;
};

#endif
