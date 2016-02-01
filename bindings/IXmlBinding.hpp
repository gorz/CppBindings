#pragma once

#include <string>

#include <tinyxml/tinyxml.h>

template<typename T>
class IXmlBinding
{
public:
    virtual ~IXmlBinding() {}
    virtual void write(const T &obj, TiXmlElement *parent) = 0;
    virtual void read(T &obj, const TiXmlElement *parent) = 0;
};
