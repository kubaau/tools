#pragma once

#define DEFINE_SINGLETON_INSTANCE(T) \
    static auto& instance()          \
    {                                \
        static T instance;           \
        return instance;             \
    }
