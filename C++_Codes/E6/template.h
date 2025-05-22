
#ifndef E6_TEMPLATE_H
#define E6_TEMPLATE_H

#include <iostream>

using namespace std;


template<class T, class U>
class A {
    T x;
    U y;

public:
    A() { cout << "Constructor Called" << endl; }
};


#endif //E6_TEMPLATE_H
