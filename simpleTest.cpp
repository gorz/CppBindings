#include <iostream>
#include <limits>
#include <cmath>
#include <assert.h>

#include "bindings/bindings.hpp"

using namespace std;

struct Custom
{
   int i;
};

bool operator==(const Custom &l, const Custom &r)
{
   return l.i == r.i;
}

template<>
void TXmlIO<Custom>::read(Custom &obj, const TiXmlElement *parent);
template<>
void TXmlIO<Custom>::write(const Custom &obj, TiXmlElement *parent);

struct A
{
   int i;
   double d;
   string s;

    A();
    A(int i, double d, string s);
    bool operator==(const A &a) const;

    START_BINDINGS(A)
    BIND_FIELD(i)
    BIND_FIELD(d)
    BIND_FIELD(s)
    END_BINDINGS
};

A::A()
{

}

A::A(int i, double d, string s)
    : i(i)
    , d(d)
    , s(s)
{

}

bool A::operator==(const A &a) const
{
    return a.i == i && s.compare(a.s) == 0 && std::abs(a.d - d) <= std::numeric_limits<double>::epsilon();
}

struct B : public A
{
    int in;
    A a;
   Custom m;

    B();
    B(int i1, double d, string s, int i2, A a, Custom m);
    bool operator==(const B &b) const;

    START_BINDINGS(B)
    BIND_PARENT(A)
    BIND_FIELD(in)
    BIND_FIELD(a)
   BIND_FIELD(m)
    END_BINDINGS
};

B::B()
{

}

B::B(int i1, double d, string s, int i2, A a, Custom m)
    : A(i1, d, s)
    , in(i2)
    , a(a)
   , m(m)
{

}

bool B::operator==(const B &b) const
{
    return b.in == in && b.a == a && (const A &)(*this) == (const A &)b && b.m == m;
}

int main()
{
    {
        A a1(2, 0.3, "arr");
        A a2;
        Bindings<A> b;
        string xml;

        b.writeXml(xml, a1);
        b.readXml(xml, a2);
        assert(a1 == a2);
    }

    {
        B a1(2, 0.3, "arr", 1, A(4, 0.7, "arrr"), {3});
        B a2;
        Bindings<B> b;
        string xml;
        b.writeXml(xml, a1);
        cout << xml << endl;
        b.readXml(xml, a2);
        assert(a1 == a2);
    }


    return 0;
}

template<>
void TXmlIO<Custom>::read(Custom &obj, const TiXmlElement *parent)
{
   const char *str = parent->Attribute("value");
   std::stringstream ss;
   ss << str;
   ss >> obj.i;
   obj.i /= 3;
}

template<>
void TXmlIO<Custom>::write(const Custom &obj, TiXmlElement *parent)
{
   std::stringstream ss;
   ss << obj.i * 3;
   parent->SetAttribute("value", ss.str());
}

