#pragma once

#include <boost/range.hpp>

namespace Detail
{
    using namespace std;

    template <typename R>
    class RangeConverter
    {
    public:
        explicit RangeConverter(R&& r) : r(move(r)) {}
        explicit RangeConverter(const R& r) : r(r) {}

        template <typename C, typename = enable_if_t<not is_same<C, initializer_list<typename C::value_type>>::value>>
        operator C()
        {
            return boost::copy_range<C>(r);
        }

    private:
        R r;
    };
}

template <class R>
auto toContainer(R&& r)
{
    return Detail::RangeConverter<R>{std::forward<R>(r)};
}
