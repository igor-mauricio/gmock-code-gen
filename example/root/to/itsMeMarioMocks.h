/* This code was generated. DO NOT EDIT */

#include <to/itsMeMario.h>
#include <gmock/gmock.h>

class MockMario : public Mario {
public:
    MOCK_METHOD(void, jump, (int height), (override));
    MOCK_METHOD(void, run, (int speed), (override));
    MOCK_METHOD(void, die, (), (override));
    
};
