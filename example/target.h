#pragma once

namespace machine{
    class I2C{
    public:
        virtual ~I2C() = default;
        virtual void beginTransmission(int address) = 0;
        virtual void write(int data) = 0;
        virtual void endTransmission() = 0;
        virtual void requestFrom(int address, int quantity) = 0;
        virtual int available() = 0;
        virtual int read() = 0;
    };


    class Obama{
    public:
        virtual ~Obama() = default;
        virtual void ahoy(int address) = 0;
        virtual void asd(int data) = 0;
        virtual void err() = 0;
        virtual void asdxcxz(int address, int quantity) = 0;
        virtual int blau() = 0;
        virtual int errr() = 0;
    };
}
