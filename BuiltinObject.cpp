#include "BuiltinObject.h"
#include "Common.h"
#include "Runtime.h"
#include "Evaluator.h"

RefPtr<TTObject> BuiltinObjectAlloc::invoke(RefPtr<TTObject> dest, std::vector<std::string> &argNames, std::vector<RefPtr<TTObject> > values, RefPtr<TTObject> env, RefPtr<TTObject> thiz)
{
#ifdef DEBUG
    std::cout << "[Builtin]: Allocating a new object." << std::endl;
#endif

    return TTObject::createObject(TT_OBJECT);
}

RefPtr<TTObject> BuiltinObjectAddField::invoke(RefPtr<TTObject> dest, std::vector<std::string> &argNames, std::vector<RefPtr<TTObject> > values, RefPtr<TTObject> env, RefPtr<TTObject> thiz)
{
    if (argNames.size() != 2 || values.size() != 2)
    {
        std::cerr << "[Builtin]: Adding field accepts two arguments only." << std::endl;
        KILL;
    }
    std::string name = (char *) values[1]->getLiteral()->data;
#ifdef DEBUG
    std::cout << "[Builtin]: Adding field '" << name << "'." << std::endl;
#endif

    RefPtr<TTObject> object = values[0];
#ifdef DEBUG
    std::cout << "[Builtin]: Before add: " << object << std::endl;
#endif

    object->addField(TO_TT_STR(name.c_str()), Runtime::globalEnvironment->getField(TO_TT_STR("nil")));

#ifdef DEBUG
    std::cout << "[Builtin]: After add: " << object << std::endl;
#endif

    return dest;
}

RefPtr<TTObject> BuiltinObjectGetter::invoke(RefPtr<TTObject> dest, std::vector<std::string> &argNames, std::vector<RefPtr<TTObject> > values, RefPtr<TTObject> env, RefPtr<TTObject> thiz)
{
    if (argNames.size() != 2 || values.size() != 2)
    {
        std::cerr << "[Builtin]: Getting field accepts two arguments only." << std::endl;
        KILL;
    }
    else
    {
        if (values[1]->type != TT_LITERAL)
        {
            std::cerr << "[Builtin]: Getting field accepts literal value only!" << std::endl;
            KILL;
        }
    }
    std::string name = (char *) values[1]->getLiteral()->data;
#ifdef DEBUG
    std::cout << "[Builtin]: Getting field '" << name << "'." << std::endl;
#endif

    RefPtr<TTObject> object = values[0];
#ifdef DEBUG
    std::cout << "[Builtin]: Checking field in dest = " << object << std::endl;
#endif

    if (!object->hasField(TO_TT_STR(name.c_str())))
    {
        return Runtime::globalEnvironment->getField(TO_TT_STR("nil"));
    }
#ifdef DEBUG
    std::cout << "[Builtin]: Getting field from dest = " << object << std::endl;
#endif

    return object->getField(TO_TT_STR(name.c_str()));
}

RefPtr<TTObject> BuiltinObjectSetter::invoke(RefPtr<TTObject> dest, std::vector<std::string> &argNames, std::vector<RefPtr<TTObject> > values, RefPtr<TTObject> env, RefPtr<TTObject> thiz)
{
    if (argNames.size() != 3 || values.size() != 3)
    {
        std::cerr << "[Builtin]: Setting field accepts 3 arguments only." << std::endl;
        KILL;
    }
    else
    {
        if (values[1]->type != TT_LITERAL)
        {
            std::cerr << "[Builtin]: Setting field accepts literal value only!" << std::endl;
            KILL;
        }
    }
    if (argNames[2] != "value")
    {
        std::cerr << "[Builtin]: Setting field's third argument must be 'value', '"
                << argNames[2] << "' given!" << std::endl;
        KILL;
    }
    std::string name = (char *) values[1]->getLiteral()->data;
#ifdef DEBUG
    std::cout << "[Builtin]: Setting field '" << name << "'." << std::endl;
#endif

    RefPtr<TTObject> object = values[0];
#ifdef DEBUG
    std::cout << "[Builtin]: Checking field in dest = " << object << std::endl;
#endif

    if (!object->hasField(TO_TT_STR(name.c_str())))
    {
        std::cerr << "[Builtin]: Field not found!" << std::endl;
        KILL;
    }
#ifdef DEBUG
    std::cout << "[Builtin]: Setting field in dest = " << object << std::endl;
#endif

    object->setField(TO_TT_STR(name.c_str()), values[2]);

    return dest;
}

RefPtr<TTObject> BuiltinObjectDebugPrint::invoke(RefPtr<TTObject> dest, std::vector<std::string> &argNames, std::vector<RefPtr<TTObject> > values, RefPtr<TTObject> env, RefPtr<TTObject> thiz)
{
    if (argNames.size() != 1 || values.size() != 1)
    {
        std::cerr << "[Builtin]: Print object accepts one argument only." << std::endl;
        KILL;
    }

    std::cout << "DBG PRINT ***************************** BEGIN ********************************" << std::endl;
    values[0]->print(std::cout, 1, false);
    std::cout << std::endl << "DBG PRINT ****************************** END *********************************" << std::endl;

    return dest;
}

RefPtr<TTObject> BuiltinObjectDebugPrintRec::invoke(RefPtr<TTObject> dest, std::vector<std::string> &argNames, std::vector<RefPtr<TTObject> > values, RefPtr<TTObject> env, RefPtr<TTObject> thiz)
{
    if (argNames.size() != 1 || values.size() != 1)
    {
        std::cerr << "[Builtin]: Print object accepts one argument only." << std::endl;
        KILL;
    }

    std::cout << "DBG PRINT REC ***************************** BEGIN ********************************" << std::endl;
    values[0]->print(std::cout, 1, true);
    std::cout << "DBG PRINT REC ****************************** END *********************************" << std::endl;

    return dest;
}

RefPtr<TTObject> BuiltinObjectDebugPrintString::invoke(RefPtr<TTObject> dest, std::vector<std::string> &argNames, std::vector<RefPtr<TTObject> > values, RefPtr<TTObject> env, RefPtr<TTObject> thiz)
{
    if (argNames.size() != 1 || values.size() != 1)
    {
        std::cerr << "[Builtin]: PrintString object accepts one argument only." << std::endl;
        KILL;
    }

    if (values[0]->type != TT_LITERAL || values[0]->getLiteral()->type != LITERAL_TYPE_STRING)
    {
        std::cerr << "[Builtin]: PrintString object not string literal!" << std::endl;
        KILL;
    }

    std::string str = (const char *) values[0]->getLiteral()->data;

    std::cout << "DBG: " << str << std::endl;

    return dest;
}

RefPtr<TTObject> BuiltinObjectDebugGC::invoke(RefPtr<TTObject> dest, std::vector<std::string> &argNames, std::vector<RefPtr<TTObject> > values, RefPtr<TTObject> env, RefPtr<TTObject> thiz)
{
    BUILTIN_CHECK_ARGS_COUNT(1, 0);

    Runtime::runCopyGC();

    return dest;
}

RefPtr<TTObject> BuiltinObjectClone::invoke(RefPtr<TTObject> dest, std::vector<std::string> &argNames, std::vector<RefPtr<TTObject> > values, RefPtr<TTObject> env, RefPtr<TTObject> thiz)
{
    if (argNames.size() != 1 || values.size() != 1)
    {
        std::cerr << "[Builtin]: Clone builting function accepts one argument only." << std::endl;
        KILL;
    }

    RefPtr<TTObject> cloned = values[0];
    RefPtr<TTObject> res = TTObject::clone(cloned);

    return  res;
}

RefPtr<TTObject> BuiltinObjectNew::invoke(RefPtr<TTObject> dest, std::vector<std::string> &argNames, std::vector<RefPtr<TTObject> > values, RefPtr<TTObject> env, RefPtr<TTObject> thiz)
{
    if (argNames.size() != 1 || values.size() != 0)
    {
        std::cerr << "[Builtin]: New builtin function accepts no arguments." << std::endl;
        KILL;
    }

    RefPtr<TTObject> res = TTObject::createObject(TT_OBJECT);
    res->setField(TO_TT_STR("parent"), dest);

    return res;
}

RefPtr<TTObject> BuiltinObjectGetFieldNames::invoke(RefPtr<TTObject> dest, std::vector<std::string> &argNames, std::vector<RefPtr<TTObject> > values, RefPtr<TTObject> env, RefPtr<TTObject> thiz)
{
    BUILTIN_CHECK_ARGS_COUNT(1, 0);

    uint32_t size = dest->size;
    uint32_t nonLiteralSize = 0;

    for(uint32_t i = 0; i < size; i++)
    {
        if (dest->names[i])
        {
            if (*dest->names[i])
            {
                nonLiteralSize++;
            }
        }
    }

    RefPtr<TTObject> result = TTLiteral::createObjectArray(nonLiteralSize);

    uint32_t objI = 0;
    for(uint32_t i = 0; i < size; i++)
    {
        if(dest->names[i])
        {
            if(*dest->names[i])
            {
                std::string nameStr = (const char *) dest->names[i];
                RefPtr<TTObject> name = TTLiteral::createStringLiteral(TO_TT_STR(nameStr.c_str()));
                ((TTObject **) result->getLiteral()->data)[objI++] = &name;
            }
        }
    }

    return result;
}

RefPtr<TTObject> BuiltinObjectGetFieldValues::invoke(RefPtr<TTObject> dest, std::vector<std::string> &argNames, std::vector<RefPtr<TTObject> > values, RefPtr<TTObject> env, RefPtr<TTObject> thiz)
{
    BUILTIN_CHECK_ARGS_COUNT(1, 0);

    uint32_t size = dest->size;
    uint32_t nonLiteralSize = 0;

    for(uint32_t i = 0; i < size; i++)
    {
        if (dest->names[i])
        {
            if (*dest->names[i])
            {
                nonLiteralSize++;
            }
        }
    }

    RefPtr<TTObject> result = TTLiteral::createObjectArray(nonLiteralSize);

    uint32_t objI = 0;
    for(uint32_t i = 0; i < size; i++)
    {
        if(dest->names[i])
        {
            if(*dest->names[i])
            {
                ((TTObject **) result->getLiteral()->data)[objI++] = dest->objects[i];
            }
        }
    }

    return result;
}

RefPtr<TTObject> BuiltinObjectToString::invoke(RefPtr<TTObject> dest, std::vector<std::string> &argNames, std::vector<RefPtr<TTObject> > values, RefPtr<TTObject> env, RefPtr<TTObject> thiz)
{
    if (argNames.size() != 1 || values.size() != 0)
    {
        std::cerr << "[Builtin]: ToString builtin function accepts no arguments." << std::endl;
        KILL;
    }

    const char *resStr = "Object";

    if(!&dest)
    {
        resStr = "NULL";
    }
/*
    if(dest->type == TT_LITERAL)
    {
       return dest->getLiteral()->onMessage(dest, argNames[0], argNames, values);
    }
*/
    RefPtr<TTObject> res = TTLiteral::createStringLiteral(TO_TT_STR(resStr));

    return res;
}
