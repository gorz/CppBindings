#pragma once

#include <string>

#include "IXmlBinding.hpp"
#include "TXmlIO.hpp"

template<typename T, typename E>
class TXmlParentBinding : public IXmlBinding<T>
{
public:
    void read(T &obj, const TiXmlElement *parent);
    void write(const T &obj, TiXmlElement *parent);
};

template<typename T, typename E>
void TXmlParentBinding<T, E>::read(T &obj, const TiXmlElement *parent)
{
    TXmlIO<E>::read(obj, parent);
}

template<typename T, typename E>
void TXmlParentBinding<T, E>::write(const T &obj, TiXmlElement *parent)
{
    TXmlIO<E>::write(obj, parent);
}
