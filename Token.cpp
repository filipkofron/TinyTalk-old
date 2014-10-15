#include "Token.h"

Token::Token()
        : type(Type::INVALID), value("")
{

}

Token::Token(const Type &type)
        : type(type), value("")
{

}

Token::Token(const Type &type, const std::string &value)
    : type(type), value(value)
{

}

const Token::Type &Token::getType()
{
    return type;
}

const std::string &Token::getValue()
{
    return value;
}

const char *Token::getTypeInfo()
{
    switch(getType())
    {
        case Type::SYMBOL:
        case Type::INTEGER:
        case Type::STRING:
        case Type::ASSIGNMENT:
        case Type::CHARACTER:
        case Type::PARENTHESIS_OPEN:
        case Type::PARENTHESIS_CLOSE:
        case Type::BLOCK_OPEN:
        case Type::BLOCK_CLOSE:
        case Type::INVALID:
        case Type::TEOF:
            return TypeStrings[getType()];
        default:
            return "Unknown";
    }
}
