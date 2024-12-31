/* This code was generated. DO NOT EDIT */

#include <ho/ho/christmas.h>
#include <gmock/gmock.h>

namespace christmas { 
    class MockSanta : public Santa {
    public:
        MOCK_METHOD(void, sayHoHoHo, (), (override));
        MOCK_METHOD(void, sayMerryChristmas, (), (override));
        MOCK_METHOD(void, sayHappyNewYear, (), (override));
        
    };
}
