
class Mario{
    public:
    virtual ~Mario() = default;
    virtual void jump(int height) = 0;
    virtual void run(int speed) = 0;
    virtual void die() = 0;
};