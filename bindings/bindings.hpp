#pragma once

#include <vector>
#include <string>
#include <memory>

#include "TXmlIO.hpp"
#include "TXmlFieldBinding.hpp"
#include "TXmlParentBinding.hpp"

template<typename T>
class Bindings
{
public:
    void readXml(const std::string &xml, T &obj);
    void writeXml(std::string &xml, const T &obj);
};

template<typename T>
void Bindings<T>::readXml(const std::string &xml, T &obj)
{
    TiXmlDocument doc;
    doc.Parse(xml.c_str());
    TiXmlElement *root = doc.FirstChildElement("root");
    TXmlIO<T>::read(obj, root);
}

template<typename T>
void Bindings<T>::writeXml(std::string &xml, const T &obj)
{
    TiXmlDocument doc;
    TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "utf-8", "");
    TiXmlElement *root = new TiXmlElement("root");
    TXmlIO<T>::write(obj, root);
    doc.LinkEndChild(decl);
    doc.LinkEndChild(root);
    TiXmlPrinter printer;
    printer.SetIndent("   ");
    doc.Accept(&printer);
    xml = printer.Str();
}

#define START_BINDINGS(CLASS_NAME) \
    public: \
    class Bindings \
    { \
    private: \
        typedef CLASS_NAME tClass; \
        typedef std::shared_ptr<IXmlBinding<tClass> > tXmlBindingPtr; \
        typedef std::vector<tXmlBindingPtr> tXmlBindings; \
        tXmlBindings mXmlFields; \
        tXmlBindings mXmlParents; \
    public: \
        Bindings() \
        { \

#define BIND_PARENT(PARENT_NAME) \
            mXmlParents.push_back(tXmlBindingPtr(new TXmlParentBinding<tClass, PARENT_NAME>())); \

#define BIND_FIELD(FIELD_NAME) \
            mXmlFields.push_back(tXmlBindingPtr(makeXmlFieldBinding(#FIELD_NAME, &tClass::FIELD_NAME))); \

#define END_BINDINGS \
        } \
        \
        void readXml(tClass &obj, const TiXmlElement *parent) \
        { \
            for(tXmlBindings::iterator it = mXmlParents.begin(); it != mXmlParents.end(); ++it) \
            { \
                (*it)->read(obj, parent); \
            } \
            for(tXmlBindings::iterator it = mXmlFields.begin(); it != mXmlFields.end(); ++it) \
            { \
                (*it)->read(obj, parent); \
            } \
        } \
        \
        void writeXml(const tClass &obj, TiXmlElement *parent) \
        { \
            for(tXmlBindings::iterator it = mXmlParents.begin(); it != mXmlParents.end(); ++it) \
            { \
                (*it)->write(obj, parent); \
            } \
            for(tXmlBindings::iterator it = mXmlFields.begin(); it != mXmlFields.end(); ++it) \
            { \
                (*it)->write(obj, parent); \
            } \
        } \
    }; \
    friend class Bindings;


