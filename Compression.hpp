#pragma once

#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include "Typedefs.hpp"

template <class T>
auto compression_op(const IOBuffer& data, const T& type)
{
    using namespace boost::iostreams;
    IOBuffer result;
    filtering_ostream os;
    os.push(type);
    os.push(boost::iostreams::back_inserter(result));
    write(os, data.data(), data.size());
    return result;
}
inline auto compress(const IOBuffer& data)
{
    return compression_op(data, boost::iostreams::gzip_compressor{});
}
inline auto decompress(const IOBuffer& data)
{
    return compression_op(data, boost::iostreams::gzip_decompressor{});
}
