#pragma once

#include <string>

#include <tinyxml/tinyxml.h>

template<typename T>
class TXmlIO
{
public:
    static void write(const T &obj, TiXmlElement *parent);
    static void read(T &obj, const TiXmlElement *parent);
};

template<typename T>
void TXmlIO<T>::write(const T &obj, TiXmlElement *parent)
{
    typename T::Bindings b;
    b.writeXml(obj, parent);
}

template<typename T>
void TXmlIO<T>::read(T &obj, const TiXmlElement *parent)
{
    typename T::Bindings b;
    b.readXml(obj, parent);
}

template<>
void TXmlIO<int>::write(const int &obj, TiXmlElement *parent);

template<>
void TXmlIO<int>::read(int &obj, const TiXmlElement *parent);

template<>
void TXmlIO<double>::write(const double &obj, TiXmlElement *parent);

template<>
void TXmlIO<double>::read(double &obj, const TiXmlElement *parent);

template<>
void TXmlIO<std::string>::write(const std::string &obj, TiXmlElement *parent);

template<>
void TXmlIO<std::string>::read(std::string &obj, const TiXmlElement *parent);
