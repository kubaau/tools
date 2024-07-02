#pragma once

#include <ciso646>

#define __builtin_bswap32(n) _byteswap_ulong(n)
#define aligned(N) align(N)
#define __attribute__(A) __declspec##A
