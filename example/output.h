/* This code was generated. DO NOT EDIT */

#include <target.h>
#include <gmock/gmock.h>

namespace machine { 
    class MockI2C : public I2C {
    public:
        MOCK_METHOD(void, beginTransmission, (int address), (override));
        MOCK_METHOD(void, write, (int data), (override));
        MOCK_METHOD(void, endTransmission, (), (override));
        MOCK_METHOD(void, requestFrom, (int address, int quantity), (override));
        MOCK_METHOD(int, available, (), (override));
        MOCK_METHOD(int, read, (), (override));
        
    };
}