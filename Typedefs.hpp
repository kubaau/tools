#pragma once

#include <cstdint>
#include <string>
#include <vector>

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using Byte = u8;
using Bytes = std::vector<Byte>;
using Buffer = Bytes;
using IOBuffer = std::vector<char>;

using Size = std::size_t;
using Count = Size;
using Name = std::string;
