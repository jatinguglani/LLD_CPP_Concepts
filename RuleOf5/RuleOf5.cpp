#include <iostream>
#include <cstring>
using namespace std;

/*
    THEORY OVERVIEW
    ----------------
    This class manually manages a heap resource (int*).

    ➜ Any class that manages a resource MUST define how it:
      - is copied
      - is assigned
      - is destroyed

    Otherwise:
      - shallow copies happen
      - multiple objects point to the same memory
      - double delete → undefined behavior

    This leads us to the Rule of 5:
      1. Destructor
      2. Copy Constructor
      3. Copy Assignment Operator
      4. Move Constructor
      5. Move Assignment Operator
*/

class MyBuffer {

private:
    int *data;
    int size;

public:

    MyBuffer() : data(nullptr), size(0) {
        cout << "Default Constructor\n";
    }


    /*
        CONSTRUCTOR

        Purpose:
        - Acquire the resource
        - Establish class invariants

        Theory:
        - Constructor is responsible for "owning" memory
        - Ownership must be clear and exclusive
    */

    MyBuffer (int size) {
        this->size = size;

        if (size > 0) {
            data = new int[size];
            memset(data, 0, size*sizeof (int));
        } else {
            data = nullptr;
        }

        cout<<"Constructor\n";
    }

    /*
        COPY CONSTRUCTOR

        Called when:
        - MyBuffer b = a;
        - MyBuffer b(a);
        - Passing object by value

        Theory:
        - Copy constructor must create a *deep copy*
        - Each object must own its own memory
        - Shallow copy here would cause double delete
    */

    MyBuffer (const MyBuffer& obj) {

        cout<<"copy Constructor"<<endl;

        size = obj.size;

        if (size > 0) {
            data = new int[size];
            memcpy(data, obj.data, size*sizeof (int));
        } else {
            data = nullptr;
        }
    }

    /*
        COPY ASSIGNMENT OPERATOR

        Called when:
        - b = a;   (both objects already exist)

        Theory:
        - Assignment ≠ construction
        - We must:
            1. Handle self-assignment
            2. Release old resource
            3. Deep copy new resource
        - Order matters to avoid leaks
    */

    MyBuffer& operator=(const MyBuffer& obj) {

        cout<<"Copy Assignment"<<endl;

        // Self assignment check    
        if (this == &obj)
            return *this;

        // release currect resource
        delete[] data;

        //copy new resource
        size = obj.size;
        if (size > 0) {
            data = new int[size];
            memcpy (data, obj.data, size*sizeof(int));
        } else {
            data = nullptr;
        }

        return *this;
    }

    /*
        MOVE CONSTRUCTOR

        Called when:
        - MyBuffer b = std::move(a);
        - Returning objects by value (optimizations)

        Theory:
        - Moves TRANSFER ownership instead of copying
        - No allocation
        - No deep copy
        - Much faster than copy

        Important:
        - Source object must be left in a valid state
        - Usually: nullptr + size = 0
        - noexcept is critical for STL containers
    */
    MyBuffer(MyBuffer&& obj) noexcept {
        
        cout<<"Move Constructor"<<endl;

        data = obj.data;
        size = obj.size;

        //steal ownership
        obj.data = nullptr;
        obj.size = 0;
    }

    /*
        MOVE ASSIGNMENT OPERATOR

        Called when:
        - b = std::move(a);

        Theory:
        - Similar to move constructor, but target already owns memory
        - Must:
            1. Free current resource
            2. Steal other's resource
            3. Null out source
    */
    MyBuffer& operator=(MyBuffer&& obj) noexcept {
        cout<<"Move Assignment"<<endl;

        if (this == &obj)
            return *this;

        delete[] data;

        data = obj.data;
        size = obj.size;

        obj.data = nullptr;
        obj.size = 0;

        return *this;
    }

    /*
        DESTRUCTOR

        Theory:
        - Called when object goes out of scope
        - Must release owned resource
        - Should NEVER throw exceptions
    */
    ~MyBuffer() {
        std::cout << "Destructor\n";
        delete[] data;
    }
};

int main() {
    MyBuffer a(5);              // Constructor

    MyBuffer b = a;             // Copy Constructor

    MyBuffer c;
    c = a;                      // Copy Assignment

    MyBuffer d = std::move(a);  // Move Constructor

    MyBuffer e;
    e = std::move(b);           // Move Assignment

    return 0;                   // Destructors called
}