#ifdef _WIN32
#include "ComPtr.hpp"
#include <d3d11.h>
#include "GtestWrapper.hpp"

TEST(ComPtr, star_operator)
{
    ComPtr<ID3D11Device> p;
    EXPECT_EQ(&*p.Get(), &*p);
}
#endif
