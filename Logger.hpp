#pragma once

#include "Endl.hpp"
#include "OutputOperators.hpp"

class Logger
{
public:
    Logger() {}
    Logger(Logger&& moved) { moved.is_alive = false; }
    ~Logger()
    {
        if (is_alive)
            endl();
    }

private:
    bool is_alive = true;
};

template <typename T>
Logger operator<<(Logger&& logger, const T& what)
{
    using namespace std;
    cout << what;
    return move(logger);
}

template <typename T>
Logger operator<<(Logger& logger, const T& what)
{
    return std::move(logger) << what;
}
