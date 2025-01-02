/* This code was generated. DO NOT EDIT */

#include <ho/ho/christmas.h>
#include <gmock/gmock.h>

namespace christmas { 
    class SantaMock : public Santa {
    public:
        MOCK_METHOD(void, sayHoHoHo, (), (override));
        MOCK_METHOD(void, sayMerryChristmas, (), (override));
        MOCK_METHOD(void, sayHappyNewYear, (), (override));
        
    };
}

namespace christmas { 
    class MyClassMock : public MyClass {
    public:
        MOCK_METHOD(void, myMethod, (), (override));
        MOCK_METHOD(int, myMethodWithReturn, (), (override));
        MOCK_METHOD(void, myMethodWithArgs, (int arg1, int arg2), (override));
        MOCK_METHOD(int, myMethodWithArgsAndReturn, (int arg1, int arg2), (override));
        
    };
}
