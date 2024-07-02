#include "Args.hpp"
#include "GtestWrapper.hpp"
#include "Repeat.hpp"

TEST(Args, args)
{
    char** args_arr = new char*[3];
    repeat(3)
    {
        args_arr[i] = new char[2];
        args_arr[i][0] = to_string(i)[0];
        args_arr[i][1] = 0;
    }

    const auto a = readArgs(3, reinterpret_cast<char**>(args_arr));
    EXPECT_EQ(a, (Args{"0", "1", "2"}));

    repeat(3) delete[] args_arr[i];
    delete[] args_arr;
}
