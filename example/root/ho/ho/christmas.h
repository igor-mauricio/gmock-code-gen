
namespace christmas {
    class Santa {
    public:
        virtual ~Santa() = default;
        virtual void sayHoHoHo() = 0;
        virtual void sayMerryChristmas() = 0;
        virtual void sayHappyNewYear() = 0;
    };
}


class MyClass {
public:
    virtual ~MyClass() = default;
    virtual void myMethod() = 0;
    virtual int myMethodWithReturn() = 0;
    virtual void myMethodWithArgs(int arg1, int arg2) = 0;
    virtual int myMethodWithArgsAndReturn(int arg1, int arg2) = 0;
};