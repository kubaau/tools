#include "Singleton.hpp"

#include "GtestWrapper.hpp"

TEST(Singleton, singleton)
{
    class Sin
    {
    public:
        DEFINE_SINGLETON_INSTANCE(Sin)
#define SIN Sin::instance()

    private:
        Sin() {}
    };

    SIN;
}
