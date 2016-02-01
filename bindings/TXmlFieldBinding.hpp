#pragma once

#include <string>

#include "IXmlBinding.hpp"
#include "TXmlIO.hpp"

template<typename T, typename E>
class TXmlFieldBinding : public IXmlBinding<T>
{
public:
    TXmlFieldBinding(std::string fieldName, E T::* pointer);

    void read(T &obj, const TiXmlElement *parent);
    void write(const T &obj, TiXmlElement *parent);
private:
    std::string mFieldName;
    E T::* mPointer;
};

template<typename T, typename E>
TXmlFieldBinding<T, E>::TXmlFieldBinding(std::string fieldName, E T::* pointer)
    : mFieldName(fieldName)
    , mPointer(pointer)
{
}

template<typename T, typename E>
void TXmlFieldBinding<T, E>::read(T &obj, const TiXmlElement *parent)
{
    const TiXmlElement *current = parent->FirstChildElement(mFieldName);
    TXmlIO<E>::read(obj.*mPointer, current);
}

template<typename T, typename E>
void TXmlFieldBinding<T, E>::write(const T &obj, TiXmlElement *parent)
{
    TiXmlElement *current = new TiXmlElement(mFieldName);
    TXmlIO<E>::write(obj.*mPointer, current);
    parent->LinkEndChild(current);
}

template<typename T, typename E>
IXmlBinding<T> *makeXmlFieldBinding(std::string fieldName, E T::* pointer)
{
    return new TXmlFieldBinding<T, E>(fieldName, pointer);
}
