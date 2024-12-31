
namespace christmas {
    class Santa {
    public:
        virtual ~Santa() = default;
        virtual void sayHoHoHo() = 0;
        virtual void sayMerryChristmas() = 0;
        virtual void sayHappyNewYear() = 0;
    };
}