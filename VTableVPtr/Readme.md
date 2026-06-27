Virtual Functions (Runtime Polymorphism)

What is a Virtual Function?

A virtual function enables runtime polymorphism.
The function invoked depends on the actual object type (dynamic type) instead of the pointer/reference type.

Base* ptr = new Derived();
ptr->display();      // Calls Derived::display()

⸻

Runtime Polymorphism

Compile-time:

* Compiler only knows Base*.
* It doesn’t know whether it points to a Base or Derived object.

Runtime:

Pointer
   ↓
Object
   ↓
vptr
   ↓
vtable
   ↓
Actual Function

⸻

vptr

* Hidden compiler-generated pointer.
* Present in every object of a polymorphic class.
* One vptr per object.
* Initialized during object construction.

⸻

vtable

* Hidden compiler-generated table.
* One vtable per polymorphic class.
* Stores addresses of virtual functions.

Example:

Base
func1 -> Base::func1
func2 -> Base::func2
func3 -> Base::func3
Derived1
func1 -> Base::func1
func2 -> Base::func2
func3 -> Derived1::func3
Derived2
func1 -> Derived2::func1
func2 -> Base::func2
func3 -> Derived1::func3

⸻

Virtual Dispatch

Base*
   ↓
Derived Object
   ↓
vptr
   ↓
Derived vtable
   ↓
Function Pointer
   ↓
Derived::function()

⸻

Interview Questions

Why is runtime dispatch needed?

At compile time, the compiler only knows the pointer/reference type.

Base* ptr;

It cannot determine whether ptr points to a Base or Derived object.

Hence, the function is resolved at runtime.

⸻

Can constructors be virtual?

❌ No.

Reason:

* Constructors create the object.
* Runtime polymorphism requires a fully constructed object.
* During construction, the object is not yet completely built.

⸻

Can constructors call virtual functions?

✅ Yes.

However, they invoke the Base implementation because the derived part has not yet been constructed.

⸻

Can destructors be virtual?

✅ Yes.

If a class is intended to be used polymorphically (deleted through a base pointer), the base destructor should be virtual.

Base* ptr = new Derived();
delete ptr;

Without virtual destructor:

Base Destructor

With virtual destructor:

Derived Destructor
Base Destructor

⸻

How does virtual destructor work?

delete ptr
      ↓
Virtual Dispatch
      ↓
Derived::~Derived()
      ↓
Compiler automatically calls
      ↓
Base::~Base()

Only the first call is resolved through the vtable.

⸻

Can static functions be virtual?

❌ No.

Reason:

Virtual dispatch requires an object (this pointer).

Static functions belong to the class, not to an object.

No object → No vptr → No virtual dispatch.

⸻

Can a pure virtual destructor exist?

✅ Yes.

But it must have a definition.

class Base {
public:
    virtual ~Base() = 0;
};
Base::~Base() {}

Reason:

Every derived destructor eventually calls the base destructor.

⸻

Pure Virtual Function vs Pure Virtual Destructor

Feature	Pure Virtual Function	Pure Virtual Destructor
Body Required	❌ No	✅ Yes
Makes Class Abstract	✅ Yes	✅ Yes

⸻

Object Slicing

Derived d;
Base b = d;

Only the Base portion is copied.

The Derived portion is discarded.

Therefore,

b.display();

prints

Base

⸻

Reference vs Object

Derived d;
Base& b = d;

No copy occurs.

The dynamic type remains Derived.

b.display();

prints

Derived

⸻

override

Compile-time safety feature.

Ensures that a virtual function is actually overriding a base class virtual function.

⸻

final

virtual void foo() final;

Cannot be overridden.

class Derived final {};

Cannot be inherited.

⸻

Why are virtual functions slower?

* Runtime dispatch.
* One extra pointer indirection (object → vptr → vtable → function).
* Harder for the compiler to inline.

⸻

Common Interview Pitfalls

* ❌ vptr is not the base class pointer.
* ❌ vtable is not created at runtime.
* ❌ Runtime polymorphism depends on the object type, not the pointer type.
* ❌ Object slicing destroys runtime polymorphism.
* ❌ A pure virtual destructor still requires a definition.
* ❌ Constructors cannot be virtual because the object is not fully constructed.
* ❌ Static functions cannot be virtual because they have no object (this pointer).

⸻

Complexity

Memory Overhead

* One hidden vptr per object.
* One vtable per polymorphic class.

Function Call Overhead

Normal Function
call → function
Virtual Function
object
   ↓
vptr
   ↓
vtable
   ↓
function

Extra indirection makes virtual calls slightly slower.