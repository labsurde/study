// built and tested with "g++ -std=c++11 ..."
#include <map>
#include <memory>
#include <iostream>

#include "mem.h"

using namespace std;

class TestLogger
{
public:
    TestLogger()
    {
        cout << "TestLogger()" << " (" << this << ")"<< endl;
    }

    TestLogger(const TestLogger &from) : _id(from.get_id())
    {
        cout << "TestLogger(TestLogger &from) : " << _id  << endl;
    }

    TestLogger(int id) : _id(id)
    {
        cout << "TestLogger(int id) : " << _id << " (" << this << ")"<< endl;
    }

    ~TestLogger()
    {
        cout << "Destructed : " << _id << " (" << this << ")" << endl;
    }

    int get_id() const { return _id; }
private:
    int _id;
};

void map_object()
{
    cout << endl << __FUNCTION__ << endl;

    TestLogger a(1);
    TestLogger b(2);
    {
        map<string, TestLogger> m;
        m["1"] = a;
        m["2"] = b;
    }
    cout << "After map destroyed" << endl;
    /*
    $ g++ map.cpp && ./a.exe
    TestLogger(int id) : 1 (0x28fef4)
    TestLogger(int id) : 2 (0x28fef0)
    TestLogger() (0x392218)
    TestLogger() (0x392090)
    Destructed : 2 (0x392090)
    Destructed : 1 (0x392218)
    
    After map destroyed
    Destructed : 2 (0x28fef0)
    Destructed : 1 (0x28fef4)
    */
}

void map_unique_ptr_value()
{
    cout << endl << __FUNCTION__ << endl;

    map<string, unique_ptr<TestLogger>> m;
    auto a = test::make_unique<TestLogger>(1);
    auto b = test::make_unique<TestLogger>(2);
    m["1"] = std::move(a);
    m["2"] = std::move(b);
    /*
    $ g++ map.cpp && ./a.exe
    TestLogger(int id) : 1 (0x5521f0)
    TestLogger(int id) : 2 (0x552200)
    Destructed : 2 (0x552200)
    Destructed : 1 (0x5521f0)
    */
}


int main()
{
    map_object();
    map_unique_ptr_value();

    return 0;
}

