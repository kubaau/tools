#pragma once

#include <memory>
#include "Lock.hpp"
#include "Repeat.hpp"
#include "Typedefs.hpp"

template <class Buffer = Bytes>
class BufferPool
{
public:
    using BufferSize = Size;
    using InitialCount = Count;
    using BufferPtr = std::shared_ptr<Buffer>;

    BufferPool(BufferSize buffer_size, InitialCount init_count = 0) : buffers(init_count), buffer_size(buffer_size)
    {
        buffers.reserve(init_count);
        repeat(init_count) addNewBuffer();
    }

    auto get()
    {
        LOCK;

        for (const auto& buffer : buffers)
            if (buffer.use_count() == 1)
                return buffer;

        return addNewBuffer();
    }

private:
    auto& addNewBuffer() { return buffers.emplace_back(std::make_unique<Buffer>(buffer_size)); }

    using BufferPtrs = std::vector<BufferPtr>;
    BufferPtrs buffers;
    const BufferSize buffer_size;
    mutable std::mutex mtx;
};
