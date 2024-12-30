#pragma once

namespace machine{
    class I2C{
    public:
        virtual void beginTransmission(int address) = 0;
        virtual void write(int data) = 0;
        virtual void endTransmission() = 0;
        virtual void requestFrom(int address, int quantity) = 0;
        virtual int available() = 0;
        virtual int read() = 0;
    };
}
