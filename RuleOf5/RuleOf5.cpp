#include <bits/stdc++.h>
using namespace std;

class RuleOf5 {

    private:
        
    // Example resource (e.g., dynamic memory)
        int *data;
        int size;

    public:

    RuleOf5 () : data(nullptr), size(0) {
        cout<<"Default constructor"<<endl;
    }

    RuleOf5 (int size) : data(nullptr), size(0) {
        cout<<"Parameterized constructor"<<endl;

        this->size = size;

        if (size > 0) {
            data = new int[size];
            memset (data, 0, size*sizeof(int));
        } else {
            data = nullptr;
        }
    }

    //copy constructor
    RuleOf5 (const RuleOf5 & obj) : data(nullptr), size(obj.size) {
        
        cout<<"Copy Constructor"<<endl;
        if (size > 0) {
            data = new int[size];

            memcpy(data, obj.data, size*sizeof(int));
        }

    }

    // copy assignment
    
    RuleOf5& operator=(const RuleOf5 & obj) {
        cout<<"Copy Assignment"<<endl;
        
        if (this == &obj)    return *this;

        delete[] data;
        data = nullptr;
        size = obj.size;

        if (size > 0) {
            data = new int[size];
            memcpy(data, obj.data, size*sizeof(int));
        }

        return *this;
    }
    
    //move construtor
    RuleOf5 (RuleOf5 && obj) noexcept {
        cout<<"move constructor"<<endl;

        data = obj.data;
        size = obj.size;
        obj.data = nullptr;
        obj.size = 0;
    }

    //move assignment
    RuleOf5& operator=(RuleOf5 && obj) noexcept {
        
        if (this == &obj) return *this;

        delete[] data;

        data = obj.data;
        size = obj.size;
        obj.data = nullptr;
        obj.size = 0;

        return *this;
    }

    ~RuleOf5 () {
        cout<<"destructor"<<endl;
        delete[] data;
    }
};

int main () {
    RuleOf5 obj1;

    RuleOf5 obj2(10);

    RuleOf5 obj3(obj2);

    obj1 = obj3;

    RuleOf5 obj4(move(obj2));

    obj3 = move(obj4);
}
