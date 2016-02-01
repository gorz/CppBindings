
#include <sstream>
#include "TXmlIO.hpp"

template<>
void TXmlIO<int>::write(const int &obj, TiXmlElement *parent)
{
    std::stringstream ss;
    ss << obj;
    parent->SetAttribute("value", ss.str());
}

template<>
void TXmlIO<int>::read(int &obj, const TiXmlElement *parent)
{
    const char *str = parent->Attribute("value");
    std::stringstream ss;
    ss << str;
    ss >> obj;
}

template<>
void TXmlIO<double>::write(const double &obj, TiXmlElement *parent)
{
    std::stringstream ss;
    ss << obj;
    parent->SetAttribute("value", ss.str());
}

template<>
void TXmlIO<double>::read(double &obj, const TiXmlElement *parent)
{
    const char *str = parent->Attribute("value");
    std::stringstream ss;
    ss << str;
    ss >> obj;
}

template<>
void TXmlIO<std::string>::write(const std::string &obj, TiXmlElement *parent)
{
    parent->SetAttribute("value", obj);
}

template<>
void TXmlIO<std::string>::read(std::string &obj, const TiXmlElement *parent)
{
    const char *str = parent->Attribute("value");
    obj = std::string(str);
}
