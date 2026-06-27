#include <iostream>
using namespace std;

class Base {
public:
    virtual void func1() {
        cout << "Base::func1()" << endl;
    }

    virtual void func2() {
        cout << "Base::func2()" << endl;
    }

    virtual void func3() {
        cout << "Base::func3()" << endl;
    }

    virtual ~Base() {
        cout << "Base Destructor" << endl;
    }
};

class Derived1 : public Base {
public:
    void func3() override {
        cout << "Derived1::func3()" << endl;
    }

    ~Derived1() override {
        cout << "Derived1 Destructor" << endl;
    }
};

class Derived2 : public Derived1 {
public:
    void func1() override {
        cout << "Derived2::func1()" << endl;
    }

    ~Derived2() override {
        cout << "Derived2 Destructor" << endl;
    }
};

/*
----------------------------------------
Conceptual VTables

Base

func1 --> Base::func1
func2 --> Base::func2
func3 --> Base::func3
~Base --> Base::~Base


Derived1

func1 --> Base::func1
func2 --> Base::func2
func3 --> Derived1::func3
~Base --> Derived1::~Derived1


Derived2

func1 --> Derived2::func1
func2 --> Base::func2
func3 --> Derived1::func3
~Base --> Derived2::~Derived2

----------------------------------------

Runtime Dispatch

Base *ptr = new Derived2();

ptr
 ↓

Derived2 Object

 ↓

vptr

 ↓

Derived2 vtable

 ↓

func1 -> Derived2::func1

----------------------------------------
*/

int main()
{
    Base *ptr1 = new Base();
    Base *ptr2 = new Derived1();
    Base *ptr3 = new Derived2();

    cout << "===== Function Dispatch =====" << endl;

    ptr1->func1();
    ptr1->func2();
    ptr1->func3();

    cout << endl;

    ptr2->func1();
    ptr2->func2();
    ptr2->func3();

    cout << endl;

    ptr3->func1();
    ptr3->func2();
    ptr3->func3();

    cout << "\n===== Destructor Dispatch =====" << endl;

    delete ptr1;
    cout << endl;

    delete ptr2;
    cout << endl;

    delete ptr3;

    return 0;
}